#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv){
    printf("Simple sockets in C++!\n ~ Written by Xyco\n");

    // Creating socket
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
        printf("[-] Creating socket...\n");

        if (clientSock == -1){
        printf("[!] Error creating socket, likely a socket in TIME_WAIT State.\n Try again in about a minute.\n");

        exit(EXIT_FAILURE);
    } else {
        printf("[+] Socket created successfully!\n");
    }

    // Create struct to hold connection/socket data
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1337);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Send connection request
    int serverConn = connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    printf("[-] Attempting to connect to the server...\n");

    if (serverConn == -1){
        printf("[!] Connection request to the server has failed! Please try again!\n");
        
        close(clientSock);
        
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Successfully connected to the server!\n");
    }

    // Send data
    const char* msg = "Hello, server!";
    int sendMsg = send(clientSock, msg, strlen(msg), 0);
    if(sendMsg == -1){
        printf("[!] Unable to send message to the server, please try again.\n");
        printf("[!] Closing socket...\n");

        close(clientSock);

        exit(EXIT_FAILURE);
    }

    // Closing socket
    int closeSock = close(clientSock);
    if (closeSock == -1){
        printf("Unable to close socket... killing program!\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Socket has been terminated! Thank you for using the client!\n");
        exit(EXIT_SUCCESS);
    }

    return 1;
}

/** Remember:
 * 1. Create socket
 * 2. Create struct to handle connection (socket) data
 * 3. Send connection request to the server (client/server model
 * 4. Send data
 * 5. Close the socket
 * **/
