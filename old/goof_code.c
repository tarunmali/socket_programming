#include <iostream>
#include <cstring>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <IP Address>" << std::endl;
        return 1;
    }

    const char* address = argv[1];
    struct sockaddr_in server_address;
    
    // Initialize the server_address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    // Use inet_pton to convert the IP address string to binary format
    if (inet_pton(AF_INET, address, &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid IP address: " << address << std::endl;
        return 1;
    }

    // Now, you can use server_address.sin_addr as intended.

    return 0;
}
