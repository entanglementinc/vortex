#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<math.h>
#define CHILD 0
#define PARENT 1
#define P_MAX_SIZE 10000

short int isPrime();
unsigned long int quickE();
unsigned long int randomPrime();
unsigned long int chooseGenerator();

unsigned long int quickE(unsigned long int a, unsigned long int b, unsigned long int n){ // quickE stands for quick exponentiation
  unsigned long int res = 1, pot = a % n;
  while(b){
    if(b % 2 == 1){
      res = (pot * res) % n;
    }
    pot = (pot * pot) % n;
    b = b >> 1;
  }
  return res;
}

unsigned long int randomPrime(){
  unsigned long int r;
  while(1){
    r = rand() % P_MAX_SIZE ;
    if(isPrime(r))
      return r;
  }
}

unsigned long int chooseGenerator(unsigned long int p){
		unsigned long int g;
		while(g = rand() % p - 1){
		if(quickE(g,(p - 1) / 2,p) != 1 && quickE(g,(p - 1) / 4,p) != 1 && quickE(g,(p - 1)*3 / 4,p) != 1){
			return g;
		} 
	}
}

short int isPrime(unsigned long int n){
  long int i;
  if (n % 2 == 0)
    return 0;
  for (i = 3; i < ceil(sqrt(n)); i+=2){
    if(n % i == 0)
      return 0;
  }
  return 1;
}

main(){
  putchar('\n');
  int sockets[2], child_id, i;
  
  srand(time(NULL));
  // public stuff
  unsigned long int p = randomPrime();
  unsigned long int g = chooseGenerator(p);
  
  puts("Public values:");
  printf("P: %li\nG: %li\n\n", p, g);
  
  socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
  if ((child_id = fork()) == -1){
    puts("error, child process cannot be made");


  } else if (child_id) { // if child_id > 1 it means this the parent process
    close(sockets[CHILD]);
    unsigned long int x = rand() % p + 1;
    unsigned long int fx = quickE(g,x,p);
    unsigned long int key, fy;
    char buf[128];
    printf("Im the parent process and I choose %li\nI computed %li\n", x,fx);
    read(sockets[PARENT], buf, sizeof(fx), 0);
    fy = (unsigned long int)atol(buf);
    printf("Parent has recieved %li from child\n", fy);
    sprintf(buf,"%li",fx);
    write(sockets[PARENT], buf, sizeof(fx));
    printf("Parent send %li to child\n", fx);
    key = quickE(fy, x, p);
    printf("Parent Key: %li\n", key);
    
    close(sockets[PARENT]);


  } else { // this means child_id == 0, this is the child process
    close(sockets[PARENT]);
    unsigned long int y = ((rand() % p) * (rand() % p) % p) + 1;
    unsigned long int fy = quickE(g,y,p);
    unsigned long int key, fx;
    char buf[128];
    printf("\tIm the child process and I choose %li\n\tI computed %li\n", y, fy);
    sprintf(buf,"%li",fy);
    write(sockets[CHILD],buf, sizeof(fx));
    printf("\tChild send %li to parent\n", fy);
    read(sockets[CHILD], buf, sizeof(fx),0);
    fx = (unsigned long int)atol(buf);
    printf("\tChild has recieved %li from parent\n", fx);
    key = quickE(fx,y,p);
    printf("\tChild Key: %li\n",key);

    close(sockets[CHILD]);
  }
putchar('\n');
}
