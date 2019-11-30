
#include <string.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


char* intToString(int i, char b[])
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

long long int gcd( long long int a, long long int b )
{
      long long int c;

      while ( a != 0 )
      {
             c = a;
             a = b%a;
             b = c;
      }

      return b;
}

long long int modPow(long long int base, long long int exp, long long int modulus)
{
    long long int result = 1;

    while(exp >=1)
    {
         if(exp%2 == 1)
         {
             result = (result*base ) % modulus;
         }

         base = (base*base) % modulus;
         exp = exp/2;
    }


    return result;
}

long long int modInv(long long int a, long long int b)
{
        long long int b0 = b, t, q;
        long long int x0 = 0, x1 = 1;
        if (b == 1)
            return 1;
        while (a > 1) {
            q = a / b;
            t = b, b = a % b, a = t;
            t = x0, x0 = x1 - q * x0, x1 = t;
        }

        if (x1 < 0) x1 += b0;

        return x1;
}

long long int Encryption(long long int g, long long int m, long long int nsquare, long long int n,  long long int r)
{
     return modPow(g, m, nsquare) * modPow(r, n, nsquare);
            // g^m mod n^2		   *   r^n mod n^2
}

long long int Decryption(long long int g, long long int lambda, long long int c, long long int nsquare, long long int n)
{
     long long int u = modInv(((modPow(g, lambda, nsquare)-1) / n), n);

     return (((modPow(c, lambda, nsquare)-1) / n)* u) % n;
             // g^m mod n^2		   *   r^n mod n^2
}

long long int createRandom(const int keyLength)
{
	const int dwLength = 1;
	unsigned char pbBuffer[dwLength] = {0};

	char* s = (char *) malloc(sizeof(char) * (keyLength + 1));
	s[0] = '\0';

	short int keySize = 0;

	do{
		rand();

		int a = static_cast<int>(pbBuffer[0]);
		int lengthOfInt =  floor(log10(abs(a))) + 1;
		char* s2 = (char *) malloc(sizeof(char) * (lengthOfInt ));
		char* c = intToString(a, s2);
		//cout  << c << endl;
		if((strlen(s)+lengthOfInt) < keyLength)
		{
			strcat(s, s2);
		}
		else
		{
			int x = keyLength - strlen(s);
			memcpy( c, &c[0], x);
			c[x] = '\0';
			//cout  << c << endl;
			strcat(s, c);
		}

		keySize = lengthOfInt + keySize;
	}while(keyLength > keySize);

	cout  <<"sss "<< strlen(s) << " aaa "<< s << endl;

return s;
}

long long int findLargePrime(const int len)
{
	cout<<"================"<<endl;
	long long int p = createRandom(len);
	do
	{
		p = p +1;
		//cout<<"prime candidate :" <<p<<endl;
	}while (!Miller(p));

	return p;
}

long long int mulmod(long long int a, long long int b, long long int mod)
{
    long long int x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

bool Miller(long long int p)
{
	int iteration = 5;
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    long long int s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
    	long long int tt = rand();
        long long int a = tt % (p - 1) + 1, temp = s;
        long long int mod = modPow(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}
