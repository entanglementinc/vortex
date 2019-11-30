
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include <iostream>

using namespace std;


int cal(int base, unsigned int exp, unsigned int mod)
{
int x = 1;
int i;
int power = base % mod;

for (i = 0; i < sizeof(int) * 8; i++) {
int least_sig_bit = 0x00000001 & (exp >> i);
if (least_sig_bit)
x = (x * power) % mod;
power = (power * power) % mod;
}

return x;
}
int rndpu(int i)
{
i=rand()%10;
return i;
}
int rndpr(int j)
{
j=rand()%20;
return j;
}

void encrypt(char msg[], char msge[], int key[])
{strcpy(msge, msg);
char ch;
int i;

for(i = 0; msge[i] != '\0'; ++i){
ch = msge[i];

if(ch >= 'a' && ch <= 'z'){
ch = ch + key[i];

if(ch > 'z'){
ch = ch - 'z' + 'a' - 1;
}

msge[i] = ch;
}
else if(ch >= 'A' && ch <= 'Z'){
ch = ch + key[i];

if(ch > 'Z'){
ch = ch - 'Z' + 'A' - 1;
}

msge[i] = ch;
}
else if(ch >= '0' && ch <= '9')
{
ch= ch + key[i];
if(ch > '9')
{
ch=ch-'9'+'0'-1;
}

msge[i] = ch;
}


}




}


//-----------------------------------------------------

void decrypt(char msge[], char msgd[], int key[])
{strcpy(msgd,msge);
char ch;
int i;


for(i = 0; msgd[i] != '\0'; ++i){
ch = msgd[i];

if(ch >= 'a' && ch <= 'z'){
ch = ch - key[i];

if(ch < 'a'){
ch = ch + 'z' - 'a' + 1;
}

msgd[i] = ch;
}
else if(ch >= 'A' && ch <= 'Z'){
ch = ch - key[i];

if(ch > 'a'){
ch = ch + 'Z' - 'A' + 1;
}

msgd[i] = ch;
}
else if(ch >= '0' && ch <= '9')
{
ch= ch - key[i];
if(ch < '0')
{
ch=ch+'9'-'0'+1;
}

msgd[i] = ch;
}
}

}





int main()
{int randnum;
unsigned int seedval;
time_t t;
seedval=(unsigned)time(&t);
srand(seedval);
//test code
/*cout<<cal(123, 456, 567)<<"\n";
int j,k;
for(int i=0;i<40;i++)
cout<<rndpu(j)<<" "<<rndpu(k)<<"\n";
*/
int publicx[10]={2,3,5,7,11,13,17,19,23,29};
int publicy[10]={31,37,41,43,47,51,53,57,61,67};
int privatekey[20]={2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
int x,y,pra,prb,exa,exb,resulta,resultb,q;
int ra[600],rb[600],z;
//z decides size of msg
for(z=0;z<=600;z++)
{x=publicx[rndpu(q)];
y=publicy[rndpu(q)];
pra=privatekey[rndpr(q)];
prb=privatekey[rndpr(q)];
cout<<"z "<<z<<" "<<"x "<<x<<" "<<"y "<<y<<" "<<"pra "<<pra<<" "<<"prb "<<prb;
exa=cal(x, pra, y);
exb=cal(x, prb, y);
cout<<" "<<"exa "<<exa<<" "<<"exb "<<exb;
resulta=cal(exb, pra, y);
resultb=cal(exa, prb, y);
cout<<" "<<"resulta "<<resulta<<" "<<"resultb "<<resultb<<"\n";
ra[z]=resulta;
rb[z]=resultb;
}
cout<<"-----------------------------------------------------------------";
cout<<endl;
 std::string buffer;
char msg[600],msge[600],msgd[600];
cout<<"enter msg: ";
 std::cin>>buffer;
 strcpy(msg, buffer.c_str());
cout<<"\nyour entered msg is: "<<msg;
int length,l;
l=length;
length=strlen(msg);
cout<<"\n\n"<<"msg entered by A is: "<<msg;
encrypt(msg, msge, ra);
cout<<"\n\n"<<"encrypted msg sent by A is: "<<msge;
cout<<"\n\n"<<"encrypted msg received by B is: "<<msge;
decrypt(msge, msgd, rb);
cout<<"\n\n"<<"msg decrypted by B is: "<<msgd;

return 0;
}
