#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "sfsb.h"
#include "pi.h"

/* parameters of S-FSB, hardcoded for each output length */
#define NUMBER_OF_PARAMETERS 3
const int parameters[NUMBER_OF_PARAMETERS][6] = {
  /*
   * parameters of S-FSB in order:
   * {hashbitlen, n, w, s, c, p}
   */
  { 160,1572864,24,384,240,389}, 
  { 224,2228224,34,544,336,547},
  { 384,3801088,58,928,576,941}
};

Return Init(keystreamState *state, int hashbitlen) {
  int i, j, k, l;
  const unsigned char* Pi_line;
  for (i=0; i<NUMBER_OF_PARAMETERS; i++) {
    if (hashbitlen == parameters[i][0]) {
      state->hashbitlen = parameters[i][0];
      state->n = parameters[i][1];
      state->w = parameters[i][2];
      state->s = parameters[i][3];
      state->c = parameters[i][4];
      state->p = parameters[i][5];
      state->b = state->n/state->s;
      state->r = state->s-state->c;
      state->nrOfIntWiseXors = (state->r>>3)/sizeof(int);
      state->nrOfByteWiseXors = (state->r>>3)-state->nrOfIntWiseXors*sizeof(int);
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
      state->buffer = (unsigned char*) malloc(state->r>>3);
      state->count = 0;
      state->databitlen = 0;

      return SUCCESS;
    }
  }

  return BAD_HASHBITLEN;
}

Return Update(keystreamState *state) {
  int i,j,index, bidx, tmp;
  unsigned int *tempInt1, *tempInt2;
  unsigned char *tempChar1, *tempChar2;

  tempInt1 = (unsigned int*) state->state;
  tempInt2 = (unsigned int*) state->buffer;
  for (i=0; i<state->nrOfIntWiseXors; i++) {
    tempInt1[i] ^= tempInt2[i];
  }
  tempChar1 = (unsigned char*) &(tempInt1[i]);
  tempChar2 = (unsigned char*) &(tempInt2[i]);
  for (i=0; i<state->nrOfByteWiseXors; i++) {
    tempChar1[i] ^= tempChar2[i];
  }

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
    tempInt1 = (unsigned int*) &(state->first_line[bidx][index&7][(state->s>>3)-(index>>3)]);
    for (j=LUI(state->s)-1; j>=0; j--) {
      state->new_state[j] ^= tempInt1[j];
    }
  }

  tempInt1 = (unsigned int*) state->new_state;
  state->new_state = (unsigned int*) state->state;
  state->state = (unsigned char*) tempInt1;

  return SUCCESS;
}

Return Final(keystreamState *state, BitSequence *hashval) {
  int i;
  
  if (state->count+65 > state->r) {
    state->buffer[state->count>>3] = 1<<7;
    for (i=(state->count>>3)+1; i<state->r>>3;i++) {
      state->buffer[i] = 0;
    }
    Update(state);
    for (i=0; i<(state->r>>3)-8; i++) {
      state->buffer[i] = 0;
    }
    for (i=0; i<8; i++) {
      state->buffer[(state->r>>3)-1-i] = (unsigned char) (state->databitlen>>(8*i));
    }
    Update(state);
  } else {
    state->buffer[state->count>>3] = 1<<7;
    for (i=(state->count>>3)+1; i<(state->r>>3)-8;i++) {
      state->buffer[i] = 0;
    }
    for (i=0; i<8; i++) {
      state->buffer[(state->r>>3)-1-i] = (unsigned char) (state->databitlen>>(8*i)) ;
    }
    Update(state);
  }

  for(i=0; i<(state->hashbitlen>>3); i++) {
    hashval[i] = state->state[i];
  }

  return SUCCESS;
}

Return HashFile(int hashbitlen, FILE* input_file, BitSequence* hashval) {
  int size, return_value;
  keystreamState* state;
  unsigned char *fbuffer; // file buffer
  int fcount; // number of bits in file buffer

  // Init
  state = (keystreamState*) malloc(sizeof(keystreamState));
  return_value = Init(state, hashbitlen);
  if (return_value != SUCCESS) {
    free(state);
    return return_value;
  }

  // Hash
  fbuffer = (unsigned char*) malloc(4096*sizeof(unsigned char));
  while (!feof(input_file)) {
    size = fread(fbuffer, 1, 4096, input_file);
    fcount = size<<3;
    if (state->count + fcount >= state->r) { // if we can fill up the input buffer completely
      // fill up the input buffer with the missing bits from the file buffer which is completely full now
      memcpy(&(state->buffer[state->count>>3]), fbuffer, (state->r-state->count)>>3);
      fcount -= (state->r-state->count);
      state->count = state->r;
      return_value = Update(state);
      state->databitlen += state->count;
      if (return_value != SUCCESS) {
        free(fbuffer);
        return return_value;
      }
      // while there are enough bits in the file buffer to fill the input buffer completely
      while (fcount >= state->r) {
        memcpy(state->buffer, &(fbuffer[size-(fcount>>3)]), state->r>>3);
        return_value = Update(state);
        state->databitlen += state->count;
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

  // Final
  state->databitlen += state->count;
  Final(state, hashval);
  if (return_value != SUCCESS) {
    free(fbuffer);
    return return_value;
  }
  
  free(fbuffer);
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
  free(state);
}

void printHash(BitSequence* hashval, int hashbitlen) {
  int i;
  for (i=0; i<hashbitlen; i+=8) {
    printf("%.2x",(unsigned int) (hashval[i>>3]));
  }
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
