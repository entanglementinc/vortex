/*
 For convenience, it is assumed that:
   * r/w == 8;
   * (s-r)/w <= 8;
   * s and r are multiples of 8.
*/
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "whirlpool.h"

#include "params.h"
#define b   (n/r)                      // number of submatrices
#define p8  (p%8 == 0 ? p/8 : p/8 + 1) // initial vector size (in bytes)
#define pm8 (p%8)                      // 8 bit alignment
#define r8  (r/8)                      // final vector size (in bytes)
#define sr8 ((s-r)/8)                  // message block size (bytes)
#define rw  (r/w)                      // Wi size (buts) (= 8)
#define srw ((s-r)/w)                  // Mi size (bites)

typedef unsigned char byte;
extern const byte H[b][8][p8+r8]; // the first p8 bytes are a precomputed shift of the vector

void update(byte in[sr8], byte out[r8])
{
	byte IV[r8];
	memcpy(IV, out, r8); // the new 'IV' is the previous result
	
	// computes the sum into 'out'
	memset(out, 0, r8);
	byte* curIVB = IV;      // IVi (byte pointer)
	byte* curMB  = in;      // Mi (byte pointer)
	unsigned int curMb = 0; // Mi (bit shift)
	for (unsigned int i = 0; i < w; i++)
	{
		// computes Mi
		unsigned int Mi;
		if (curMb <= 8 - srw) // if it fits only on a byte
		{
			Mi = (*curMB >> (8-srw-curMb)) & (0xFF >> (8-srw));
			curMb += srw;
		}
		else // if it is split on two ones
		{
			Mi = (*curMB << (curMb+srw-8)) & (0xFF >> (8-srw));
			curMB++;
			Mi |= *curMB >> (16-srw-curMb);
			curMb += srw - 8;
		}
		unsigned int Wi = i*n/w + *curIVB + (Mi << rw);
		curIVB++;
		
		unsigned int Wir = Wi/r;  // vector id
		unsigned int mWir = Wi%r; // shift
		unsigned int iB = mWir/8; // byte part of the shift
		unsigned int ib = mWir%8; // bit part of the shift
		
		const byte* Vi = (byte*)(H[Wir][ib] + r8 - iB);
		// adds Vi
		for (unsigned int j = 0; j < r8; j++)
			out[j] ^= Vi[j];
	}
}
int main(int argc, char** argv)
{
	byte in[sr8];
	byte out[r8];
	memset(out, 0, r8); // IV
	
	FILE* f = argc > 1 ? fopen(argv[1], "r") : stdin;
	assert(f);
	unsigned long long int databitlen = 0;
	while (1)
	{
		databitlen += fread(in, 1, sr8, f);
		if (feof(f))
			break;
		update(in, out);
	}
	fclose(f);
	
	// padding handling
	unsigned long long int lastRead = databitlen % sr8;
	in[lastRead] = 0x80;
	if (lastRead >= sr8-8)
	{
		memset(in+lastRead+1, 0, sr8-lastRead-1);
		update(in, out);
		lastRead = 0;
	}
	memset(in+lastRead+1, 0, sr8-lastRead-9);
	unsigned int len = databitlen << 3;
	for (unsigned int i = 1; i <= 8; i++)
	{
		in[sr8-i] = len;
		len >>= 8;
	}
	update(in, out);
	
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
