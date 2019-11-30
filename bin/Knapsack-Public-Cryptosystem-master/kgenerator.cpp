#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void help () {
    std::cerr <<
    "Correct usage: kgenerator [private_key_filename] [public_key_filename]"
    << std::endl;
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
int main (int argc, char **argv) {
    if (argc < 3 && argv[1] == "-h") help();
    else {
        int n = 8;

        // Read the filenames or create them
        std::string private_key_filename;
        if (argc >= 2) {
            private_key_filename = argv[1];
        } else {
            private_key_filename = "private_key.txt";
        }

        std::string public_key_filename;
        if (argc >= 3) {
            public_key_filename = argv[2];
        } else {
            public_key_filename = "public_key.txt";
        }

        // Create a seed for the random generator
        srand(time(NULL));

        // Create the superincreasing set A and q
        long A[n];
        long q = 0;
        for (int i = 0; i < n; i++) {
            int random_number = std::rand() % 10;
            A[i] = q + random_number;
            q += A[i];
        }

        q += std::rand() % 10;

        // Generate r
        long r;
	long r1;
	long r2;
	long r3;
        do {
            r = std::rand() % q;
	    r1 = rand()%q;
	    r2 = rand()%q;

        } while (findGCD(q, r, r1, r2) != 1);

        // Store the private key to a file
        std::ofstream private_key_file;
        private_key_file.open (private_key_filename);
        private_key_file << n << "\n";
        private_key_file << q << "\n";
        private_key_file << r << "\n";
	private_key_file << r1 << "\n";
	private_key_file << r2 << "\n";
	
        for (int i = 0; i < n; i++) {
            private_key_file << A[i] << " ";
        }
        private_key_file << -1; // End token
        private_key_file.close();

        // Create the set B
        long B[n];
        for (int i = 0; i < n; i++) {
            B[i] = (A[i] * r * r1 * r2) % q;
        }

        // Store the public key to a file
        std::ofstream public_key_file;
        public_key_file.open (public_key_filename);
        public_key_file << n << "\n";
        for (int i = 0; i < n; i++) {
            public_key_file << B[i] << " ";
        }
        public_key_file.close();

        return 0;
    }

    return -1;
}
