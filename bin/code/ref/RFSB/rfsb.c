#include <stdio.h>
#include <string.h>
#include <assert.h>

#define crypto_hashblocks_rfsb509_xmm1_matrix matrix
#define crypto_hashblocks_rfsb509_xmm1reg_matrix matrix
#define crypto_hashblocks_rfsb509_xmm2_matrix matrix
#define crypto_hashblocks_rfsb509_xmm4_matrix matrix
//#include "xmm1.c"
#include "xmm1reg.c"
//#include "xmm2.c"
//#include "xmm4.c"

int main(int argc, char** argv)
{
	unsigned char in[48];
	unsigned char state[128] = {0};
	
	FILE* f = argc > 1 ? fopen(argv[1], "r") : stdin;
	assert(f);
	unsigned long long int databitlen = 0;
	while (1)
	{
		databitlen += fread(in, 1, 48, f);
		if (feof(f))
			break;
		crypto_hashblocks(state, in, 48);
	}
	fclose(f);
	
	unsigned int lastRead = databitlen % 48;
	if (lastRead > 40)
	{
		memset(in+lastRead, 0, 48-lastRead);
		crypto_hashblocks(state, in, 48);
		lastRead = 0;
	}
	memset(in+lastRead, 0, 40-lastRead);
	memcpy(in+40, &databitlen, 8);
	crypto_hashblocks(state, in, 48);
	
	int i;
	for (i = 1; i <= 64; i++)
		printf("%.2x", state[64-i]);
	printf("\n");
	
	return 0;
}
