/*
Copyright (c) 2019 Entanglement Incorporated

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

Subject to the terms and conditions of this license, each copyright holder and contributor hereby grants to those receiving rights under this license a perpetual, worldwide, non-exclusive, no-charge, royalty-free, irrevocable (except for failure to satisfy the conditions of this license) patent license to make, have made, use, offer to sell, sell, import, and otherwise transfer this software, where such license applies only to those patent claims, already acquired or hereafter acquired, licensable by such copyright holder or contributor that are necessarily infringed by:

(a) their Contribution(s) (the licensed copyrights of copyright holders and non-copyrightable additions of contributors, in source or binary form) alone; or

(b) combination of their Contribution(s) with the work of authorship to which such Contribution(s) was added by such copyright holder or contributor, if, at the time the Contribution is added, such addition causes such combination to be necessarily infringed. The patent license shall not apply to any other combinations which include the Contribution.

Except as expressly stated above, no rights or licenses from any copyright holder or contributor is granted under this license, whether expressly, by implication, estoppel or otherwise.

DISCLAIMER

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include<bits/stdc++.h> 
using namespace std; 


long int exponentiation(long int base, 
                        long int exp, long int c, int N) 
{ 
    if (exp == 0) 
        return 1; 
  
    if (exp == 1) 
        return base*c % N; 
  
    long int t = exponentiation(base, exp / 2, c, N); 
    t = (t * t) % N; 
  
    // if exponent is even value 
    if (exp % 2 == 0) 
        return t; 
  
    // if exponent is odd value 
    else
        return ((base*c % N) * t) % N; 
}


int powmod(long int x, long int c, long int y, long int p) 
{ 
	int res = 1; // Initialize result 

	x = x % p; // Update x if it is more than or 
				// equal to p 

	c = c % p;
	while (y > 0) 
	{ 
		// If y is odd, multiply x with result 
		if (y & 1) 
			res = (res*x*c) % p; 

		// y must be even now 
		y = y>>1; // y = y/2 
		x = (x*x) % p; 
		c = (c*c) % p;
	} 
	return res; 
} 

// Function to calculate k for given a, b, m 
int discreteLogarithm(long int a,  long int b, long int c, long int m) { 

	int n = (int) sqrt (m) + 1; 

	unordered_map<int, int> value; 

	// Store all values of a^(n*i) of LHS 
	for (int i = n; i >= 1; --i) 
		value[ powmod (a, c, i * n, m) ] = i; 

	for (int j = 0; j < n; ++j) 
	{ 
		// Calculate (a ^ j) * b and check 
		// for collision 
		int cur = (powmod (a, c, j, m) * b) % m; 

		// If collision occurs i.e., LHS = RHS 
		if (value[cur]) 
		{ 
			int ans = value[cur] * n - j; 
			// Check whether ans lies below m or not 
			if (ans < m) 
				return ans; 
		} 
	} 
	return -1; 
}
int gcd(long int a, long int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} 
  
// Function to find gcd of array of 
// numbers 
int findGCD(long int arr[], int n) 
{ 
    int result = arr[0]; 
    for (int i = 1; i < n; i++) 
        result = gcd(arr[i], result); 
  
    return result; 
} 
  int prime(double  n) 
{ 
    // Corner case 
    if (n <= 1) 
        return 0; 
  
    // Check from 2 to n-1 
    for (double i = 2; i < n; i++) 
      if ((int)n % (int)i == 0) 
	  return  1;
	      
    return 0;
} 

int * generate_prime(int n)
{
  int *output=(int*)malloc(n);
  int i, count, c;
  for ( count = 2 ; count <= n ;  )
   {
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 )
            break;
      }
      if ( c == i )
      {
         printf("%d\n",i);
	 output[count]=i;
		 
         count++;
      }
      i++;
   }
  return output;
}
 int generate(int seed)
{
  srand(seed);
 
  
  int data;
  int payload;
  int a=0;
  int b=0;
  int e=0;
  int m=0;
  int n;

  std::clock_t start;
  double duration;

  start = std::clock();

  while(gcd(a, m)!=1||prime(a)!=1||prime(b)!=1||prime(e)!=1||prime(m)!=1||a<=0||m<=0||data!=a)
    {
      
      int lower = 1;
      int upper = 10000;
      int a = rand() % (upper - lower) + lower;
      int b = rand() % (upper - lower) + lower;
      int e = rand() % (upper - lower) + lower;
      int m = rand() % (upper - lower) + lower;
      int c = rand() % (upper - lower) + lower;
      n=b*e;
      
      
	  payload = discreteLogarithm(a, b, c, m);
	  data = exponentiation(payload, b, c, m);

	  // printf("a=%d    data=%d    b=%d    e=%d    m=%d\n", a, data, b, e, m);
	  if(data==a){printf("[SUCCESS]data=%d    p=%d  public=%d    m=%d\n", data, a, n, m);}
	  
   
    
	}

     
  return 0;
}

// Driver code 
int main() 
{
  generate(rand());
  
} 
