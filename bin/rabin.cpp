#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <vector>

int e = 2, n;
int p, q, p1 ,q1;

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


int KeyGeneration()
{
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
	do {
		do {
			p1 = rand() % 500;
		}
		while (!((p1 % 2 == 1) && (p1% 4 == 3)));
	}
	while (!PrimarityTest(2, p1));
	do {
		do {
			q1 = rand() % 500;
		}
		while (!((q1 % 2 == 1) && (q1 % 4 == 3)));
	}
	while (!PrimarityTest(2, q1));
	
	n = p * q * p1 * q1;
	printf("p = %d, q = %d, n = %d\n\n", p, q, n);
}

int Encryption(int PlainText)
{
	printf("PlainText is %d\n", PlainText);
	int cipher = FindT(PlainText, e, n);
	fprintf(stdout, "Cipher Text is %d\n", cipher);
	
	return cipher;
}

int inverse(int a, int b)
{
	int inv;
	int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;

	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	if (r1 == 1)
		inv = t1;
	if (inv < 0)
		inv = inv + a;

	return inv;
}

int ChineseRemainderTheorem(int a, int b, int m1, int m2)
{
	int M, M1, M2, M1_inv, M2_inv;
	int result;
 
	M = m1 * m2;
	M1 = M / m1;
	M2 = M / m2;
 
	M1_inv = inverse(m1, M1);
	M2_inv = inverse(m2, M2);
 
	result = (a * M1 * M1_inv + b * M2 * M2_inv) % M;
 
	return result;

}
int *getGCD(int a, int b )  {
  while(b != 0) {
    a, b = b, a%b;
    }
  int *set;
  set[0]=a;
  set[1]=b;
  return set;
}
int *GetGCD(int numbers[]) {
  int gdc = numbers[0];
  int *buffer;
      for (int i = 0; i < sizeof(numbers); i++ ){
      int number = numbers[i];
      buffer  = getGCD(gdc, number);
      gdc = buffer[0];
    }
    return buffer;
}
int *find_gcd(int arr[])
{
  int a;
  int b;
  int *set;
  if(sizeof(arr) <= 1)
    {
      return arr;
    }
    else{
      for(int i=0;i<sizeof(arr)-1;i++)
	{
	  a = arr[i];
	  b = arr[i+1];
	  
	    a, b = b, a%b;
           
	  
	}
      set[0]=a;
      set[1]=b;
    }
  return set;
}	   
 int gcdRecursive(int bigger, int smaller) {
  int remainder = bigger % smaller;
  if (remainder == 0) {
   return smaller;
  } else {
   return gcdRecursive(smaller, remainder);
  }
 }

int input[] = { 24, 7 ,161, 157 };
   int *euclideanalgorithm() {
  int prevgcd = input[0];
  for (int i = 1; i < sizeof(input); i++) {
   if (prevgcd > input[1]) {
    prevgcd=gcdRecursive(prevgcd, input[i]);
   }else{
    prevgcd=gcdRecursive(input[i],prevgcd);
   }
  }
  
  printf("GCD: %d\n", prevgcd);
 }
 
 
  
int Decryption(int Cipher)
{
  std::vector<int> plain;
  int P1, P2, P3, P4, P5, P6, P7, P8;
  int a1, a2, b1, b2, c1, c2, d1, d2;

	a1 = FindT(Cipher, (p + 1) / 4, p);
	a2 = p - a1;

	b1 = FindT(Cipher, (q + 1) / 4, q);
	b2 = q - b1;

	a1 = FindT(Cipher, (p1 + 1) / 4, p1);
	c2 = p1 - c1;

	b1 = FindT(Cipher, (q1 + 1) / 4, q1);
	d2 = q1 - d1;

	
	plain.push_back(ChineseRemainderTheorem(a1, b1, p, q));
	plain.push_back(ChineseRemainderTheorem(a1, b2, p, q));
	plain.push_back(ChineseRemainderTheorem(a2, b1, p, q));
	plain.push_back(ChineseRemainderTheorem(a2, b2, p, q));


	for(int x=0;x<plain.size();x++)
	  {
	    printf("PLAINTEXT: %d\n", plain[x]);
	  }
}

int main(void)
{
	int PlainText;
	KeyGeneration();

	do {
		PlainText = rand() % (n - 1) + 1; // PlainText belongs to the group Zn
	}
	while (gcd(PlainText, n) != 1); // PlainText belongs to the group Z*n

	int Cipher = Encryption(PlainText);
	Decryption(Cipher);

	int *set=GetGCD(input);
	printf("x=%d, y=%d\n", set[0], set[1]);
	return 0;
}
