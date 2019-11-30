#define LUI(a) (((a)-1)/(sizeof(int)<<3)+1)

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;

typedef enum {
  SUCCESS = 0,
  FAIL = 1,
  BAD_SECURITY_LEVEL = 2,
  BAD_KEYLEN = 3,
  BAD_IVLEN = 4
} Return;

typedef struct{
  /* current state and space for new state, r bits first part and c bits second part each*/
  unsigned char* state;
  unsigned int* new_state;

  /* s state size, r key size *MUST* be a multiple of 8, c capacity*/
  unsigned int s, r, c;

  /* n regular word length, w regular word weight */
  unsigned int n, w, p;
    /* number of QC blocks */
  unsigned int b;
  /* for each column : number of input bits, number from first "r" part, number from second "c" part */
  unsigned int bpc, bfr, bfc;

  /* the "first line" of matrix H */
  unsigned char *** first_line;

  /* input buffer */
  BitSequence* buffer;
  /* number of bits in the input buffer */
  unsigned int count;

  /* output buffer */
  BitSequence* output_buffer;
  /* number of bits in the output buffer */
  unsigned int outcount;
} keystreamState;

Return Init(keystreamState *state, int securityLevel);
Return InitState(keystreamState *state, const BitSequence* key, const BitSequence* iv);
Return Update(keystreamState *state);
Return Output(keystreamState *state, FILE* output_file);
Return EncryptFile(int securityLevel, FILE* input_file, FILE* key_file, FILE* output_file);

void freeKeystreamState(keystreamState* state);

unsigned int logarithm(unsigned int a);
