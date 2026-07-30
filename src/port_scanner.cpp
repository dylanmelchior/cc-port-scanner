/*
    A simple port scanner. 
*/

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "thread_pool.h"

void scanPort(int portNumber, sockaddr_in hostAddress){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    hostAddress.sin_port = htons(portNumber);
    if(connect(clientSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress)) == 0){
        std::cout << "Connection on port: " << portNumber << std::endl;
    }
    close(clientSocket);
}

int main(int argc, char* argv[]){

    if (argc != 3){
        std::cout << "Must include a host and number of workers as an argument." << std::endl;
        return 1;
    }

    int workerCount = std::stoi(argv[2]);
    ThreadPool workers(workerCount);

    sockaddr_in hostAddress;
    hostAddress.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &hostAddress.sin_addr);

    for(int i = 1; i < 65536; i++){
        workers.submit([i, hostAddress]() { scanPort(i, hostAddress); });
    }
    return 0;
}