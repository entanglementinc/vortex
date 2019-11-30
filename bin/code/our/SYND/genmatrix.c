#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "params.h"

extern const unsigned char Pi[1024*472];
int main(int argc, char** argv)
{
	assert(argc > 1);
	
	unsigned int PiIdx = 0;
	printf("const unsigned char %s[%u][%u] __attribute((aligned(16))) =\n", argv[1], N, R8A);
	printf("{\n");
	for (unsigned int i = 0; i < N; i++)
	{
		printf("\t{");
		if (R8 <= 32)
			for (unsigned int j = 0; j < R8; j++)
				printf("0x%.2X,", Pi[PiIdx++]);
		else
		{
			printf("\n");
			unsigned int j = 0;
			while (j < R8)
			{
				printf("\t\t");
				for (unsigned int k = 0; k < 32 && j < R8; k++, j++)
					printf("0x%.2X,", Pi[PiIdx++]);
				printf("\n");
			}
			printf("\t");
		}
		printf("},\n");
	}
	printf("};\n");
	return 0;
}
