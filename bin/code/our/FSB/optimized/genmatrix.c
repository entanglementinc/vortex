#include <string.h>
#include <stdio.h>

typedef unsigned long long int word;
#define WORDSIZE 8
#define LVEC8 (p8+r8)
#define LVECW (LVEC8 % WORDSIZE == 0 ? LVEC8/WORDSIZE : LVEC8/WORDSIZE+1)

#include "params.h"
#define b   (n/r)                      // number of submatrices
#define p8  (p%8 == 0 ? p/8 : p/8 + 1) // initial vector size (in bytes)
#define pm8 (p%8)                      // 8 bit alignment
#define r8  (r/8)                      // final vector size (in bytes)

typedef unsigned char byte;
extern const unsigned char Pi[1024*472];
int main()
{
	// I prefer computing all what is to be printed, to alievate the printing process itself
	byte H[b][8][LVEC8];
	
	const byte* curPi = Pi;
	// each of the b cyclic matrices is stored as its first column
	for (unsigned int i = 0; i < b; i++)
	{
		// just the non-shifted p length vector
		memcpy(H[i][0], curPi, p8);
		
		// computes its 7 other bit cyclic shifts
		for (unsigned int S = 1; S < 8; S++)
		{
			byte* Vip = H[i][S-1];
			byte* Vi =  H[i][S];
			Vi[0] = (Vip[0] >> 1) | ( (Vip[p8-1] & (0xFF<<(8-pm8))) << (pm8-1));
			for (unsigned int j = 1; j < p8; j++)
				Vi[j] = (Vip[j] >> 1) | (Vip[j-1] << 7);
		}
		curPi += p8;
	}
	
	// copy the end at the front of the vector, in order to faster the hash computing
	// NB: I know it's not very effective but it's easier to maintain and does not belong to the actuel hashing programm
	for (unsigned int i = 0; i < b; i++)
		for (unsigned int S = 0; S < 8; S++)
		{
			// "frees" the first r8 bytes
			memmove(H[i][S] + r8, H[i][S], p8);
			
			// copy the bytes
			byte* Vi = H[i][S] + p8-1;
			for (unsigned int j = 0; j < r8; j++)
				H[i][S][j] = (Vi[j] << pm8) | (Vi[j+1] >> (8-pm8));
		}
	
	printf("const unsigned long long int H[%u][8][%u] =\n", b, LVECW);
	printf("{\n");
	for (unsigned int i = 0; i < b; i++)
	{
		printf("	{\n");
		for (unsigned int S = 0; S < 8; S++)
		{
			printf("		{");
			for (unsigned int j = 0; j < LVEC8; j+=8)
			{
				byte B0 = H[i][S][j];
				byte B1 = j + 1 < LVEC8 ? H[i][S][j+1] : 0;
				byte B2 = j + 2 < LVEC8 ? H[i][S][j+2] : 0;
				byte B3 = j + 3 < LVEC8 ? H[i][S][j+3] : 0;
				byte B4 = j + 4 < LVEC8 ? H[i][S][j+4] : 0;
				byte B5 = j + 5 < LVEC8 ? H[i][S][j+5] : 0;
				byte B6 = j + 6 < LVEC8 ? H[i][S][j+6] : 0;
				byte B7 = j + 7 < LVEC8 ? H[i][S][j+7] : 0;
				printf("0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X, ", B7, B6, B5, B4, B3, B2, B1, B0);
			}
			printf("},\n");
		}
		printf("	},\n");
	}
	printf("};\n");
	
	return 0;
}
