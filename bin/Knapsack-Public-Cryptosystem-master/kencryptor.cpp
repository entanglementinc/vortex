#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>

void help () {
    std::cerr <<
        "Correct usage: kencryptor <message_filename> " <<
        "<ciphertext_filename> [public_key_filename]" << std::endl;
}

bool is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}


int main (int argc, char **argv) {
    if (argc < 3) help();
    else {
        // Read the filenames or create them
        std::string message_filename = argv[1];
        std::string ciphertext_filename = argv[2];

        std::string public_key_filename;
        if (argc >= 4) {
            public_key_filename = argv[3];
        } else {
            public_key_filename = "public_key.txt";
        }

        // Open the file with the messahe
        std::ifstream message_file;
        message_file.open(message_filename);
        if (is_empty(message_file)) {
            std::cerr << "The file " << message_filename << " is empty"
                << std::endl;
            return -1;
        }
        // Read the message
        std::string message;
        std::stringstream buf;
        buf << message_file.rdbuf();
        message = buf.str();
        message_file.close();

        // Open the file with the public key
        std::ifstream public_key_file;
        public_key_file.open(public_key_filename);
        if (is_empty(public_key_file)) {
            std::cerr << "The file " << public_key_filename << " is empty"
                << std::endl;
            return -1;
        }
        // Read n
        int n;
        public_key_file >> n;
        // Read the public key
        long B[n];
        for (int i = 0; i < n; i++) {
            public_key_file >> B[i];
        }
        public_key_file.close();

        // Open the file to store the ciphertext
        std::ofstream ciphertext_file;
        ciphertext_file.open (ciphertext_filename);

        // Encrypt the message
        long c = 0;
        int counter = 0;
        for (int l = 0; l < message.size(); l++) {
            if (counter == n) {
                ciphertext_file << c << " ";
                counter = 0;
                c = 0;
            }
            counter += 8;
            for (int b = 0; b < 8; b++) {
                c += std::bitset<8>(message[l])[7-b] * B[b];
            }
        }
        ciphertext_file << c << " " << "-1";
        ciphertext_file.close();

        return 0;
    }

    return -1;
}
