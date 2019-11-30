/*
 For convenience, it is assumed that:
  * s/w = 16;
  * s and c are multiples of 8.
*/

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "params.h"
#define b (n/s)                       // number of submatrices
#define p8 (p%8 == 0 ? p/8 : p/8 + 1) // lenght of the virtual vectors (in bytes)
#define pm8 (p%8)                     // 8 bit alignment
#define s8 (s/8)                      // state size (in bytes)
#define c8 (c/8)                      // sponge capacity (in bytes)
#define r (s-c)                       // message block size (in bits)
#define r8 (r/8)                      // message block size (in bytes)

typedef unsigned char byte;
extern byte H[b][8][p8+s8];

void update(byte in[s8], byte out[s8])
{
	static int block = 0;
	printf("== Block %u ==\n", block++);
	
	for (unsigned int i = 0; i < r8; i++)
		in[i] ^= out[i];
	memcpy(in+r8, out+r8, s8-r8);
	
	// computes the sum
	memset(out, 0, s8);
	for (unsigned int i = 0; i < w; i++)
	{
		unsigned int Wi = i*n/w + (in[2*i] << 8) + in[2*i+1];
		
		unsigned int Wis = Wi/s;  // vector id
		unsigned int mWis = Wi%s; // shift
		unsigned int iB = mWis/8; // byte part of the shift
		unsigned int ib = mWis%8; // bit part of the shift
		
		byte* Vi = (byte*)(H[Wis][ib] + s8 - iB);
		// adds Vi
		for (unsigned int j = 0; j < s8; j++)
			out[j] ^= Vi[j];
		
		printf("Step %.3u: ", i);
		for (unsigned int j = 1; j <= s8; j++)
			printf("%.2X", out[s8-j]);
		printf("\n");
	}
	printf("\n");
}
int main(int argc, char** argv)
{
	byte in[s8];
	byte out[s8];
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
	in[lastRead] = 0x80;
	if (lastRead >= r8-8)
	{
		memset(in+lastRead+1, 0, r8-lastRead-1);
		update(in, out);
		lastRead = 0;
		in[0] = 0;
	}
	memset(in+lastRead+1, 0, r8-lastRead-9);
	unsigned int len = databitlen << 3;
	for (unsigned int i = 1; i <= 8; i++)
	{
		in[r8-i] = len;
		len >>= 8;
	}
	update(in, out);
	
	// output
	printf("%s: ", argc > 1 ? argv[1] : "Standard input");
	for (unsigned int j = 0; j < hashlen/8; j++)
		printf("%.2x", out[j]);
	printf("\n");
	
	return 0;
}
