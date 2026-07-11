#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
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

int main(int argc, char** argv) {
    welcomeArt();
    std::cout << "Simple sockets in C++!\n ~ Written by Xyco\n\n";

    std::cout << "[-] Creating socket...\n";
    int servSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (servSock == -1){
        std::cout << "[!] Error creating socket, likely a socket in TIME_WAIT State.\n Try again in about a minute.\n";

        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Socket created successfully!\n";
    }

    // Specify type, port, and address
    sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(1337);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    std::cout << "[-] Binding socket...\n";
    if (bind(servSock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cout << "[!] Error binding socket\n";
        close(servSock);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Socket bound successfully!\n";
    }

    // Receive data
    char buffer[2048];
    int recvData = recv(servSock, buffer, sizeof(buffer), 0);
    if (recvData == -1) {
        std::cout << "[!] Could not receive data. Please try again.\n";
        exit(EXIT_FAILURE);
    } else {
        buffer[recvData] = '\0';
        std::cout << "Message from client: " << buffer << std::endl;
    }

    // Closing socket
    int closeSock = close(servSock);
    if (closeSock == -1){
        std::cout << "Unable to close socket... killing program!\n";
        exit(EXIT_FAILURE);
    } else {
        std::cout << "[+] Socket has been terminated! Thank you for using the server!\n";
        exit(EXIT_SUCCESS);
    }

    return 0;
}
