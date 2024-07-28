#ifndef SHARED_H
#define SHARED_H

#define MAX_CLIENTS 2

typedef struct {
    char SenderName[50];
    char ReceiverName[50];
    char Message[100];
} FriendRequest;

void handleCommand(char *buffer, int clientfd);

#endif
