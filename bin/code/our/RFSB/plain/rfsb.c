#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
#define R 64
#define W 112
#define C (W-R)
extern byte c[256][R];
void update(byte state[R], byte in[C])
{
	// M = state . in
	byte M[W];
	memcpy(M, state, R);
	memcpy(M+R, in, C);
	
	memset(state, 0, R);
	for (unsigned int i = 0; i < W; i++)
	{
		byte* cj = c[M[i]];
		// shift nstate
		byte nstate[R];
		for (unsigned int k = 0; k < 16; k++)
			nstate[k] = (state[48+k] << 3) | (state[47+k] >> 5);
		memcpy(&nstate[16], state, R-16);
		nstate[63] &= 0x1F;
		
		memcpy(state, nstate, R);
		
		// xor
		for (unsigned int k = 0; k < R; k++)
			state[k] ^= cj[k];
	}
}
int main(int argc, char** argv)
{
	static byte state[R] = {0};
	static byte in[C];
	
	FILE* f = argc > 1 ? fopen(argv[1], "r") : stdin;
	assert(f);
	unsigned long long int databitlen = 0;
	while (1)
	{
		databitlen += fread(in, 1, C, f);
		if (feof(f))
			break;
		update(state, in);
	}
	fclose(f);
	
	// padding handling
	unsigned int lastRead = databitlen % C;
	if (lastRead > C-8)
	{
		memset(in+lastRead, 0, C-lastRead);
		update(state, in);
		lastRead = 0;
	}
	memset(in+lastRead, 0, C-lastRead-8);
	memcpy(in+C-8, &databitlen, 8);
	update(state, in);
	
	// TODO: final (SHA256)
	
	// output
	for (unsigned int i = 1; i <= R; i++)
		printf("%.2x", state[R-i]);
	printf("\n");
	return 0;
}
