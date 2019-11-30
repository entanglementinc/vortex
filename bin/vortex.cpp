#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdint.h>
#include <bits/stdc++.h>
#include <stdint.h>

#define ROUNDS 8192

#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"
#define MODE_ECB "ecb"
#define MODE_CBC "cbc"

enum { ACTION = 1, MODE };

uint32_t f(uint32_t block, uint32_t key);
uint64_t encrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]);
uint64_t decrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]);

void encrypt_ecb(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[]);
void decrypt_ecb(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[]);
void encrypt_cbc(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[], int affine_a, int affine_b, std::string vig_key, int len);
uint64_t *encrypt_cbc(std::string infile, uint32_t rounds, uint32_t keys[], int affine_a, int affine_b, std::string vig_key);
void decrypt_cbc(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[], std::string vig_key);
uint64_t *decrypt_cbc(std::string infile, uint32_t rounds, uint32_t keys[], std::string vig_key);

void usage(void);

static int randto(int n) {
  int r;
  int maxrand = (RAND_MAX / n) * n;
  do r = rand(); while (r >= maxrand);
  return r % n;
}

// C++ code to implement Vigenere Cipher 
#include<bits/stdc++.h> 
using namespace std; 

// This function generates the key in 
// a cyclic manner until it's length isi'nt 
// equal to the length of original text 
string generateKey(string str, string key) 
{ 
	int x = str.size(); 

	for (int i = 0; ; i++) 
	{ 
		if (x == i) 
			i = 0; 
		if (key.size() == str.size()) 
			break; 
		key.push_back(key[i]); 
	} 
	return key; 
} 

// This function returns the encrypted text 
// generated with the help of the key 
string vig_encrypt(std::string str, std::string key) 
{ 
std::string cipher_text; 

	for (int i = 0; i < str.size(); i++) 
	{ 
		// converting in range 0-25 
		int x = (str[i] + key[i]) %26; 

		// convert into alphabets(ASCII) 
		x += 'A'; 

		cipher_text.push_back(x); 
	} 
	return cipher_text; 
} 

// This function decrypts the encrypted text 
// and returns the original text 
std::string vig_decrypt(std::string cipher_text, std::string key) 
{ 
std::string orig_text; 

	for (int i = 0 ; i < cipher_text.size(); i++) 
	{ 
		// converting in range 0-25 
		int x = (cipher_text[i] - key[i] + 26) %26; 

		// convert into alphabets(ASCII) 
		x += 'A'; 
		orig_text.push_back(x); 
	} 
	return orig_text; 
} 

std::string XOR(std::string inpString) 
{ 
	// Define XOR key 
	// Any character value will work 
	char xorKey = 'P'; 

	// calculate length of input string 
int len = strlen(inpString.c_str()); 

	// perform XOR operation of key 
	// with every caracter in string 
	for (int i = 0; i < len; i++) 
	{ 
		inpString[i] = inpString[i] ^ xorKey; 
	}

	return inpString;
}

static void shuffle(unsigned *x, size_t n) {
  while (--n) {
    size_t j = randto(n + 1);
    unsigned tmp = x[n];
    x[n] = x[j];
    x[j] = tmp;
  }
}

uint16_t nrand16(int n) {
  uint16_t v = 0;
  static unsigned pos[16] = {0, 1,  2,  3,  4,  5,  6,  7,
                             8, 9, 10, 11, 12, 13, 14, 15};
  shuffle(pos, 16);
  while (n--) v |= (1U << pos[n]);
  return v;
}

uint32_t RANDOM(int n) {
  uint32_t v = 0;
  static unsigned pos[32] = { 0,  1,  2,  3,  4,  5,  6,  7,
                              8,  9, 10, 11, 12, 13, 14, 15,
                             16, 17, 18, 19, 20, 21, 22, 23,
                             24, 25, 26, 27, 28, 29, 30, 31};
  shuffle(pos, 32);
  while (n--) v |= (1U << pos[n]);
  return v;
}
	
std::string string_to_hex(std::string input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output+=lut[c >> 4];
        output+=lut[c & 15];
	
    }
    std::cout<<output<<std::endl;
    return output;
}
int main(int argc, char *argv[])
{
  
  uint32_t keys[ROUNDS];
  for(int x=0;x<ROUNDS;x++)
    {
      keys[x]=RANDOM(32);
    }

        FILE *infile, *outfile;
        /* Check argc */
        if(argc < 5) {
                fprintf(stderr,"An insufficient amount of arguments supplied\n");
                return EXIT_FAILURE;
        }
        /* Open in/out files */
        fprintf(stderr,"Trying to open file '%s' as input file\n",argv[3]);
        infile = fopen(argv[3],"r");
        if(!infile) {
                perror("fopen");
                return EXIT_FAILURE;
        }

	FILE *file=fopen(argv[3], "r");
	fseek(file, 0, SEEK_END);
	int len = (int)ftell(file);
	fclose(file);
        fprintf(stderr,"Trying to open file '%s' as output file\n",argv[4]);
        outfile = fopen(argv[4],"w");
        if(!outfile) {
                perror("fopen");
                return EXIT_FAILURE;
        }
        /* Parse cmdline */
        if(!strcmp(argv[ACTION],ACTION_ENCRYPT)) {
                if(!strcmp(argv[MODE],MODE_ECB)) {
                        encrypt_ecb(infile,outfile,ROUNDS,keys);
                } else if(!strcmp(argv[MODE],MODE_CBC)) {
		  encrypt_cbc(infile,outfile,ROUNDS,keys, 920, 720, "password", len);
                } else {
                        usage();
                }
        } else if(!strcmp(argv[ACTION],ACTION_DECRYPT)) {
                if(!strcmp(argv[MODE],MODE_ECB)) {
                        fprintf(stderr,"decrypt_ecb()\n");
                        decrypt_ecb(infile,outfile,ROUNDS,keys);
                } else if(!strcmp(argv[MODE],MODE_CBC)) {
		  decrypt_cbc(infile,outfile,ROUNDS,keys, "password");
                } else {
                        usage();
                }
        } else {
                usage();
        }
        /* Close files */
        fclose(infile);
        fclose(outfile);
        return 0;
}

std::string to_hex(char *input)
{
  std::stringstream ss;
  for(int i=0; i<sizeof(input); ++i)
    ss << std::hex << (int)input[i];
  return ss.str();
  
}
void usage(void) {
        fprintf(stderr,"NOPE.\n");
}

uint32_t f(uint32_t block, uint32_t key) {
        return block ^ key;
}

//CPP program to illustate Affine Cipher 



std::string affine_encrypt(std::string msg, int a, int b) 
{ 
	///Cipher Text initially empty 
  std::string cipher = ""; 
	for (int i = 0; i < msg.length(); i++) 
	{ 
		// Avoid space to be encrypted 
		if(msg[i]!=' ') 
			/* applying encryption formula ( a x + b ) mod m 
			{here x is msg[i] and m is 26} and added 'A' to 
			bring it in range of ascii alphabet[ 65-90 | A-Z ] */
			cipher = cipher + 
						(char) ((((a * (msg[i]-'A') ) + b) % 26) + 'A'); 
		else
			//else simply append space character 
			cipher += msg[i];	 
	} 
	return cipher; 
} 

std::string affine_decrypt(std::string cipher, int a , int b) 
{ 
  std::string msg = ""; 
	int a_inv = 0; 
	int flag = 0; 
	
	//Find a^-1 (the multiplicative inverse of a 
		//in the group of integers modulo m.) 
	for (int i = 0; i < 26; i++) 
	{ 
		flag = (a * i) % 26; 
		
		//Check if (a*i)%26 == 1, 
				//then i will be the multiplicative inverse of a 
		if (flag == 1) 
		{ 
			a_inv = i; 
		} 
	} 
	for (int i = 0; i < cipher.length(); i++) 
	{ 
		if(cipher[i]!=' ') 
			/*Applying decryption formula a^-1 ( x - b ) mod m 
			{here x is cipher[i] and m is 26} and added 'A' 
			to bring it in range of ASCII alphabet[ 65-90 | A-Z ] */
			msg = msg + 
					(char) (((a_inv * ((cipher[i]+'A' - b)) % 26)) + 'A'); 
		else
			//else simply append space characte 
			msg += cipher[i]; 
	} 

	return msg; 
} 



uint64_t encrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]) {
        uint32_t i, left1, right1;
        for(i = 0;i < rounds;i++) {
                left1 = f(left,keys[i]) ^ right;
                right1 = left;
                if(i == (rounds-1)) {
                        left = right1;
                        right = left1;
                } else {
                        left = left1;
                        right = right1;
                }
        }
        return (uint64_t)left<<32 | right;
}

uint64_t decrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]) {
        uint32_t i, left1, right1;
        for(i = 0;i < rounds;i++) {
                left1 = f(left,keys[rounds-i-1]) ^ right;
                right1 = left;
                if(i == (rounds-1)) {
                        left = right1;
                        right = left1;
                } else {
                        left = left1;
                        right = right1;
                }
        }
        return (uint64_t)left<<32 | right;
}

void encrypt_ecb(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[]) {
        uint32_t left, right;
        size_t ret;
        uint64_t sblock;
        while(!feof(infile)) {
                memset(&sblock,0,sizeof(sblock));
                ret = fread(&sblock,1,sizeof(sblock),infile);
                if(!ret) break;
                left = (sblock>>32) & 0xFFFFFFFF;
                right = sblock & 0xFFFFFFFF;
                sblock = encrypt(left,right,ROUNDS,keys);
                ret = fwrite(&sblock,1,sizeof(sblock),outfile);
        }
}

void decrypt_ecb(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[]) {
        uint32_t left, right;
        size_t ret;
        uint64_t sblock;
        while(!feof(infile)) {
                memset(&sblock,0,sizeof(sblock));
                ret = fread(&sblock,1,sizeof(sblock),infile);
                if(!ret) break;
                left = (sblock>>32) & 0xFFFFFFFF;
                right = sblock & 0xFFFFFFFF;
                sblock = decrypt(left,right,ROUNDS,keys);
                ret = fwrite(&sblock,1,sizeof(sblock),outfile);
        }
}

uint64_t *encrypt_cbc(std::string infile, uint32_t rounds, uint32_t keys[], int affine_a, int affine_b, std::string vig_key) {
        uint32_t left, right;
        size_t ret;
        uint64_t sblock, sblock_prev = RANDOM(32);
	std::string payload;
	size_t z;
	
	uint64_t sblocks[sizeof(infile)+1];
	 for(int x=0;x<sizeof(infile);x++) {
                memset(&sblock,0,sizeof(sblock));
		sblock=(uint64_t)infile[x];
                /* CBC */
                sblock ^= sblock_prev;
                left = (sblock>>32) & RANDOM(32);
                right = sblock & RANDOM(32);
                sblock = encrypt(left,right,ROUNDS,keys);
                sblock_prev = sblock;
		std::ostringstream o;
		o << sblock;
		sblocks[x]=sblock;

		
        }

        
	 return sblocks;
}
void encrypt_cbc(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[], int affine_a, int affine_b, std::string vig_key, int len) {
        uint32_t left, right;
        size_t ret;
        uint64_t sblock, sblock_prev = 0xFFFFFFF;

	uint64_t *data=(uint64_t*)malloc(8192);
	uint64_t sblocks[ROUNDS];
        while(!feof(infile)) {
                memset(&sblock,0,sizeof(sblock));
                ret = fread(&sblock,1,sizeof(sblock),infile);

                if(!ret) break;


                /* CBC */
                sblock ^= sblock_prev;
                left = (sblock>>32) & RANDOM(32);
                right = sblock & RANDOM(32);
                sblock = encrypt(left,right,ROUNDS,keys);
                sblock_prev = sblock;
		std::ostringstream o;
		o << sblock;
		std::string xord=XOR(o.str());
		printf("XOR: %s\n", xord.c_str());
		std::string cipher=vig_encrypt(xord, vig_key);
		printf("VIG: %s\n", cipher.c_str());
		//FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[], int affine_a, int affine_b, std::string vig_key
	        
		std::cout<<std::hex<<std::setfill('0')<<std::setw(8) <<cipher;
	
		
	        
		fwrite(&sblock,1,sizeof(sblock),outfile);
        }


}

void decrypt_cbc(FILE *infile, FILE *outfile, uint32_t rounds, uint32_t keys[], std::string vig_key) {
        int first = 1;
        uint32_t left, right;
        size_t ret;
        uint64_t sblock, sblock_prev, saved;
        while(!feof(infile)) {
                memset(&sblock,0,sizeof(sblock));
                ret = fread(&sblock,1,sizeof(sblock),infile);
                if(!ret) break;
                saved = sblock;
                left = (sblock>>32) & RANDOM(32);
                right = sblock & RANDOM(32);
                sblock = decrypt(left,right,ROUNDS,keys);
                if(first) {
                        sblock ^= 0xFEEDFACE;
                        first = 0;
                } else {
                        sblock ^= sblock_prev;
                }
		std::cout<<std::hex<<std::setfill('0')<<std::setw(8) <<sblock;

		std::ostringstream os;
		os<<sblock;
		std::string vd=vig_decrypt(os.str(), vig_key);
		printf("VIG: %s\n", vd);
		std::string xord=XOR(vd);
		printf("XOR:%s\n", xord);
                /* CBC */
                sblock_prev = saved;
                fwrite(&xord,1,sizeof(xord),outfile);
        }
}
uint64_t *decrypt_cbc(std::string infile, uint32_t rounds, uint32_t keys[], std::string vig_key) {
        int first = 1;
        uint32_t left, right;
        size_t ret;
        uint64_t sblock, sblock_prev, saved;
	
	uint64_t *sblocks;
        for(int x=0;x<sizeof(infile);x++) {
                memset(&sblock,0,sizeof(sblock));
		sblock=(uint64_t)infile[x];

                if(!ret) break;
                saved = sblock;
                left = (sblock>>32) & RANDOM(32);
                right = sblock & RANDOM(32);
                sblock = decrypt(left,right,ROUNDS,keys);
                if(first) {
                        sblock ^= 0xFEEDFACE;
                        first = 0;
                } else {
                        sblock ^= sblock_prev;
                }

	

		
                /* CBC */
                sblock_prev = saved;
        }
	return sblocks;
}

#include<bits/stdc++.h> 
#include<iostream>
#include<string>
#include<iomanip>
#include<vector>


using namespace std;


void printBytes(vector<string> v_s)
{
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;
	
		cout  << *left << " " << *right << " ";
	}
	cout << endl;
}

int f(int subblock, char key)
{
	return subblock^key;
}

int* decrypt(int *left, int *right, long long* p_key)
{
	int rounds = 8;
	for(int i = rounds - 1; i >= 0; i--)
	{
		int temp = *left ^ f(*right, *(char*)p_key+i);
		if(i != 7)
		{
			*left = *right;
			*right = temp;
		}
		else *right = temp;
		
		//cout << 8-i << "th iteration:" << endl << *left << " " << *right << endl << endl;
	}
	
	return left;
}

int* encrypt(int *left, int *right, long long* p_key)
{
	int rounds = 8;
	for(int i = 0; i < rounds; i++)
	{
		int temp = *right ^ f(*left, *(char*)p_key+i);
		
		if(i != 7)
		{
			*right = *left;
			*left = temp;
		}
		else *right = temp;
		
		//cout << i+1 << "th iteration:" << endl << *left << " " << *right << endl << endl;
	}
	
	return left;
}

