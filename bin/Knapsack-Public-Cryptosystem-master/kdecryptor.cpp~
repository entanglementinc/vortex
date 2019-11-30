#include <iostream>
#include <fstream>
#include <string>

void help () {
    std::cerr << "Correct usage: kencryptor <ciphertext_filename> " <<
    "<message_filename> [private_key_filename]" << std::endl;
}

bool is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}


int main (int argc, char **argv) {
    if (argc < 3) help();
    else {
        // Read the filenames or create them
        std::string ciphertext_filename = argv[1];
        std::string message_filename = argv[2];

        std::string private_key_filename;
        if (argc >= 4) {
            private_key_filename = argv[3];
        } else {
            private_key_filename = "private_key.txt";
        }

        // Open the file with the private key
        std::ifstream private_key_file;
        private_key_file.open(private_key_filename);
        if (is_empty(private_key_file)) {
            std::cerr << "The file " << private_key_filename << " is empty" <<
                std::endl;
            return -1;
        }
        // Read n
        int n;
        private_key_file >> n;
        // Read the private key
        long q, r;
        private_key_file >> q;
        private_key_file >> r;
        long A[n];
        for (int i = 0; i < n; i++) {
            private_key_file >> A[i];
        }
        private_key_file.close();

        // Open the file with the ciphertext
        std::ifstream ciphertext_file;
        ciphertext_file.open(ciphertext_filename);
        if (is_empty(ciphertext_file)) {
            std::cerr << "The file " << ciphertext_filename << " is empty" <<
                std::endl;
            return -1;
        }

        // Find s
        int s = 2;
        while((s * r)%q != 1) {
            s++;
        }

        // Open the file to store the deciphered message
        std::ofstream message_file;
        message_file.open (message_filename);

        // Decrypt
        long c;
        while (true) {
            ciphertext_file >> c;
            if (c == -1) break;

            c = (c * s) % q;
            char letter = 0;

            int i = n;
            while (c > 0) {
                i--;
                if (A[i] <= c) {
                    letter |= (1 << 7-i);
                    c -= A[i];
                }
            }

            message_file << letter;
        }


        return 0;
    }

    return -1;
}
