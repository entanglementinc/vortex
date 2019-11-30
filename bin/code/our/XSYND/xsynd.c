#include <assert.h>
#include <string.h>
#include <stdio.h>

#define asm __asm

typedef unsigned char byte;
#define R 64
#define W 112
#define C (W-R)
extern byte c[256][R];

#define K8 64
#define IV8 48

#define FOLDX(SRC, DST, DSTN, TMP)                           \
	asm                                                  \
	(                                                    \
		  "movaps " #SRC    ", " #TMP           "\n" \
		"\tpsllq  " "$3"    ", " #SRC           "\n" \
		"\txorps  " #SRC    ", " #DST           "\n" \
		"\tpsrlq  " "$61"   ", " #TMP           "\n" \
		"\tpshufd " "$0xCF" ", " #TMP ", " #SRC "\n" \
		"\txorps  " #SRC    ", " #DST           "\n" \
		"\tpsrldq " "$8"    ", " #TMP           "\n" \
		"\txorps  " #TMP    ", " #DSTN          "\n" \
	);

#define EVENSTEP(A)                         \
	asm                                 \
	(                                   \
		  "movaps   (%0), %%xmm4\n" \
		"\tmovaps 16(%0), %%xmm5\n" \
		"\tmovaps 32(%0), %%xmm6\n" \
		"\tmovaps 48(%0), %%xmm7\n" \
		"\txorps    (%1), %%xmm5\n" \
		"\txorps  16(%1), %%xmm6\n" \
		"\txorps  32(%1), %%xmm7\n" \
		"\txorps  48(%1), %%xmm0\n" \
		"\txorps    (%2), %%xmm6\n" \
		"\txorps  16(%2), %%xmm7\n" \
		"\txorps  32(%2), %%xmm0\n" \
		"\txorps  48(%2), %%xmm1\n" \
		"\txorps    (%3), %%xmm7\n" \
		"\txorps  16(%3), %%xmm0\n" \
		"\txorps  32(%3), %%xmm1\n" \
		"\txorps  48(%3), %%xmm2"   \
		:                           \
		: "r" (c[state[A+3]]),      \
		  "r" (c[state[A+2]]),      \
		  "r" (c[state[A+1]]),      \
		  "r" (c[state[A+0]])       \
	);                                  \
	FOLDX(%xmm3, %xmm7, %xmm0, %xmm8);  \
	FOLDX(%xmm0, %xmm4, %xmm5, %xmm8);  \
	FOLDX(%xmm1, %xmm5, %xmm6, %xmm8);  \
	FOLDX(%xmm2, %xmm6, %xmm7, %xmm8);
#define ODD_STEP(A)                         \
	asm                                 \
	(                                   \
		  "movaps   (%0), %%xmm0\n" \
		"\tmovaps 16(%0), %%xmm1\n" \
		"\tmovaps 32(%0), %%xmm2\n" \
		"\tmovaps 48(%0), %%xmm3\n" \
		"\txorps    (%1), %%xmm1\n" \
		"\txorps  16(%1), %%xmm2\n" \
		"\txorps  32(%1), %%xmm3\n" \
		"\txorps  48(%1), %%xmm4\n" \
		"\txorps    (%2), %%xmm2\n" \
		"\txorps  16(%2), %%xmm3\n" \
		"\txorps  32(%2), %%xmm4\n" \
		"\txorps  48(%2), %%xmm5\n" \
		"\txorps    (%3), %%xmm3\n" \
		"\txorps  16(%3), %%xmm4\n" \
		"\txorps  32(%3), %%xmm5\n" \
		"\txorps  48(%3), %%xmm6"   \
		:                           \
		: "r" (c[state[A+3]]),      \
		  "r" (c[state[A+2]]),      \
		  "r" (c[state[A+1]]),      \
		  "r" (c[state[A+0]])       \
	);                                  \
	FOLDX(%xmm7, %xmm3, %xmm4, %xmm8);  \
	FOLDX(%xmm4, %xmm0, %xmm1, %xmm8);  \
	FOLDX(%xmm5, %xmm1, %xmm2, %xmm8);  \
	FOLDX(%xmm6, %xmm2, %xmm3, %xmm8);
	
inline void upd(byte state[W])
{
	// First step
	// loading
	asm
	(
		  "movaps   (%0), %%xmm0\n"
		"\tmovaps 16(%0), %%xmm1\n"
		"\tmovaps 32(%0), %%xmm2\n"
		"\tmovaps 48(%0), %%xmm3\n"
		"\txorps    (%1), %%xmm1\n"
		"\txorps  16(%1), %%xmm2\n"
		"\txorps  32(%1), %%xmm3\n"
		"\tmovaps 48(%1), %%xmm4\n"
		"\txorps    (%2), %%xmm2\n"
		"\txorps  16(%2), %%xmm3\n"
		"\txorps  32(%2), %%xmm4\n"
		"\tmovaps 48(%2), %%xmm5\n"
		"\txorps    (%3), %%xmm3\n"
		"\txorps  16(%3), %%xmm4\n"
		"\txorps  32(%3), %%xmm5\n"
		"\tmovaps 48(%3), %%xmm6\n"
		:
		: "r" (c[state[3]]),
		  "r" (c[state[2]]),
		  "r" (c[state[1]]),
		  "r" (c[state[0]])
	);
	// folding
	FOLDX(%xmm4, %xmm0, %xmm1, %xmm8);
	FOLDX(%xmm5, %xmm1, %xmm2, %xmm8);
	FOLDX(%xmm6, %xmm2, %xmm3, %xmm8);
	
	// Other steps
	EVENSTEP(  4);
	ODD_STEP(  8);
	EVENSTEP( 12);
	ODD_STEP( 16);
	EVENSTEP( 20);
	ODD_STEP( 24);
	EVENSTEP( 28);
	ODD_STEP( 32);
	EVENSTEP( 36);
	ODD_STEP( 40);
	EVENSTEP( 44);
	ODD_STEP( 48);
	EVENSTEP( 52);
	ODD_STEP( 56);
	EVENSTEP( 60);
	ODD_STEP( 64);
	EVENSTEP( 68);
	ODD_STEP( 72);
	EVENSTEP( 76);
	ODD_STEP( 80);
	EVENSTEP( 84);
	ODD_STEP( 88);
	EVENSTEP( 92);
	ODD_STEP( 96);
	EVENSTEP(100);
	ODD_STEP(104);
	EVENSTEP(108);
	
	asm
	(
// Final fold
		  "movaps %%xmm7, %%xmm0\n"
		"\tpsrldq $8,     %%xmm0\n"
		"\tpsrlq  $61,    %%xmm0\n"
		"\txorps  %%xmm0, %%xmm4\n"
		"\tpsllq  $61,    %%xmm0\n"
		"\tpslldq $8,     %%xmm0\n"
		"\txorps  %%xmm0, %%xmm7\n"
// Unload
		:
		: "r" (state)
		: "memory"
	);
}
inline void out(byte state[W])
{
	// First step
	// loading
	asm
	(
		  "movaps   (%0), %%xmm0\n"
		"\tmovaps 16(%0), %%xmm1\n"
		"\tmovaps 32(%0), %%xmm2\n"
		"\tmovaps 48(%0), %%xmm3\n"
		"\txorps    (%1), %%xmm1\n"
		"\txorps  16(%1), %%xmm2\n"
		"\txorps  32(%1), %%xmm3\n"
		"\tmovaps 48(%1), %%xmm4\n"
		"\txorps    (%2), %%xmm2\n"
		"\txorps  16(%2), %%xmm3\n"
		"\txorps  32(%2), %%xmm4\n"
		"\tmovaps 48(%2), %%xmm5\n"
		"\txorps    (%3), %%xmm3\n"
		"\txorps  16(%3), %%xmm4\n"
		"\txorps  32(%3), %%xmm5\n"
		"\tmovaps 48(%3), %%xmm6\n"
		:
		: "r" (c[state[3]]),
		  "r" (c[state[2]]),
		  "r" (c[state[1]]),
		  "r" (c[state[0]])
	);
	// folding
	FOLDX(%xmm4, %xmm0, %xmm1, %xmm8);
	FOLDX(%xmm5, %xmm1, %xmm2, %xmm8);
	FOLDX(%xmm6, %xmm2, %xmm3, %xmm8);
	
	// Other steps
	EVENSTEP(  4);
	ODD_STEP(  8);
	EVENSTEP( 12);
	ODD_STEP( 16);
	EVENSTEP( 20);
	ODD_STEP( 24);
	EVENSTEP( 28);
	ODD_STEP( 32);
	EVENSTEP( 36);
	ODD_STEP( 40);
	EVENSTEP( 44);
	ODD_STEP( 48);
	EVENSTEP( 52);
	ODD_STEP( 56);
	EVENSTEP( 60);
	ODD_STEP( 64);
	EVENSTEP( 68);
	ODD_STEP( 72);
	EVENSTEP( 76);
	ODD_STEP( 80);
	EVENSTEP( 84);
	ODD_STEP( 88);
	EVENSTEP( 92);
	ODD_STEP( 96);
	EVENSTEP(100);
	ODD_STEP(104);
	EVENSTEP(108);
	
	asm
	(
// Final fold
		  "movaps %xmm7, %xmm0\n"
		"\tpsrldq $8,    %xmm0\n"
		"\tpsrlq  $61,   %xmm0\n"
		"\txorps  %xmm0, %xmm4\n"
		"\tpsllq  $61,   %xmm0\n"
		"\tpslldq $8,    %xmm0\n"
		"\txorps  %xmm0, %xmm7\n"
	);
}
int main(int argc, char** argv)
{
	// STATE INITIALISATION
	
	byte state[W] __attribute__((aligned(16)));
	byte in   [W] __attribute__((aligned(16)));
	
	// key
	FILE* keyFile = (argc > 1 && strcmp(argv[1], "-")) ? fopen(argv[1], "r") : stdin;
	assert(keyFile);
	fread(state, K8, 1, keyFile);
	
	// initial value
	memset(state + K8, 0, IV8);
	
	
	// ENCRYPTION
	
	FILE* inFile = (argc > 2 && strcmp(argv[2], "-")) ? fopen(argv[2], "r") : stdin;
	assert(inFile);
	FILE* outFile = argc > 3 ? fopen(argv[3], "w") : stdout;
	assert(outFile);
	while (!feof(inFile))
	{
		fread(in, W, 1, inFile);
		
		upd(state); // update the state
		out(state); // the outpu of the keystreamt is only set in SSE registers
		asm
		(
			    "xorps     (%0), %%xmm4"
			"\n\tmovaps %%xmm4,    (%0)"
			"\n\txorps   16(%0), %%xmm5"
			"\n\tmovaps %%xmm5,  16(%0)"
			"\n\txorps   32(%0), %%xmm7"
			"\n\tmovaps %%xmm6,  32(%0)"
			"\n\txorps   48(%0), %%xmm7"
			"\n\tmovaps %%xmm7,  48(%0)"
			:
			: "r"(in)
			: "memory"
		);
		
		fwrite(in, 1, W, outFile);
	}
	fclose(outFile);
	fclose(inFile);
	fclose(keyFile);
	
	return 0;
}
