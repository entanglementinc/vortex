#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include<bits/stdc++.h>

std::string generatekey(std::string str, std::string key) 
{ 
    int x = str.size(); 
  
    for (int i = 0; i<key.length(); i++) 
    { 
      key.push_back((char)i);
    } 
    return key; 
} 
  
int encrypt(int content, int key)
{
  int payload = (content + key) % 26;
  return payload;
}

int decrypt(int payload, int key)
{
  int plain = (payload-key+26)%26;
  return plain;
}

int main(int argc, char **argv)
{
  std::string key="password";
  key=generatekey(argv[1], key);
  printf("KEY=%s\n", key);
  int payload = encrypt(atoi(argv[1]), (int)key[0]);
int plain = decrypt(payload, (int)key[0]);

  printf("ENCRYPTING: %s\nCIPHERTEXT: %i\nPLAINTEXT: %i\n", argv[1], payload, plain);
}
