#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server-ip> <port>\n", argv[0]);
        return 1;
    }

    char *serverIp = argv[1];
    char *serverPort = argv[2];

    // look up server address
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *serverAddress;
    if (getaddrinfo(serverIp, serverPort, &hints, &serverAddress) != 0) {
        printf("could not find host\n");
        return 1;
    }

    // make socket
    int clientSocket = socket(serverAddress->ai_family, serverAddress->ai_socktype, serverAddress->ai_protocol);
    if (clientSocket < 0) {
        printf("socket creation failed\n");
        return 1;
    }

    // connect to server
    if (connect(clientSocket, serverAddress->ai_addr, serverAddress->ai_addrlen) < 0) {
        printf("connection failed\n");
        return 1;
    }
    freeaddrinfo(serverAddress);

    printf("Connected to server.\n");

    // ask user for input
    char userMessage[1024];
    printf("Enter a message: ");
    if (fgets(userMessage, sizeof(userMessage), stdin) != NULL) {
        // remove trailing newline
        userMessage[strcspn(userMessage, "\r\n")] = 0;

        // send user text
        send(clientSocket, userMessage, strlen(userMessage), 0);

        // receive echo back
        char serverReply[1024];
        memset(serverReply, 0, sizeof(serverReply));
        int bytesIn = recv(clientSocket, serverReply, sizeof(serverReply) - 1, 0);

        if (bytesIn > 0) {
            printf("Server replied: %s\n", serverReply);
        }
    }

    // clean up
    close(clientSocket);
    return 0;
}
