#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){

    if (argc != 3){
        std::cout << "Must include a host and a port as arguments." << std::endl;
        return 1;
    }

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in hostAddress;
    hostAddress.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &hostAddress.sin_addr);

    try{
        int port = std::stoi(argv[2]);
        hostAddress.sin_port = htons(static_cast<uint16_t>(port));
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Port argument invalid: not a number." << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::out_of_range&) {
        std::cerr << "Port argument invalid: too large." << std::endl;
        return EXIT_FAILURE;
    }

    // sending connection request
    if(connect(clientSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress)) == -1){
        perror("connect");
        return EXIT_FAILURE;
    }
    else{        
        std::cout << "Connected successfully" << std::endl;
    }

    // closing socket
    close(clientSocket);

    return 0;

}