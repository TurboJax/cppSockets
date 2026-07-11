#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include <iostream>

void welcomeArt() {
    std::cout << R"(
$$\   $$\ $$\     $$\  $$$$$$\   $$$$$$\  $$\  $$$$$$\
$$ |  $$ |\$$\   $$  |$$  __$$\ $$  __$$\ $  |$$  __$$\
\$$\ $$  | \$$\ $$  / $$ /  \__|$$ /  $$ |\_/ $$ /  \__|
 \$$$$  /   \$$$$  /  $$ |      $$ |  $$ |    \$$$$$$\
 $$  $$<     \$$  /   $$ |      $$ |  $$ |     \____$$\
$$  /\$$\     $$ |    $$ |  $$\ $$ |  $$ |    $$\   $$ |
$$ /  $$ |    $$ |    \$$$$$$  | $$$$$$  |    \$$$$$$  |
\__|  \__|    \__|     \______/  \______/      \______/
 $$$$$$\   $$$$$$\   $$$$$$\  $$\   $$\ $$$$$$$$\ $$$$$$$$\  $$$$$$\
$$  __$$\ $$  __$$\ $$  __$$\ $$ | $$  |$$  _____|\__$$  __|$$  __$$\
$$ /  \__|$$ /  $$ |$$ /  \__|$$ |$$  / $$ |         $$ |   $$ /  \__|
\$$$$$$\  $$ |  $$ |$$ |      $$$$$  /  $$$$$\       $$ |   \$$$$$$\
 \____$$\ $$ |  $$ |$$ |      $$  $$<   $$  __|      $$ |    \____$$\
$$\   $$ |$$ |  $$ |$$ |  $$\ $$ |\$$\  $$ |         $$ |   $$\   $$ |
\$$$$$$  | $$$$$$  |\$$$$$$  |$$ | \$$\ $$$$$$$$\    $$ |   \$$$$$$  |
 \______/  \______/  \______/ \__|  \__|\________|   \__|    \______/
)" << std::endl;
}

int main(int argc, char** argv){
    welcomeArt();
    printf("Simple sockets in C++!\n ~ Written by Xyco\n\n");

    printf("[-] Creating socket...\n");
    int servSock = socket(AF_INET, SOCK_STREAM, 0);
    if (servSock == -1){
        printf("[!] Error creating socket, likely a socket in TIME_WAIT State.\n Try again in about a minute.\n");

        exit(EXIT_FAILURE);
    } else {
        printf("[+] Socket created successfully!\n");
    }

    // Specify type, port, and address
    sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(1337);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    printf("[-] Binding socket...\n");
    if (bind(servSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("[!] Error binding socket");
        close(servSock);
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Socket bound successfully!\n");
    }

    // Listen to the assigned/created socket
    int listSock = listen(servSock, 5);
    if (listSock == -1) {
        printf("[!] Error listening to the created socket. Please try again.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Listening...\n");
    }

    // Accept connection request
    int acceptClientSock = accept(servSock, nullptr, nullptr);
    if (acceptClientSock == -1) {
        printf("[!] Unable to accept connection request. Please try again.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Connection from client has been accepted!\n");
    }

    // Receive data
    char buffer[2048] = { 0 };
    int recvData = recv(acceptClientSock, buffer, sizeof(buffer), 0);
    if (recvData == -1) {
        printf("[!] Could not receive data. Please try again.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Message from client: %s\n", buffer);
    }

    // Closing socket
    int closeSock = close(servSock);
    if (closeSock == -1){
        printf("Unable to close socket... killing program!\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[+] Socket has been terminated! Thank you for using the server!\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}
