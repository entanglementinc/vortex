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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
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
        do {
            r = std::rand() % q;
        } while (gcd(q, r) != 1);

        // Store the private key to a file
        std::ofstream private_key_file;
        private_key_file.open (private_key_filename);
        private_key_file << n << "\n";
        private_key_file << q << "\n";
        private_key_file << r << "\n";
        for (int i = 0; i < n; i++) {
            private_key_file << A[i] << " ";
        }
        private_key_file << -1; // End token
        private_key_file.close();

        // Create the set B
        long B[n];
        for (int i = 0; i < n; i++) {
            B[i] = (A[i] * r) % q;
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
