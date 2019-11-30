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

#define out8 ((byte*)out)

typedef unsigned char byte;
extern const byte H[b][8][LVECW*WORDSIZE];

inline void update(byte in[sr8], word out[NWORDS], byte IV[r8])
{
	memcpy(IV, out, r8);

	asm
	(
		    "xorps %xmm0, %xmm0"
#if r >= 256
		"\n\txorps %xmm1, %xmm1\n"
#endif
#if r >= 384
		"\n\txorps %xmm2, %xmm2\n"
#endif
#if r >= 512
		"\n\txorps %xmm3, %xmm3\n"
#endif
#if r >= 640
		"\n\txorps %xmm4, %xmm4\n"
#endif
#if r >= 768
		"\n\txorps %xmm5, %xmm5\n"
#endif
#if r >= 896
		"\n\txorps %xmm6, %xmm6\n"
#endif
#if r >= 1024
		"\n\txorps %xmm7, %xmm7\n"
#endif
#if r >= 1152
		"\n\txorps %xmm8, %xmm8\n"
#endif
#if r >= 1280
		"\n\txorps %xmm9, %xmm9\n"
#endif
#if r >= 1408
		"\n\txorps %xmm10, %xmm10\n"
#endif
#if r >= 1536
		"\n\txorps %xmm11, %xmm11\n"
#endif
#if r >= 1664
		"\n\txorps %xmm12, %xmm12\n"
#endif
#if r >= 1792
		"\n\txorps %xmm13, %xmm13\n"
#endif
#if r >= 1920
		"\n\txorps %xmm14, %xmm14\n"
#endif
	);
#if (r % 128) == 8
#define LASTWORD unsigned char
#endif
#if (r % 128) == 16
#define LASTWORD unsigned short int
#endif
#if (r % 128) == 32
#define LASTWORD unsigned int
#endif
#if (r % 128) == 64
#define LASTWORD unsigned long long int
#endif
#ifdef LASTWORD
	LASTWORD last = 0;
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
		
		const byte* Vi = H[Wir][ib] + r8 - iB;
		asm
		(
			    "movups    (%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm0"
#if r >= 256
			"\n\tmovups  16(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm1"
#endif
#if r >= 384
			"\n\tmovups  32(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm2"
#endif
#if r >= 512
			"\n\tmovups  48(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm3"
#endif
#if r >= 640
			"\n\tmovups  64(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm4"
#endif
#if r >= 768
			"\n\tmovups  80(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm5"
#endif
#if r >= 896
			"\n\tmovups  96(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm6"
#endif
#if r >= 1024
			"\n\tmovups 112(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm7"
#endif
#if r >= 1152
			"\n\tmovups 128(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm8"
#endif
#if r >= 1280
			"\n\tmovups 144(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm9"
#endif
#if r >= 1408
			"\n\tmovups 160(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm10"
#endif
#if r >= 1536
			"\n\tmovups 176(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm11"
#endif
#if r >= 1664
			"\n\tmovups 192(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm12"
#endif
#if r >= 1792
			"\n\tmovups 208(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm13"
#endif
#if r >= 1920
			"\n\tmovups 224(%0), %%xmm15"
			"\n\txorps  %%xmm15, %%xmm14"
#endif
			:
			: "r"(Vi)
		);
#ifdef LASTWORD
		last ^= *(LASTWORD*)(Vi + r/128*16);
#endif
	}
	asm
	(
		    "movups %%xmm0,    (%0)"
#if r >= 256
		"\n\tmovups %%xmm1,  16(%0)"
#endif
#if r >= 384
		"\n\tmovups %%xmm2,  32(%0)"
#endif
#if r >= 512
		"\n\tmovups %%xmm3,  48(%0)"
#endif
#if r >= 640
		"\n\tmovups %%xmm4,  64(%0)"
#endif
#if r >= 768
		"\n\tmovups %%xmm5,  80(%0)"
#endif
#if r >= 896
		"\n\tmovups %%xmm6,  96(%0)"
#endif
#if r >= 1024
		"\n\tmovups %%xmm7, 112(%0)"
#endif
#if r >= 1152
		"\n\tmovups %%xmm8, 128(%0)"
#endif
#if r >= 1280
		"\n\tmovups %%xmm9, 144(%0)"
#endif
#if r >= 1408
		"\n\tmovups %%xmm10, 160(%0)"
#endif
#if r >= 1536
		"\n\tmovups %%xmm11, 176(%0)"
#endif
#if r >= 1664
		"\n\tmovups %%xmm12, 192(%0)"
#endif
#if r >= 1792
		"\n\tmovups %%xmm13, 208(%0)"
#endif
#if r >= 1920
		"\n\tmovups %%xmm14, 224(%0)"
#endif
		:
		: "r"(out)
	);
#ifdef LASTWORD
	*(LASTWORD*)(out8 + r/128*16) = last;
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
