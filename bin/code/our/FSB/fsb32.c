#include <assert.h>
#include <string.h>
#include <stdio.h>

#define asm __asm

#include "whirlpool.h"

typedef unsigned long long int word;
#define WORDSIZE 8
#define NWORDS (r8/WORDSIZE)
#define LVEC8 (p8+r8)
#define LVECW (LVEC8 % WORDSIZE == 0 ? LVEC8/WORDSIZE : LVEC8/WORDSIZE+1)

#include "params.h"
#define b   (n/r)                      // number of submatrices
#define p8  (p%8 == 0 ? p/8 : p/8 + 1) // initial vector size (in bytes)
#define pm8 (p%8)                      // 8 bit alignment
#define r8  (r/8)                      // final vector size (in bytes)
#define sr8 ((s-r)/8)                  // message block size (bytes)
#define rw  (r/w)                      // Wi size (buts) (= 8)
#define srw ((s-r)/w)                  // Mi size (bites)

typedef unsigned char byte;
extern const byte H[b][8][LVECW*WORDSIZE];

inline void update(byte in[sr8], word out[NWORDS], byte IV[r8])
{
	memcpy(IV, out, r8);

#if hashlen == 160
	asm
	(
		  "xorps %xmm0, %xmm0\n"
		"\txorps %xmm1, %xmm1\n"
		"\txorps %xmm2, %xmm2\n"
		"\txorps %xmm3, %xmm3\n"
		"\txorps %xmm4, %xmm4"
	);
#else
#if hashlen == 224
	asm
	(
		  "xorps %xmm0, %xmm0\n"
		"\txorps %xmm1, %xmm1\n"
		"\txorps %xmm2, %xmm2\n"
		"\txorps %xmm3, %xmm3\n"
		"\txorps %xmm4, %xmm4\n"
		"\txorps %xmm5, %xmm5\n"
		"\txorps %xmm6, %xmm6\n"
	);
#else
	memset(out, 0, r8);
#endif
#endif
	
	unsigned int curIndexShift = 0;
	byte* curIVB = IV;
	byte* curMB  = in;
	unsigned int curMb = 0;
	for (unsigned int i = 0; i < w; i++)
	{
		unsigned int Mi;
		if (curMb <= 8 - srw)
		{
			Mi = (*curMB >> (8-srw-curMb)) & (0xFF >> (8-srw));
			curMb += srw;
		}
		else
		{
			Mi = (*curMB << (curMb+srw-8)) & (0xFF >> (8-srw));
			curMB++;
			Mi |= *curMB >> (16-srw-curMb);
			curMb += srw - 8;
		}
		unsigned int Wi = curIndexShift + *curIVB + (Mi << rw);
		curIVB++;
		curIndexShift += n / w;
		
		unsigned int Wir = Wi/r;  // vector id
		unsigned int mWir = Wi%r; // shift
		unsigned int iB = mWir/8; // byte part of the shift
		unsigned int ib = mWir%8; // bit part of the shift
		
		const word* Vi = (word*)(H[Wir][ib] + r8 - iB);
#if hashlen == 160
		asm
		(
			  "movups   (%0), %%xmm5\n"
			"\txorps  %%xmm5, %%xmm0\n"
			"\tmovups 16(%0), %%xmm5\n"
			"\txorps  %%xmm5, %%xmm1\n"
			"\tmovups 32(%0), %%xmm5\n"
			"\txorps  %%xmm5, %%xmm2\n"
			"\tmovups 48(%0), %%xmm5\n"
			"\txorps  %%xmm5, %%xmm3\n"
			"\tmovups 64(%0), %%xmm5\n"
			"\txorps  %%xmm5, %%xmm4"
			:
			: "r"(Vi)
		);
#else
#if hashlen == 224
		asm
		(
			  "movups   (%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm0\n"
			"\tmovups 16(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm1\n"
			"\tmovups 32(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm2\n"
			"\tmovups 48(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm3\n"
			"\tmovups 64(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm4\n"
			"\tmovups 80(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm5\n"
			"\tmovups 96(%0), %%xmm7\n"
			"\txorps  %%xmm7, %%xmm6\n"
			:
			: "r"(Vi)
		);
#else
//		for (unsigned int j = 0; j < NWORDS; j++)
//			out[j] ^= Vi[j];
#include "outXorVi.c"
#endif
#endif
	}
#if hashlen == 160
	asm
	(
		  "movups %%xmm0,   (%0)\n"
		"\tmovups %%xmm1, 16(%0)\n"
		"\tmovups %%xmm2, 32(%0)\n"
		"\tmovups %%xmm3, 48(%0)\n"
		"\tmovups %%xmm4, 64(%0)"
		:
		: "r"(out)
	);
#else
#if hashlen == 224
	asm
	(
		  "movups %%xmm0,   (%0)\n"
		"\tmovups %%xmm1, 16(%0)\n"
		"\tmovups %%xmm2, 32(%0)\n"
		"\tmovups %%xmm3, 48(%0)\n"
		"\tmovups %%xmm4, 64(%0)\n"
		"\tmovups %%xmm5, 80(%0)\n"
		"\tmovups %%xmm6, 96(%0)"
		:
		: "r"(out)
	);
#endif
#endif
}
int main(int argc, char** argv)
{
	byte in[sr8];
	word out[NWORDS];
	byte tmp[r8];
	memset(out, 0, r8); // IV
	
	FILE* f = argc > 1 ? fopen(argv[1], "r") : stdin;
	assert(f);
	unsigned long long int databitlen = 0;
	while (1)
	{
		databitlen += fread(in, 1, sr8, f);
		if (feof(f))
			break;
		update(in, out, tmp);
	}
	fclose(f);
	
	// padding handling
	unsigned long long int lastRead = databitlen % sr8;
	in[lastRead] = 0x80;
	if (lastRead >= sr8-8)
	{
		memset(in+lastRead+1, 0, sr8-lastRead-1);
		update(in, out, tmp);
		lastRead = 0;
	}
	memset(in+lastRead+1, 0, sr8-lastRead-9);
	unsigned int len = databitlen << 3;
	for (unsigned int i = 1; i <= 8; i++)
	{
		in[sr8-i] = len;
		len >>= 8;
	}
	update(in, out, tmp);
	
	// final
	byte hash[64];
	struct NESSIEstruct whirlpool_ctx;
	NESSIEinit(&whirlpool_ctx);
	NESSIEadd((byte*)out, r, &whirlpool_ctx);
	NESSIEfinalize(&whirlpool_ctx, hash);
	
	// output
	printf("%s: ", argc > 1 ? argv[1] : "Standard input");
	for (unsigned int j = 0; j < hashlen/8; j++)
		printf("%.2x", hash[j]);
	printf("\n");
	
	return 0;
}
