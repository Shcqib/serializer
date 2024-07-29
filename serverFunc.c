#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "shared.h"

#define MAX_LINE_LENGTH 256

void deserializeMessage(unsigned char *buffer) {
    MessageType type = buffer[0];
    size_t dataSize = (size_t)buffer[1];
	Data *request;
	memcpy(request, buffer + 2, dataSize); 

    switch (type) {
        case FRIEND_REQUEST: {
			printf("FRIEND_REQUEST:\n");
            printf("Sender name = %s\n", request->SenderName);
            printf("Receiver name = %s\n", request->ReceiverName);
            printf("Message = %s\n", request->Message);
            break;
        }
        case SEND_MESSAGE: {
            printf("SEND_MESSAGE:\n");
			printf("Sender name = %s\n", request->SenderName);
            printf("Receiver name = %s\n", request->ReceiverName);
            printf("Message = %s\n", request->Message);
            break;
		}
        default:
            printf("Unknown message type\n");
			break;
    }
}

void handleCommand(unsigned char *buffer, int clientfd) {
	deserializeMessage(buffer);
}
