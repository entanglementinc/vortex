#include <assert.h>
#include <string.h>
#include <stdio.h>

#define asm __asm

typedef unsigned long long int word;
#define WORDSIZE 8
#define NWORDS (s8 % WORDSIZE == 0 ? s8/WORDSIZE : s8/WORDSIZE+1)
#define LVEC8 (p8+s8)
#define LVECW (LVEC8 % WORDSIZE == 0 ? LVEC8/WORDSIZE : LVEC8/WORDSIZE+1)
#define in8  ((byte*)in)
#define out8 ((byte*)out)

#include "params.h"
#define b (n/s)                       // number of submatrices
#define p8 (p%8 == 0 ? p/8 : p/8 + 1) // lenght of the virtual vectors (in bytes)
#define pm8 (p%8)                     // 8 bit alignment
#define s8 (s/8)                      // state size (in bytes)
#define c8 (c/8)                      // sponge capacity (in bytes)
#define r (s-c)                       // message block size (in bits)
#define r8 (r/8)                      // message block size (in bytes)
#define r8w (r8 % WORDSIZE == 0 ? r8 / WORDSIZE : r8 / WORDSIZE + 1)

typedef unsigned char byte;
extern byte H[b][8][LVECW*WORDSIZE];

inline void update(word in[NWORDS], word out[NWORDS])
{
	for (unsigned int i = 0; i < r8w; i++)
		in[i] ^= out[i];
	memcpy(in8+r8, out8+r8, s8-r8);
	
	asm
	(
		    "xorps %xmm0, %xmm0"
#if s >= 256
		"\n\txorps %xmm1, %xmm1"
#endif
#if s >= 384
		"\n\txorps %xmm2, %xmm2"
#endif
#if s >= 512
		"\n\txorps %xmm3, %xmm3"
#endif
#if s >= 640
		"\n\txorps %xmm4, %xmm4"
#endif
#if s >= 768
		"\n\txorps %xmm5, %xmm5"
#endif
#if s >= 896
		"\n\txorps %xmm6, %xmm6"
#endif
	);
#if (s % 128) == 8
#define LASTWORD unsigned char
#endif
#if (s % 128) == 16
#define LASTWORD unsigned short int
#endif
#if (s % 128) == 32
#define LASTWORD unsigned int
#endif
#if (s % 128) == 64
#define LASTWORD unsigned long long int
#endif
#ifdef LASTWORD
	LASTWORD last = 0;
#endif
	
	byte* curB = in8;
	unsigned int curIndexShift = 0;
	for (unsigned int i = 0; i < w; i++)
	{
		unsigned int Wi = curIndexShift + (*curB << 8);
		curB++;
		Wi += *curB;
		curB++;
		curIndexShift += n / w;
		unsigned int Wis = Wi/s;  // vector id
		unsigned int mWis = Wi%s; // shift
		unsigned int iB = mWis/8; // byte part of the shift
		unsigned int ib = mWis%8; // bit part of the shift
		
		const byte* Vi = H[Wis][ib] + s8 - iB;
		asm
		(
			    "movups   (%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm0"
#if s >= 256
			"\n\tmovups 16(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm1"
#endif
#if s >= 384
			"\n\tmovups 32(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm2"
#endif
#if s >= 512
			"\n\tmovups 48(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm3"
#endif
#if s >= 640
			"\n\tmovups 64(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm4"
#endif
#if s >= 768
			"\n\tmovups 80(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm5"
#endif
#if s >= 896
			"\n\tmovups 96(%0), %%xmm7"
			"\n\txorps  %%xmm7, %%xmm6"
#endif
			:
			: "r"(Vi)
		);
#ifdef LASTWORD
		last ^= *(LASTWORD*)(Vi + s/128*16);
#endif
	}
	asm
	(
		    "movups %%xmm0,   (%0)"
#if s >= 256
		"\n\tmovups %%xmm1, 16(%0)"
#endif
#if s >= 384
		"\n\tmovups %%xmm2, 32(%0)"
#endif
#if s >= 512
		"\n\tmovups %%xmm3, 48(%0)"
#endif
#if s >= 640
		"\n\tmovups %%xmm4, 64(%0)"
#endif
#if s >= 768
		"\n\tmovups %%xmm5, 80(%0)"
#endif
#if s >= 896
		"\n\tmovups %%xmm6, 96(%0)"
#endif
		:
		: "r"(out)
	);
#ifdef LASTWORD
	*(LASTWORD*)(out8 + s/128*16) = last;
#endif
}
int main(int argc, char** argv)
{
	word in[NWORDS];
	word out[NWORDS];
	memset(out, 0, s8); // IV
	
	FILE* f = argc > 1 ? fopen(argv[1], "r") : stdin;
	assert(f);
	unsigned long long int databitlen = 0;
	while (1)
	{
		databitlen += fread(in, 1, r8, f);
		if (feof(f))
			break;
		update(in, out);
	}
	fclose(f);
	
	// padding handling
	unsigned int long long lastRead = databitlen % r8;
	in8[lastRead] = 0x80;
	if (lastRead >= r8-8)
	{
		memset(in8+lastRead+1, 0, r8-lastRead-1);
		update(in, out);
		lastRead = 0;
		in8[0] = 0;
	}
	memset(in8+lastRead+1, 0, r8-lastRead-9);
	unsigned int len = databitlen << 3;
	for (unsigned int i = 1; i <= 8; i++)
	{
		in8[r8-i] = len;
		len >>= 8;
	}
	update(in, out);
	
	// output
	printf("%s: ", argc > 1 ? argv[1] : "Standard input");
	for (unsigned int j = 0; j < hashlen/8; j++)
		printf("%.2x", out8[j]);
	printf("\n");
	
	return 0;
}
