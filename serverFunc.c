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
    MessageType type = (MessageType)buffer[0];
    size_t dataSize = (size_t)buffer[1];
    Data *data = buffer + 2;

    switch (type) {
        case FRIEND_REQUEST: {
            Data *request = data;
            printf("Sender name = %s\n", request->sender);
            printf("Receiver name = %s\n", request->receiver);
            printf("Message = %s\n", request->message);
            break;
        }
		case SEND_MESSAGE: {
			Data *request = data;
			printf("Sender name = %s\n", request->sender);
            printf("Receiver name = %s\n", request->receiver);
            printf("Message = %s\n", request->message);
            break;
		}
        default:
            printf("Unknown message type\n");
			break;
    }
}

void handleCommand(char *buffer, int clientfd) {
}
