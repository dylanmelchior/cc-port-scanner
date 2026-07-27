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
    hostAddress.sin_port = htons(80);
    inet_pton(AF_INET, argv[1], &hostAddress.sin_addr);

    // sending connection request
    if(connect(clientSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress)) == -1){
        perror("connect");
        return EXIT_FAILURE;
    }

    std::cout << "Connected successfully";
    
    // closing socket
    close(clientSocket);

    return 0;

}