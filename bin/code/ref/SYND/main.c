#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "synd.h"

int main(int argc, char* argv[]) {
  int i;
  FILE* input_file = stdin;
  FILE* key_file = stdin;
  FILE* output_file = stdout;
  int securityLevel = 83;
  
  for (i=1; i<argc; i++) {
    /* read input file name */
    if (strcmp(argv[i],"-i") == 0) {
      if ((argc > i+1) && (strcmp(argv[i+1],"-k") != 0) && (strcmp(argv[i+1],"-o") != 0)) {
        input_file = fopen(argv[i+1], "rb");
      } else {
        fprintf(stderr, "Error: option \"-i\" must be followed by the name of the file to be encrypted.\n");
        return 1;
      }
    }
    /* read key file name */
    else if (strcmp(argv[i],"-k") == 0) {
      if ((argc > i+1) && (strcmp(argv[i+1],"-i") != 0) && (strcmp(argv[i+1],"-o") != 0)) {
        key_file = fopen(argv[i+1], "rb");
      } else {
        fprintf(stderr, "Error: option \"-k\" must be followed by the name of the key file to be used.\n");
        return 1;
      }
    }
    /* read output file name */
    else if (strcmp(argv[i],"-o") == 0) {
      if ((argc > i+1) && (strcmp(argv[i+1],"-i") != 0) && (strcmp(argv[i+1],"-k") != 0)) {
        output_file = fopen(argv[i+1], "wb");
      } else {
        fprintf(stderr, "Error: option \"-o\" must be followed by the name of the output file.\n");
        return 1;
      }
    }
    else if (strcmp(argv[i],"-s") == 0) {
      securityLevel = atoi(argv[i+1]);
    }
  }
  
  return EncryptFile(securityLevel, input_file, key_file, output_file);
}
