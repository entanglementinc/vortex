#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;



int FastExponention(int bit, int n, int* y, int* a)
{
	if (bit == 1)
		*y = (*y * (*a)) % n;

	*a = (*a) * (*a) % n;
}

int FindT(int a, int m, int n)
{
	int r;
	int y = 1;
	
	while (m > 0) {
		r = m % 2;
		FastExponention(r, n, &y, &a);
		m = m / 2;
	}
	
	return y;
}

int mod(int k, int b, int m)
{
    int i=0;
    int a=1;
    vector<int> t;
    while(k>0){
        t.push_back(k%2);
        k=(k-t[i])/2;
        i++;
    }
    for(int j=0; j<i; j++){
        if(t[j]==1){
            a=(a*b)%m;
            b=(b*b)%m;
        } else{
            b=(b*b)%m;
        }
    }
    return a;
}

vector<int> eea(int a, int b)
{
    if (b>a) {
        int temp=a; a=b; b=temp;
    }
    int x=0;
    int y=1;
    int lastx=1;
    int lasty=0;
    while (b!=0) {
        int q= a/b;
        int temp1= a%b;
        a=b;
        b=temp1;
        int temp2 = x;
        x=lastx-q*x;
        lastx = temp2;
        int temp3 = y;
        y = lasty-q*y;
        lasty=temp3;
    }
    vector<int>arr(3);
    arr[0] = lastx;
    arr[1] = lasty;
    arr[2] = 1;
    return arr;
}

int modulo (int a, int b)
{
    return a >= 0 ? a % b : ( b - abs ( a%b ) ) % b;
}

int decrypt(int c, int p, int q)
{
    int mp = mod((p+1)/4, c, p);
    int mq = mod((q+1)/4, c, q);
    vector<int> arr = eea(p, q);
    int pp = arr[0]*p*mq;
    int qq = arr[1]*q*mp;
    double r = modulo((pp+qq), (p*q));
    if( r < 128)
        return r;
    int negative_r = (p*q) - r;
    if (negative_r < 128)
        return negative_r;
    int s = modulo((pp-qq), (p*q));
    if( s < 128)
        return s;
    int negative_s = (p*q) - s;
    if( negative_s < 128)
        return negative_s;
}

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

int gcd(int a, int b)
{
	int q, r1, r2, r;

	if (a > b) {
		r1 = a;
		r2 = b;
	}
	else {
		r1 = b;
		r2 = a;
	}

	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;
	}

	return r1;
}

int PrimarityTest(int a, int i)
{
	int n = i - 1;
	int k = 0;
	int j, m, T;

	while (n % 2 == 0) {
		k++;
		n = n / 2;
	}

	m = n;
	T = FindT(a, m, i);

	if (T == 1 || T == i - 1)
		return 1;

	for (j = 0; j < k; j++)
	{
		T = FindT(T, 2, i);

		if (T == 1)
			return 0;

		if (T == i - 1)
			return 1;
	}

	return 0;
}


std::vector<int> generate()
{
  int p;
  int q;
  int n;
  
  do {
    do {
      p = rand() % 500;
    }
    while (!((p % 2 == 1) && (p % 4 == 3)));
  }
  while (!PrimarityTest(2, p));
  
  do {
    do {
      q = rand() % 500;
    }
    while (!((q % 2 == 1) && (q % 4 == 3)));
  }
  while (!PrimarityTest(2, q));
  
  n = p * q;
  printf("p = %d, q = %d, n = %d\n\n", p, q, n);
  
  std::vector<int> key = {n, 167, 151};
  
  return key;
}

int encrypt(int m, int n)
{
  int c = (m * m)%n;
  return c;
}
int main(int argc,  char**argv)
{
  std::vector<int> key = generate();
  int c = encrypt(atoi(argv[1]), key[0]);
  int d = decrypt(c, key[1], key[2]);

  printf("ENCRYPTING: %s with public %i\n", argv[1], key[0]);
  printf("PLAINTEXT: %i\n", d);
}
