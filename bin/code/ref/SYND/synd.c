#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "synd.h"
#include "h1.h"
#include "h2.h"

/* parameters of SYND, hardcoded for each security level */
#define NUMBER_OF_PARAMETERS 3
const int parameters[NUMBER_OF_PARAMETERS][4] = {
  /*
   * parameters of SYND in order:
   * securityLevel, n, w, r}
   */
  {83,8192,32,256},
  {170,8192,64,512},
  {366,8192,128,1024}
};

Return Init(keystreamState *state, int mode) {
  int i;
  for (i=0; i<NUMBER_OF_PARAMETERS; i++) {
    if (mode == parameters[i][0]) {
      state->n = parameters[i][1];
      state->w = parameters[i][2];
      state->r = parameters[i][3];
      state->bpc = logarithm(state->n/state->w);
      state->state = (unsigned char*) calloc(LUI(state->r),sizeof(unsigned int));
      state->new_state = (unsigned int*) calloc(LUI(state->r),sizeof(unsigned int));
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
  unsigned int* y; // space to store y == k || iv
  unsigned int* z; // space to store z == f1(y) xor y
  unsigned int* temp;
  int i, j;
  int nrOfFullBytes;
  int nrOfRemainingBits;

  // Concatenate key and IV, i.e. state->state == key || iv
  nrOfFullBytes = state->r>>4;
  nrOfRemainingBits = (state->r>>2) - (nrOfFullBytes<<3);
  for (i = 0; i < nrOfFullBytes; i++) {
    state->state[i] = key[i];
  }
  if (nrOfRemainingBits > 0) {
    state->state[i] = (key[i] & (0xFF<<(8-nrOfRemainingBits)));
    j = 0;
    for (; i < (state->r>>3)-1;) {
      state->state[i] ^= (iv[j]>>nrOfRemainingBits);
      i++;
      state->state[i] = (iv[j] & (0xFF<<(8-nrOfRemainingBits)));
      j++;
    }
  } else {
    j = 0;
    for (; i < (state->r>>3); i++) {
      state->state[i] = iv[j];
      j++;
    }
  }

  // Save y for later use
  y = (unsigned int*) calloc(LUI(state->r), sizeof(unsigned int));
  memcpy(y, state->state, ((state->r-1)>>3)+1);

  // Call Update, i.e. state->new_state == f1(y)
  Update(state, matrixH1);

  // Calculate z == f1(y) xor y, i.e. state->state == z
  temp = (unsigned int*) state->state;
  for (i = 0; i < LUI(state->r); i++) {
    temp[i] ^= state->new_state[i];
  }

  // Save z for later use
  z = (unsigned int*) calloc(LUI(state->r), sizeof(unsigned int));
  memcpy(z, state->state, ((state->r-1)>>3)+1);

  // Call Update, i.e. state->new_state == f1(z)
  Update(state, matrixH1);

  // Calculate y xor f1(z), i.e. state->state == y xor f1(z)
  for (i = 0; i < LUI(state->r); i++) {
    temp[i] = state->new_state[i] ^ y[i];
  }

  // Call Update, i.e. state->new_state == f2(y xor f1(z))
  Update(state, matrixH2);

  // Calculate z xor f2(y xor f1(z)), i.e. state->state == z xor f2(y xor f1(z)) == g(k, iv)
  for (i = 0; i < LUI(state->r); i++) {
    temp[i] = state->new_state[i] ^ z[i];
  }

  free(y);
  free(z);

  return SUCCESS;
}

Return Update(keystreamState *state, const unsigned char matrix[8192][32]) {
  int i,j,index,tmp;
  unsigned int* temp;

  for (i=0; i<LUI(state->r); i++) {
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
    default:
      tmp = (i+1)*state->bpc;
      for (j=i*state->bpc; j<tmp; j++) {
	      index ^= ((state->state[j>>3]>>(7-(j&7)))&1)<<(tmp-j-1);
      }
    }

    /* we have finished computing the vector index, now we XOR it! */
    temp = (unsigned int*) &(matrix[index][0]);
    for (j=LUI(state->r)-1; j>=0; j--) {
      state->new_state[j] ^= temp[j];
    }
  }

  return SUCCESS;
}

Return Output(keystreamState *state, FILE* output_file) {
  int i, return_value;
  unsigned int* tempInt;
  unsigned char* tempChar;
  
  // Update
  return_value = Update(state, matrixH2);
  if (return_value != SUCCESS) {
    return return_value;
  }

  // XOR to encrypt
  tempInt = (unsigned int*) state->buffer;
  for (i=0; i<LUI(state->count); i++) {
    state->new_state[i] ^= tempInt[i];
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

Return EncryptFile(int mode, FILE* input_file, FILE* key_file, FILE* output_file) {
  int size, return_value;
  keystreamState* state;
  unsigned char *temp;
  unsigned char *key, *iv; // key, initial vector (IV)
  unsigned char *fbuffer; // file buffer
  int fcount; // number of bits in file buffer
  // Init
  state = (keystreamState*) malloc(sizeof(keystreamState));
  return_value = Init(state, mode);
  if (return_value != SUCCESS) {
    free(state);
    return return_value;
  }

  // Read key
  key = (unsigned char*) malloc(((state->r-1)>>3)+1);
  size = fread(key, 1, ((state->r-1)>>4)+1, key_file);
  if (size < ((state->r-1)>>4)+1) {
    free(key);
    printf("bad keylength");
    return BAD_KEYLEN;
  }

  // Set IV
  iv = (unsigned char*) calloc(((state->r-1)>>4)+1, sizeof(unsigned char)); // use the all 0 r bit vector as IV
  
  // InitState
  return_value = InitState(state, key, iv);
  free(key);
  free(iv);
  if (return_value != SUCCESS) {
    return return_value;
  }

  fbuffer = (unsigned char*) malloc(4096*sizeof(unsigned char));
  while (!feof(input_file)) {
    size = fread(fbuffer, 1, 4096, input_file);
    fcount = size<<3;
    if (state->count + fcount >= state->r) { // if we can fill up the input buffer completely
      // fill up the input buffer with the missing bits from the file buffer which is completely full now
      memcpy(&(state->buffer[state->count>>3]), fbuffer, (state->r-state->count)>>3);
      fcount -= (state->r-state->count);
      state->count = state->r;
      // Update
      return_value = Update(state, matrixH1);
      if (return_value != SUCCESS) {
        return return_value;
      }
      temp = (unsigned char*) state->new_state;
      state->new_state = (unsigned int*) state->state;
      state->state = temp;
      // Output
      return_value = Output(state, output_file);
      if (return_value != SUCCESS) {
        return return_value;
      }
      // while there are enough bits in the file buffer to fill the input buffer completely
      while (fcount >= state->r) {
        memcpy(state->buffer, &(fbuffer[size-(fcount>>3)]), state->r>>3);
        // Update
        return_value = Update(state, matrixH1);
        if (return_value != SUCCESS) {
          return return_value;
        }
        temp = (unsigned char*) state->new_state;
        state->new_state = (unsigned int*) state->state;
        state->state = temp;
        // Output
        return_value = Output(state, output_file);
        if (return_value != SUCCESS) {
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
    // Update
    return_value = Update(state, matrixH1);
    if (return_value != SUCCESS) {
      return return_value;
    }
    temp = (unsigned char*) state->new_state;
    state->new_state = (unsigned int*) state->state;
    state->state = temp;
    // Output
    return_value = Output(state, output_file);
    if (return_value != SUCCESS) {
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
