#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

std::vector<std::vector<int>> generate(std::vector<int> set)
{
  int x1=set[0];
  int x2=set[1];
  int y1=set[2];
  int y2=set[3];
  int z=set[4];

  int p=17;
  int q=15;
  int c = (pow(p, set[0]))*(pow(q, set[1]));
  int d = (pow(p, set[2]))*(pow(q, set[3]));
  int h = pow(p, set[4]);

  printf("X1 = %d  X2 = %d  Y1 = %d  Y2 = %d  Z = %d\n", set[0], set[1], set[2], set[3], set[4]);
  printf("C = %d  D = %d  H = %d\n", c, d, h);
  std::vector<int> public_key={c, d, h};
  std::vector<int> private_key={x1, x2, y1, y2, z};
  std::vector<std::vector<int>> block = {public_key, private_key};
  return block;
}

std::vector<int> encrypt(std::vector<int> public_key, int byte, int k)
{
  printf("k=%d\n", k);
  int u1 = pow(17, k);
  int u2 = pow(15, k);
  int e = pow(public_key[2], k)*byte;


  printf("E = %d  U1 = %d  U2 = %d\n", e, u1, u2);
  std::vector<int> payload = {e, u1, u2};
  return payload;
}

int decrypt(std::vector<int> private_key, std::vector<int> payload)
{
  printf("%d / %d^%d\n",payload[0], payload[1], private_key[4]);
  int plaintext = payload[0] / (pow(payload[1], private_key[4]));
  printf("D = %d\n", plaintext);
  return plaintext;
}
int main(int argc , char **argv)
{
  std::vector<int> set = {1,2,3,4,5};
  std::vector<std::vector<int>> block = generate(set);
  std::vector<int> payload = encrypt(block[0], 920,14);
  int plaintext = decrypt(block[1], payload);
  return 1;
}
