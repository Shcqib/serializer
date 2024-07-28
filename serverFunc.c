#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "shared.h"

#define MAX_LINE_LENGTH 256

void deserializeFriendRequest(unsigned char *buffer, FriendRequest *request) {
    memcpy(request, buffer + 2, sizeof(FriendRequest));
}

void handleCommand(char *buffer, int clientfd) {
	printf("%s", buffer);

    char *firstSpacePosition;
    char firstWord[256];

    firstSpacePosition = strchr(buffer, ' ');

    if (firstSpacePosition != NULL) {
        int lengthToCopy = firstSpacePosition - buffer;
        strncpy(firstWord, buffer, lengthToCopy);
        firstWord[lengthToCopy] = '\0';
    } else {
        return;
    }
}
