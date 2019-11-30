#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "2sc.h"
#include "pi.h"

#define NUMBER_OF_UPDATE_ROUNDS 100

/* parameters of 2SC, hardcoded for each security level */
#define NUMBER_OF_PARAMETERS 3
const int parameters[NUMBER_OF_PARAMETERS][6] = {
  /*
   * parameters of 2SC in order:
   * {securityLevel (bits), n, w, s, c, p}
   */
  {100,1572864,24,384,240,389},
  {200,2228224,34,544,336,547},
  {350,3801088,58,928,576,941}
};

Return Init(keystreamState *state, int securityLevel) {
  int i, j, k, l;
  const unsigned char* Pi_line;
  for (i=0; i<NUMBER_OF_PARAMETERS; i++) {
    if (securityLevel == parameters[i][0]) {
      state->n = parameters[i][1];
      state->w = parameters[i][2];
      state->s = parameters[i][3];
      state->c = parameters[i][4];
      state->p = parameters[i][5];
      state->b = state->n/state->s;
      state->r = state->s-state->c;
      state->bpc = logarithm(state->n/state->w);
      state->bfr = state->r/state->w;
      state->bfc = state->c/state->w;

      /* compute the first QC matrix line */
      state->first_line = (unsigned char***) malloc(state->b*sizeof(unsigned char**));
      for (k=0; k<state->b; k++) {
        state->first_line[k] = (unsigned char**) malloc(8*sizeof(unsigned char*));
        state->first_line[k][0] = (unsigned char*) calloc(((state->p+state->s)>>3)+1,1);
        Pi_line = &(Pi[k*((state->p>>3)+1)]);
        for (j=0; j<(state->p>>3); j++) {
          state->first_line[k][0][(state->s>>3)+j] = Pi_line[j];
        }
        state->first_line[k][0][(state->p+state->s)>>3] = Pi_line[state->p>>3]&(((1<<(state->p&7))-1)<<(8-(state->p&7)));
        for (j=0; j<(state->s>>3); j++) {
          state->first_line[k][0][j] = state->first_line[k][0][(state->p>>3)+j]<<(state->p&7);
          state->first_line[k][0][j] ^= state->first_line[k][0][(state->p>>3)+j+1]>>(8-(state->p&7));
        }
        for (j=1; j<8; j++) {
          state->first_line[k][j] = (unsigned char*) calloc(((state->p+state->s)>>3)+1,1);
          for (l=0; l<(state->p+state->s)>>3; l++) {
            state->first_line[k][j][l] ^= state->first_line[k][0][l] >> j;
            state->first_line[k][j][l+1] ^= state->first_line[k][0][l] << (8-j);
          }
        }
      }

      state->state = (unsigned char*) calloc(LUI(state->s),sizeof(unsigned int));
      state->new_state = (unsigned int*) calloc(LUI(state->s),sizeof(unsigned int));
      state->buffer = (unsigned char*) calloc(LUI(state->r),sizeof(unsigned int));
      state->output_buffer = (unsigned char*) malloc(4096);
      state->count = 0;
      state->outcount = 0;

      return SUCCESS;
    }
  }

  return BAD_SECURITY_LEVEL;
}

Return InitState(keystreamState *state, const BitSequence* key, const BitSequence* iv) {
  int i;

  // Call Update for the first time, i.e. state->state == f1(x1||0^c)
  for (i=0; i<(state->r>>3); i++) {
    state->state[i] = key[i];
  }
  Update(state);

  // XOR first "r" part with IV, i.e. state->state == ((f1[r](x1||0^c) xor IV) || (f1[c](x1||0^c)))
  for (i=0; i<(state->r>>3); i++) {
    state->state[i] ^= iv[i];
  }

  // Call Update for a second time, i.e. state->state == f1((f1[r](x1||0^c) xor IV) || (f1[c](x1||0^c)))
  Update(state);

  return SUCCESS;
}

Return Update(keystreamState *state) {
  int i,j,index,bidx,tmp;
  unsigned int* temp;

  for (i=0; i<LUI(state->s); i++) {
    state->new_state[i] = 0;
  }

  for (i=0; i<state->w; i++) {
    index = i<<state->bpc;
    switch (state->bpc) {
    case 2:
      index ^= (state->state[i>>2]>>(6-((i&3)<<1)))&3;
      break;
    case 4:
      index ^= (state->state[i>>1]>>(4-((i&1)<<2)))&15;
      break;
    case 8:
      index ^= state->state[i];
      break;
    case 16:
	    index ^= state->state[i<<1]<<8;
      index ^= state->state[(i<<1)+1];
	    break;
    default:
      tmp = (i+1)*state->bpc;
      for (j=i*state->bpc; j<tmp; j++) {
	      index ^= ((state->state[j>>3]>>(7-(j&7)))&1)<<(tmp-j-1);
      }
    }

    bidx = index/state->s; /* index of the vector */
    index = index - bidx*state->s; /* shift to perform on the vector */

    /* we have finished computing the vector index, now we XOR it! */
    temp = (unsigned int*) &(state->first_line[bidx][index&7][(state->s>>3)-(index>>3)]);
    for (j=LUI(state->s)-1; j>=0; j--) {
      state->new_state[j] ^= temp[j];
    }
  }

  temp = state->new_state;
  state->new_state = (unsigned int*) state->state;
  state->state = (unsigned char*) temp;

  return SUCCESS;
}

Return Output(keystreamState *state, FILE* output_file) {
  int i, return_value;
  unsigned int *tempInt1, *tempInt2;
  unsigned char* tempChar;
  
  // Update
  return_value = Update(state);
  if (return_value != SUCCESS) {
    return return_value;
  }

  // XOR to encrypt
  tempInt1 = (unsigned int*) state->state;
  tempInt2 = (unsigned int*) state->buffer;
  for (i=0; i<LUI(state->count); i++) {
    state->new_state[i] = tempInt1[i] ^ tempInt2[i];
  }

  // Write cipher block to stream
  tempChar = (unsigned char*) state->new_state;
  if ((state->outcount + state->count)>>3 >= 4096) { // if we can fill the output buffer completely
    // fill up the output buffer with the missing bits from the current cipher block
    memcpy(&(state->output_buffer[state->outcount>>3]), state->new_state, (4096-(state->outcount>>3)));
    // write output buffer to stream
    fwrite(state->output_buffer, 1, 4096, output_file);
    // write the remaining bits from the current cipher block to the output buffer
    memcpy(state->output_buffer, &tempChar[(4096-(state->outcount>>3))], ((state->count>>3)-(4096-(state->outcount>>3))));
    state->outcount = (state->count-((4096<<3)-state->outcount));
  } else {
    // write all bits from the current cipher block to the output buffer
    memcpy(&(state->output_buffer[state->outcount>>3]), state->new_state, state->count>>3);
    state->outcount += state->count;
  }

  return SUCCESS;
}

Return EncryptFile(int securityLevel, FILE* input_file, FILE* key_file, FILE* output_file) {
  int i, size, return_value;
  keystreamState* state;
  unsigned char *key, *iv; // key, initial vector (IV)
  unsigned char *fbuffer; // file buffer
  int fcount; // number of bits in file buffer

  // Init
  state = (keystreamState*) malloc(sizeof(keystreamState));
  return_value = Init(state, securityLevel);
  if (return_value != SUCCESS) {
    free(state);
    return return_value;
  }

  // Read key
  key = (unsigned char*) malloc(state->r>>3);
  size = fread(key, 1, (state->r>>3), key_file);
  if (size < (state->r>>3)) {
    free(key);
    return BAD_KEYLEN;
  }

  // Set IV
  iv = (unsigned char*) calloc(state->r>>3, sizeof(unsigned char)); // use the all 0 r bit vector as IV

  // InitState
  return_value = InitState(state, key, iv);
  free(key);
  free(iv);
  if (return_value != SUCCESS) {
    return return_value;
  }
  
  // Update
  for (i=0; i<NUMBER_OF_UPDATE_ROUNDS; i++) {
    return_value = Update(state);
    if (return_value != SUCCESS) {
      return return_value;
    }
  }

  // Output
  fbuffer = (unsigned char*) malloc(4096*sizeof(unsigned char));
  while (!feof(input_file)) {
    size = fread(fbuffer, 1, 4096, input_file);
    fcount = size<<3;
    if (state->count + fcount >= state->r) { // if we can fill up the input buffer completely
      // fill up the input buffer with the missing bits from the file buffer which is completely full now
      memcpy(&(state->buffer[state->count>>3]), fbuffer, (state->r-state->count)>>3);
      fcount -= (state->r-state->count);
      state->count = state->r;
      return_value = Output(state, output_file);
      if (return_value != SUCCESS) {
        free(fbuffer);
        return return_value;
      }
      // while there are enough bits in the file buffer to fill the input buffer completely
      while (fcount >= state->r) {
        memcpy(state->buffer, &(fbuffer[size-(fcount>>3)]), state->r>>3);
        return_value = Output(state, output_file);
        if (return_value != SUCCESS) {
          free(fbuffer);
          return return_value;
        }
        fcount -= state->r;
      }
      // copy remaining bits in file buffer to input buffer
      memcpy(state->buffer, &(fbuffer[size-(fcount>>3)]), fcount>>3);
      state->count = fcount;
      fcount = 0;
    } else { // we can't fill up the input buffer completely
      // copy remaining bits in file buffer to input buffer
      memcpy(&(state->buffer[state->count>>3]), &(fbuffer[size-(fcount>>3)]), fcount>>3);
      state->count += fcount;
      fcount = 0;
    }
  }
  
  // handle the last [1; state->r) bits
  if (state->count > 0) {
    Output(state, output_file);
    if (return_value != SUCCESS) {
      free(fbuffer);
      return return_value;
    }
  }
  
  // write the remaining bits from the output buffer to the output file
  if (state->outcount > 0) {
    fwrite(state->output_buffer, 1, state->outcount>>3, output_file);
  }
  free(fbuffer);

  fclose(input_file);
  fclose(key_file);
  fclose(output_file);

  freeKeystreamState(state);

  return return_value;
}

void freeKeystreamState(keystreamState* state) {
  /*
   * Now we also have to free all the memory allocated during Init
   */
  free(state->state);
  free(state->new_state);
  free(state->buffer);
  free(state->output_buffer);
  free(state);
}

unsigned int logarithm(unsigned int a) {
  int i;
  for (i=0; i<32; i++) {
    if (a == (1<<i)) {
      return i;
    }
  }
  fprintf(stderr,"Error: bad parameters, log %u does not exists.\n",a);
  return -1;
}
