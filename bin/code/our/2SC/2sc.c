/*
 For convenience, it is assumed that:
   * r, r1 and r2 are multiples of 8
   * w = r / 8
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define asm __asm
#include "params.h"
typedef unsigned char byte;
extern byte H1[N][S8A] __attribute((aligned(16)));
extern byte H2[N][S8A] __attribute((aligned(16)));

inline void apply(byte F[N][S8A], byte in[S8A], byte out[S8A])
{
	asm
	(
		    "xorps %xmm0, %xmm0"
#if S > 128
		"\n\txorps %xmm1, %xmm1"
#endif
#if S > 256
		"\n\txorps %xmm2, %xmm2"
#endif
#if S > 384
		"\n\txorps %xmm3, %xmm3"
#endif
#if S > 512
		"\n\txorps %xmm4, %xmm4"
#endif
#if S > 640
		"\n\txorps %xmm5, %xmm5"
#endif
#if S > 768
		"\n\txorps %xmm6, %xmm6"
#endif
#if S > 896
		"\n\txorps %xmm7, %xmm7"
#endif
	);
	unsigned int currentIndexShift = 0;
	byte* curMB = in;
	for (unsigned int i = 0; i < W; i++)
	{
		unsigned int Wi = currentIndexShift + *curMB;
		currentIndexShift += N/W;
		curMB++;
		
		asm
		(
			    "xorps   0(%0), %%xmm0"
#if S > 128
			"\n\txorps  16(%0), %%xmm1"
#endif
#if S > 256
			"\n\txorps  32(%0), %%xmm2"
#endif
#if S > 384
			"\n\txorps  48(%0), %%xmm3"
#endif
#if S > 512
			"\n\txorps  64(%0), %%xmm4"
#endif
#if S > 640
			"\n\txorps  80(%0), %%xmm5"
#endif
#if S > 768
			"\n\txorps  96(%0), %%xmm6"
#endif
#if S > 896
			"\n\txorps 112(%0), %%xmm7"
#endif
			:
			: "r"(F[Wi])
		);
	}
	
	if (!out)
		return;
	
	asm
	(
		    "movups %%xmm0,   0(%0)"
#if S > 128
		"\n\tmovups %%xmm1,  16(%0)"
#endif
#if S > 256
		"\n\tmovups %%xmm2,  32(%0)"
#endif
#if S > 384
		"\n\tmovups %%xmm3,  48(%0)"
#endif
#if S > 512
		"\n\tmovups %%xmm4,  64(%0)"
#endif
#if S > 640
		"\n\tmovups %%xmm5,  80(%0)"
#endif
#if S > 768
		"\n\tmovups %%xmm6,  96(%0)"
#endif
#if S > 896
		"\n\tmovups %%xmm7, 112(%0)"
#endif
		:
		: "r"(out)
		: "memory"
	);
}
int main(int argc, char** argv)
{
	// STATE INITIALISATION
	
	byte state[S8A] __attribute__((aligned(16)));
	byte in   [R8A] __attribute__((aligned(16)));
	
	// key
	FILE* keyFile = (argc > 1 && strcmp(argv[1], "-")) ? fopen(argv[1], "r") : stdin;
	assert(keyFile);
//	fread(y, K8, 1, keyFile);
	
	// initial value
//	memset(y + K8, 0, IV8);
	
	// first state computation
	// TODO
	memset(state, 0, S8);
	
	// ENCRYPTION
	
	FILE* inFile = (argc > 2 && strcmp(argv[2], "-")) ? fopen(argv[2], "r") : stdin;
	assert(inFile);
	FILE* outFile = argc > 3 ? fopen(argv[3], "w") : stdout;
	assert(outFile);
	while (!feof(inFile))
	{
		fread(in, R8, 1, inFile);
		
		apply(H1, state, state); // update the state
		asm
		(
			    "xorps     (%0), %%xmm0"
			"\n\tmovaps %%xmm0,    (%0)"
#if R > 128
			"\n\txorps   16(%0), %%xmm1"
			"\n\tmovaps %%xmm1,  16(%0)"
#endif
#if R > 256
			"\n\txorps   32(%0), %%xmm2"
			"\n\tmovaps %%xmm2,  32(%0)"
#endif
#if R > 384
			"\n\txorps   48(%0), %%xmm3"
			"\n\tmovaps %%xmm3,  48(%0)"
#endif
#if R > 512
			"\n\txorps   64(%0), %%xmm4"
			"\n\tmovaps %%xmm4,  64(%0)"
#endif
#if R > 640
			"\n\txorps   80(%0), %%xmm5"
			"\n\tmovaps %%xmm5,  80(%0)"
#endif
#if R > 768
			"\n\txorps   96(%0), %%xmm6"
			"\n\tmovaps %%xmm6,  96(%0)"
#endif
#if R > 896
			"\n\txorps  112(%0), %%xmm7"
			"\n\tmovaps %%xmm7, 112(%0)"
#endif
			:
			: "r"(in)
			: "memory"
		);
		
		fwrite(in, 1, R8, outFile);
	}
	fclose(outFile);
	fclose(inFile);
	fclose(keyFile);
	
	return 0;
}
