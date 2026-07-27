/*
    A simple port scanner. 
*/

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        std::cout << "Must include a host as an argument." << std::endl;
        return 1;
    }

    sockaddr_in hostAddress;
    hostAddress.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &hostAddress.sin_addr);

    for(int i = 1; i < 65536; i++){
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        hostAddress.sin_port = htons(i);
        // sending connection request
        if(connect(clientSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress)) == 0){
            std::cout << "Connected on port: " << i << std::endl;
        }
        else {
            perror("connect: ");
        }

        // closing socket
        close(clientSocket);
    }
    return 0;
}