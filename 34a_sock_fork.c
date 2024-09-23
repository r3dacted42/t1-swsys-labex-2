/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       22 September 2024

34. Write a program to create a concurrent server.
    a. use fork <---
    b. use pthread_create
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include "sock_msg_struct.h"

#define PORT 5008

void close_sock(int);
int sfd;

int main() {
    struct sockaddr_in serv, cli;
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("failed while opening socket");
        return -1;
    }
    int opt = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("failed during setsockopt");
        close_sock(0);
    }

    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);
    if (bind(sfd, (void*)&serv, sizeof(serv)) < 0) { 
        perror("failed at bind"); 
        close_sock(0); 
    }
    if (listen(sfd, 5) < 0) { 
        perror("failed at listen"); 
        close_sock(0); 
    }
    printf("listening at port %d...\n", PORT);
    signal(SIGINT, close_sock);
    int num_requests = 0;
    socklen_t clisize = sizeof(cli);
    
    while (1) {
        int cfd = accept(sfd, (void*)&cli, &clisize);
        if (cfd < 0) {
            perror("failed at accept");
            close_sock(0);
        }
        num_requests++;
        if (!fork()) {
            printf("forked for request #%d\n", num_requests);
            msg_struct msg;
            int rd = read(cfd, &msg, sizeof(msg));
            printf("msg from client (%d bytes):\n", rd);
            printf("client id: %d\nservice time: %d\n", msg.id, msg.service_time);
            printf("message: %s\n", msg.buf);
            sleep(msg.service_time);
            char buf[128];
            sprintf(buf, "hello from server at %ld", time(NULL));
            int wr = write(cfd, buf, 128);
            printf("sent %d bytes to client\n", wr);
            return 0;
        }
    }

    return 0;
}

void close_sock(int s) {
    printf("\nshutting down server...\n");
    close(sfd);
    // delete socket file to reuse address :P
    system("unlink $(ls -l | grep -a '^s' | awk '{ print $NF }')");
    exit(0);
}

/*
Sample Execution:

-- first terminal with server
$ runc 34a_sock_fork.c 
listening at port 5008...
forked for request #1
msg from client (136 bytes):
client id: 66940
service time: 6
message: hello from client at 1727103207
forked for request #2
msg from client (136 bytes):
client id: 66952
service time: 3
message: hello from client at 1727103208
sent 128 bytes to client
sent 128 bytes to client
^C
shutting down server...

-- second terminal with client 1
$ runc 34_sock_client.c f
trying to connect to server...
sent 136 bytes to server
msg from server (128 bytes): hello from server at 1727103211

-- third terminal with client 2
$ runc 34_sock_client.c f
trying to connect to server...
sent 136 bytes to server
msg from server (128 bytes): hello from server at 1727103213

*/