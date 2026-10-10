#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    char *portNum = argv[1];

    // setup address hints
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bindAddress;
    getaddrinfo(0, portNum, &hints, &bindAddress);

    // create listening socket
    int listenSocket = socket(bindAddress->ai_family, bindAddress->ai_socktype, bindAddress->ai_protocol);
    if (listenSocket < 0) {
        printf("failed to create socket\n");
        return 1;
    }

    // bind socket to port
    if (bind(listenSocket, bindAddress->ai_addr, bindAddress->ai_addrlen) < 0) {
        printf("bind error\n");
        return 1;
    }
    freeaddrinfo(bindAddress);

    // listen for incoming client
    if (listen(listenSocket, 5) < 0) {
        printf("listen error\n");
        return 1;
    }

    printf("Server is listening on port %s...\n", portNum);

    // accept connection
    struct sockaddr_storage clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(listenSocket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSocket < 0) {
        printf("accept error\n");
        return 1;
    }

    // get client ip string
    char clientIp[100];
    getnameinfo((struct sockaddr *)&clientAddr, clientLen, clientIp, sizeof(clientIp), 0, 0, NI_NUMERICHOST);
    printf("Client connected from: %s\n", clientIp);

    // read message from client
    char textBuffer[1024];
    memset(textBuffer, 0, sizeof(textBuffer));
    int bytesRead = recv(clientSocket, textBuffer, sizeof(textBuffer) - 1, 0);

    if (bytesRead > 0) {
        printf("Message received: %s\n", textBuffer);
        printf("Echoing message back to client...\n");

        // send message back
        send(clientSocket, textBuffer, bytesRead, 0);
    }

    // close down sockets
    close(clientSocket);
    close(listenSocket);

    return 0;
}
