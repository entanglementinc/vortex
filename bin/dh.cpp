/* This program calculates the Key for two persons 
using the Diffie-Hellman Key exchange algorithm */
#include<stdio.h> 
#include<math.h>



// Power function to return value of a ^ b mod P 
long long int power(long long int a, long long int b, long long int P, long long int c) 
{ 
	if (b == 1) 
		return a; 

	else
	  return (((long long int)pow(a, pow(b, c))) % P); 
} 

//Driver program 
int main() 
{ 
  long long int P, G, x, a, y, b, ka, kb, c, d; 
  c=920;
  d=720;
	// Both the persons will be agreed upon the 
		// public keys G and P 
	P = 23; // A prime number P is taken 
	printf("The value of P : %lld\n", P); 

	G = 9; // A primitve root for P, G is taken 
	printf("The value of G : %lld\n\n", G); 

	// Alice will choose the private key a 
	a = 4; // a is the chosen private key 
	printf("The private key a for Alice : %lld\n", a); 
	x = power(G, a, P, c); // gets the generated key 
	
	// Bob will choose the private key b 
	b = 3; // b is the chosen private key 
	printf("The private key b for Bob : %lld\n\n", b); 
	y = power(G, b, P, d); // gets the generated key 

	// Generating the secret key after the exchange 
		// of keys 
	ka = power(y, a, P, c); // Secret key for Alice 
	kb = power(x, b, P, c); // Secret key for Bob 
	
	printf("Secret key for the Alice is : %lld\n", ka); 
	printf("Secret Key for the Bob is : %lld\n", kb); 
	
	return 0; 
} 
