/*************************************************
*	dixon.cc -- Factor any integer into primes using Dixon's random
*	squares method.
*
*	Compile: 
*	g++ -s -O4 -o fact fact.cc
*	Invoke:
*	./fact NumberToFactor
*
* ChangeLog
*  970324 -- Created by Paul Herman <a540pau@pslc.ucla.edu>
*  Future -- I want to later include the Linear Algebra routines - Paul
********************************************************/
#include <iostream>
#include <math.h>

#define max_k	20

using namespace std;

bool issquare(int x) 
{   
  // Find floating point value of  
  // square root of x. 
  int sr = sqrt(x); 
  
  // If square root is an integer 
  return ((sr - floor(sr)) == 0); 
}

int gcd(int x, int y)
{
  int gcd;
  for (int i = 1; i <= x && i <= y; i++)
   {
      if (x % i == 0 && y % i == 0)
         gcd = i;
   }
  return gcd;
}

/***************************
*	factor(Integer n)
*	Given n, try to find a factor.
****************************/
int factor(int n) {
    int x, xx, y, d, q, rt;
    int i, j;

    rt = sqrt(n);
    if (issquare(n)) return rt;
    x = rt;
    for (;;x++) {
	d = gcd(x, n);
	if (1<d && d<n) goto end;
	xx = (x*x)%n;
	if (issquare(xx)) {
		y = sqrt(xx);
		q = (x-y)%n;
		d = gcd(q, n);
		if (1<d && d<n) goto end;
		}
	}
/*	At this point the loop would stop after a few times, and then
*	we would try to construct a perfect square by expressing the
*	previous r^2 in terms of an exponent vector with
*	primes {2, 3, ..., k} as a basis, for some k.  Then row reduce
*	until I find a solution in terms of each vector with only even
*	entries.  Thus the result would also be a perfect square.
*		I hope to impliment this later. -Paul.
*/
    cout << "Giving up on the whole deal!" << endl;
    return 0;

    end:
    return d;
};

bool isprime(int n) 
{ 
    // Corner case 
    if (n <= 1) 
        return false; 
  
    // Check from 2 to n-1 
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false; 
  
    return true; 
}

int main(int argc, char *argv[]) {

    int n, f;
    char ai, *p, smart;

    if (argc < 2) {
	cerr << "Usage: " << argv[0] << " NumberToFactor" << endl;
	return 1;
    }

    n = atoi(argv[1]);
    cout << n << ": " << flush;

    if (isprime(n)) {cout << "is prime..." << endl; return 0;}

    while (!isprime(n)) {
	f = factor(n);
	cout << f << " " << flush;
	n /= f;
	}
    cout << n << endl;
    return 0;
};
