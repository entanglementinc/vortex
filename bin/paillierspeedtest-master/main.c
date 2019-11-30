#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include "paillier.h"

#define NUM 1000

int main() {
	
	paillier_pubkey_t *pubkey;
	paillier_prvkey_t *privkey;
	paillier_ciphertext_t ciphertext1[NUM];
	paillier_ciphertext_t ciphertext2[NUM];
	paillier_ciphertext_t ciphertext3[NUM];
	paillier_plaintext_t** input1 = malloc(NUM*sizeof(paillier_plaintext_t* ));
	paillier_plaintext_t** input2 = malloc(NUM*sizeof(paillier_plaintext_t* ));
	paillier_plaintext_t output[NUM];

	printf("Generating 2048 bit key\n");

	// Generate 2048 bit keys
	paillier_keygen(2048, &pubkey, &privkey, &paillier_get_rand_devurandom);

	printf("Allocating memory\n");

	size_t i = 0;
	for(i=0; i<NUM; i++) {
		input1[i] = paillier_plaintext_from_ui(i);
		input2[i] = paillier_plaintext_from_ui(i+1);
		mpz_init(ciphertext1[i].c);
		mpz_init(ciphertext2[i].c);
		mpz_init(ciphertext3[i].c);
		mpz_init(output[i].m);
	}


	// Do the encryptions
	printf("Doing %d encryptions\n", NUM*2);
	clock_t start = clock(), diff;

	for(i=0; i<NUM; i++) {
		paillier_enc(&ciphertext1[i], pubkey, input1[i], &paillier_get_rand_devurandom);
		paillier_enc(&ciphertext2[i], pubkey, input2[i], &paillier_get_rand_devurandom);
	}

	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Done %d encryptions in %d miliseconds\n", 2*NUM, msec);


	// Do the multiplications, 1000 times NUM because it is much faster
	printf("Doing %d multiplications\n", 1000*NUM);
	start = clock();

	size_t j = 0;
	for(i=0; i<NUM; i++) {
		for(j=0; j<1000; j++) {
			paillier_mul(pubkey, &ciphertext3[i], &ciphertext1[i], &ciphertext2[i]);
		}
	}
	
	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Done %d multiplications in %d miliseconds\n", 1000*NUM, msec);

	printf("Doing %d decryptions\n", NUM);
	start = clock();

	for(i=0; i<NUM; i++) {
		paillier_dec(&output[i], pubkey, privkey, &ciphertext3[i]);
	}

	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Done %d decryptions in %d miliseconds\n", NUM, msec);
	

	// Check if the homomorphic addition and decryption are correct
	printf("Checking decryptions\n");

	for(i=0; i<NUM; i++) {
		int res = mpz_get_ui(output[i].m);
		if (res != i+i+1) {
			printf("Result: %d (ERROR)\n", res);
		}
	}
	return 0;
}