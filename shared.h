#ifndef SHARED_H
#define SHARED_H

#define MAX_CLIENTS 2

typedef enum {
    FRIEND_REQUEST = 1,
	SEND_MESSAGE = 2,
} MessageType;

typedef struct {
    char SenderName[50];
    char ReceiverName[50];
    char Message[100];
} Data;

typedef struct {
    MessageType type;
    size_t size;
	char data[];
} Message;

void handleCommand(char *buffer, int clientfd);

#endif
