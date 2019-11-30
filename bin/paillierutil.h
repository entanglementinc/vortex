/*
 * add.h

 */

#ifndef ADD_H_
#define ADD_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

long long int gcd(long long int a, long long int b);
long long int modPow(long long int base, long long int exp, long long int modulus);
long long int modInv(long long int a, long long int b);
long long int Encryption(long long int g, long long int m, long long int nsquare, long long int n, long long int r);
long long int Decryption(long long int g, long long int lambda, long long int c, long long int nsquare, long long int n);
long long int createRandom(const int len);
long long int findLargePrime(const int len);

bool Miller(long long int p);

#endif /* ADD_H_ */
