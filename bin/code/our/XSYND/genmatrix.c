#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "rijndael.h"
#define KEYARCHI_ITS 128

typedef unsigned char byte;

int main()
{
	unsigned long int rk[RKLENGTH(KEYARCHI_ITS)];
	byte key[KEYLENGTH(KEYARCHI_ITS)];
	memset(key, 0, 16);
	unsigned int nrounds = rijndaelSetupEncrypt(rk, key, KEYARCHI_ITS);
	
	byte clearString[16];
	memset(clearString, 0, 16);
	byte c[256][64];
	for (unsigned int j = 0; j < 256; j++)
	{
		byte* cj = c[j];
		
		// AES crypt (0, ... 0, j, 0) .. (0, ... 0, j, 3)
		clearString[1] = j;
		for (byte k = 0; k < 4; k++)
		{
			clearString[0] = k;
			rijndaelEncrypt(rk, nrounds, clearString, cj + 16*k);
		}
		
		// folding
		cj[0] ^= cj[63] >> 5;
		cj[63] &= 0x1F;
	}
	
	printf("unsigned int c[256][16] =\n");
	printf("{\n");
	for (unsigned int j = 0; j < 256; j++)
	{
		printf("\t{");
		byte* cj = c[j];
		for (unsigned int k = 0; k < 16; k++)
			printf("0x%.2X%.2X%.2X%.2X,", cj[4*k+3], cj[4*k+2], cj[4*k+1], cj[4*k]);
		printf("},\n");
	}
	printf("};\n");
	
	return 0;
}
