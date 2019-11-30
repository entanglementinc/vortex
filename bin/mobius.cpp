// CPP Program to evaluate Mobius Function 
// M(N) = 1 if N = 1 
// M(N) = 0 if any prime factor of N is contained twice 
// M(N) = (-1)^(no of distinct prime factors) 
#include<iostream> 
using namespace std; 

// Function to check if n is prime or not 
bool isPrime(int n) 
{ 
	if (n < 2) 
		return false; 
	for (int i = 2; i * i <= n; i++) 
		if (n % i == 0) 
			return false;	 
	return true; 
} 

int mobius(int N) 
{ 
	// Base Case 
	if (N == 1) 
		return 1; 

	// For a prime factor i check if i^2 is also 
	// a factor. 
	int p = 0; 
	for (int i = 1; i <= N; i++) { 
		if (N % i == 0 && isPrime(i)) { 

			// Check if N is divisible by i^2 
			if (N % (i * i) == 0) 
				return 0; 
			else

				// i occurs only once, increase f 
				p++; 
		} 
	} 

	// All prime factors are contained only once 
	// Return 1 if p is even else -1 
	return (p % 2 != 0)? -1 : 1; 
} 

// Driver code 
int main() 
{ 
	int N = 17; 
	cout << "Mobius Functions M(N) at N = " << N << " is: "
		<< mobius(N) << endl; 
	cout << "Mobius Functions M(N) at N = " << 25 << " is: "
		<< mobius(25) << endl; 
	cout << "Mobius Functions M(N) at N = " << 6 << " is: "
		<< mobius(6) << endl; 
} 
