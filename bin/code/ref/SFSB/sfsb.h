#define LUI(a) (((a)-1)/(sizeof(int)<<3)+1)

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;

typedef enum {
  SUCCESS = 0,
  FAIL = 1,
  BAD_HASHBITLEN = 2
} Return;

typedef struct{
  /* current state and space for new state, r bits first part and c bits second part each*/
  unsigned char *state;
  unsigned int *new_state;

  /* s state size, r key size *MUST* be a multiple of 8, c capacity*/
  unsigned int s, r, c;

  unsigned int nrOfIntWiseXors, nrOfByteWiseXors;

  /* n regular word length, w regular word weight */
  unsigned int n, w, p;
  /* number of QC blocks */
  unsigned int b;
  /* for each column : number of input bits, number from first "r" part, number from second "c" part */
  unsigned int bpc, bfr, bfc;

  /* the "first line" of matrix H */
  unsigned char *** first_line;

  /* hash length */
  int hashbitlen;

  /* input buffer */
  BitSequence* buffer;
  /* number of bits in the input buffer */
  unsigned int count;

  /* number of bits hashed */
  DataLength databitlen;
} keystreamState;

Return Init(keystreamState *state, int hashbitlen);
Return Update(keystreamState *state);
Return Final(keystreamState *state, BitSequence *hashval);
Return HashFile(int hashbitlen, FILE* input_file, BitSequence* hashval);

void freeKeystreamState(keystreamState* state);

void printHash(BitSequence* hashval, int hashbitlen);
unsigned int logarithm(unsigned int a);
