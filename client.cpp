#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv) {
    std::cout << "Simple sockets in C++!\n ~ Written by Xyco\n";

    // Creating socket
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
        std::cout << "[-] Creating socket...\n";

        if (clientSock == -1){
        std::cout << "[!] Error creating socket, likely a socket in TIME_WAIT State.\n Try again in about a minute.\n";

        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Socket created successfully!\n";
    }

    // Create struct to hold connection/socket data
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1337);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Send connection request
    int serverConn = connect(clientSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    std::cout << "[-] Attempting to connect to the server...\n";

    if (serverConn == -1){
        std::cout << "[!] Connection request to the server has failed! Please try again!\n";

        close(clientSock);

        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Successfully connected to the server!\n";
    }

    // Read line of data from user
    std::string msg;
    std::getline(std::cin, msg);

    // Send data to server
    int sendMsg = send(clientSock, msg.c_str(), msg.length(), 0);
    if(sendMsg == -1){
        std::cout << "[!] Unable to send message to the server, please try again.\n";
        std::cout << "[!] Closing socket...\n";

        close(clientSock);

        exit(EXIT_FAILURE);
    }

    // Closing socket
    int closeSock = close(clientSock);
    if (closeSock == -1){
        std::cout << "Unable to close socket... killing program!\n";
        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Socket has been terminated! Thank you for using the client!\n";
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
