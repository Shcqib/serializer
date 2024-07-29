#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include "shared.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int sockfd = 0;
char message[100];

void promptUserForString(char *string);
void *receiveMessageFromServer(void *arg);
void clientSocket();
void serializeMessage(MessageType type, void *data, size_t dataSize, unsigned char *buffer);

int main(void) {
	unsigned char buffer[1024];

	clientSocket();
	Data request = {"user1", "user2", "Wants to be your friend"};
	serializeMessage(FRIEND_REQUEST, &request, sizeof(Data), buffer);
	printf("sending buffer = %s", buffer);

	buffer[0] = '\0';

	Data request2 = {"user3", "user4", "Sent you a message"};
	serializeMessage(SEND_MESSAGE, &request2, sizeof(Data), buffer);
	printf("sending buffer = %s", buffer);
}

void serializeMessage(MessageType type, void *data, size_t dataSize, unsigned char *buffer) {
    buffer[0] = (unsigned char)type;
    buffer[1] = (unsigned char)dataSize; 
    memcpy(buffer + 2, data, dataSize); 

	send(sockfd, buffer, 2 + dataSize, 0);
}

void promptUserForString(char *string) {
    printf(": ");
    fgets(string, 250, stdin);
    string[strcspn(string, "\n")] = '\0';
    printf("\n");
}

void clientSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);



    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(9999),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };



    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) == 0) {
        char message[200];
        snprintf(message, sizeof(message), "CONNECT");
        send(sockfd, message, strlen(message) + 1, 0);
    }

    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, receiveMessageFromServer, NULL) != 0) {
        perror("pthread_create");
        close(sockfd);
        exit(1);
    }

}

void sendMessage(char *bufferToSend) {
    send(sockfd, bufferToSend, strlen(bufferToSend) + 1, 0);
}

void *receiveMessageFromServer(void *arg) {
    while (true) {
        char buffer[256];

        int bytes_received = recv(sockfd, buffer, 255, 0);
        if (bytes_received <= 0) return NULL;
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    return NULL;

}
