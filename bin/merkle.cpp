#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>

bool is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} 
  
// Function to find gcd of array of 
// numbers 
int findGCD(int q, int r, int q1, int r1) 
{
  int n=4;
  int arr[4];
  arr[0]=q;
  arr[1]=r;
  arr[2]=q1;
  arr[3]=r1;
    int result = arr[0]; 
    for (int i = 1; i < n; i++) 
        result = gcd(arr[i], result); 
  
    return result; 
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int hcf(int a, int h)
{
int temp;
while(1)
{
temp = a%h;
if(temp==0)
return h;
a = h;
h = temp;
}
}
int modInverse(int a, int m)
{
int x;
a %= m;
for( x = 1; x < m; x++) {
if((a*x) % m == 1)
return x;
}
}
int phi(int num)
{
int result = num,p;
for ( p=2; p*p<=num; ++p)
{
if (num % p == 0)
{
while (num % p == 0)
num /= p;
result -= result / p;
}
}
if (num > 1)
result -= result / num;
return result;
}
int power(int x, unsigned int y, int p)
{
int res = 1;
x = x % p;
while (y > 0)
{
if (y & 1)
res = (res*x) % p;
y = y>>1;
x = (x*x) % p;
}
return res;
}
int prime(int q)
{
int i,flag;
for(i=2; i<=q/2; ++i)
{
if(q%i==0)
{
flag=1;
break;
}
}
if (flag==0)
  printf("%d is a prime number.\n",q);
 return 1;
}

int main()
{
  int no,i=0;
  printf("Merkle-Hellman Cryptosystem (Proposed System)\n\nKey Generation:\nSuper-Increasing Subset\n");
  printf("\nEnter the No.of.Element:");
  scanf("%d",&no);
  printf("\n\n");
  int w[no],temp=0,sumofw,q,flag=0,gcd,r,pk;
  for(i=0;i<no;i++)
    {
      printf("Enter the Element-%d: ",i+1);
      scanf("%d",&pk);
      if(pk>=temp)
	{
	  w[i]=pk;
	  temp=temp+pk;
	}
      else
	{
	  printf("\nError in Superincreasing subset");
	  exit(0);
	}
    }
  temp=0;
  for(i=0;i<no;i++)
    {
      temp=temp+w[i];
    }
  sumofw=temp;
  printf("\nThe Sum of W: %d",sumofw);
  printf("\nEnter the Prime Number > %d as q: ",sumofw);
 
  if(q>sumofw)
    {
      
      while(1!=prime(q))
	q=rand();
      
    }
  else
    {
printf("\nq value is invalid please enter q>%d",sumofw);
 exit(0);
    }
  printf("\n\nEnter the value of r in range of (1-%d): ",q);
  
  
  while(1!=hcf(q,r)&&prime(q)!=1&&prime(r)!=1)
    {
      q=rand();
      r=rand();
      gcd=hcf(q,r);
    }
 
  if(gcd==1)
    {
      printf("%d and %d are Coprimes\n\n",q,r);
    }
  else
    {
      printf("%d and %d are not coprimes\n\n",q,r);
      exit(0);
    }
  int b[no];
for(i=0;i<no;i++)
  {
    b[i]=(w[i]*r)%q;
  }
 printf("\nThe Private Key is: ");
for(i=0;i<no;i++)
  {
    printf("%d\t",w[i]);
  }
 printf("\nThe Public Key is: ");
for(i=0;i<no;i++)
  {
    printf("%d\t",b[i]);
  }
 int n,d,e,p1,p2,gcd1,gcd2;
 printf("\n\n\nEnter any two prime number for Security Encryption:\n");
 
 while(!prime(p1))
   p1=rand();
 while(!prime(p2))
   p2=rand();

 printf("%d  %d", p1 ,p2);
n=p1*p2;
printf("\nEnter the value of e:");
scanf("%d",&e);
int coprime1,coprime2;
 while(coprime1!=1)
   coprime1=hcf(p1,e);
 while(coprime2!=1)
   coprime2=hcf(p2,e);
int coprimes=0;
if(coprime1==1 && coprime2==1)
{
printf("\n%d, %d and %d are Coprimes\n\n",e,p1,p2);
coprimes=1;
}
else
{
printf("\n%d, %d and %d are not coprimes\n\n",e,p1,p2);
exit(0);
}
if(coprimes==1)
{
gcd1=e,gcd2=n;
while(gcd1!=gcd2)
{
if(gcd1 > gcd2)
gcd1 -= gcd2;
else
gcd2 -= gcd1;
}
if(gcd1==1)
{
	d=modInverse(e,phi(n));
}
else
{
printf("\n The Value of e is invalid");
}
}
printf("\nThe value of e: %d",e);
printf("\nThe value of d: %d",d);
printf("\nThe value of n: %d",n);
printf("\n------------------------------------------------------------------------------------------------------------------");
//Encryption
printf("\n\nEncryption:");
int txtsize;
printf("\n\nEnter the Size of Plain Text: ");
scanf("%d",&txtsize);
int plaintxt[txtsize],pltxt;
temp=0;
for(i=0;i<txtsize;i++)
{
printf("Enter the Plain Text Element-%d: ",i+1);
scanf("%d",&pltxt);
if(pltxt==0 || pltxt==1)
{
plaintxt[i]=pltxt;
}
else
{
printf("\nError in Plaintext");
exit(0);
}
}
printf("\nThe Plain text: ");
for(i=0;i<txtsize;i++)
{
printf("%d ",plaintxt[i]);
}
for(i=0;i<txtsize;i++)
{
temp=temp+(plaintxt[i]*b[i]);
}
int ciphertxt;
ciphertxt=power(temp,e,n);
printf("\nReal Cipher Text: %d",temp);
printf("\nCipher Text(%d^%d Mod %d) :%d",temp,e,n,ciphertxt);
printf("\n------------------------------------------------------------------------------------------------------------------");
//Decryption
printf("\n\nDecryption:\n\n");
printf("\nCipher Text: %d",ciphertxt);
temp=ciphertxt;
ciphertxt=power(ciphertxt,d,n);
printf("\nReal Ciphertext(%d^%d Mod %d): %d",temp,d,n,ciphertxt);
int rinv=modInverse(r,q);
printf("\nThe Inverse of R (%d): %d",r,rinv);
int decipher,deciphertxt[txtsize];
decipher=ciphertxt*rinv%q;
printf("\nThe value of Decryption: %d",decipher);
for(i=(no-1);i>0;i--)
{
if(w[i]==0)
{
deciphertxt[i]=0;
}
else if(decipher>=w[i])
{
decipher=decipher-w[i];
deciphertxt[i]=1;
}
else
{
deciphertxt[i]=0;
}
deciphertxt[0]=plaintxt[0];
}
printf("\nThe Decrypted cipher text: ");
for(i=0;i<txtsize;i++)
{
printf("%d ",deciphertxt[i]);
}
}
