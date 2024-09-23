/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       22 September 2024

34. Write a program to create a concurrent server.
    a. use fork
    b. use pthread_create
========================================================================================
*/

/////////////////////////////// client for task 34 /////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "sock_msg_struct.h"

#define FPORT 5008
#define PPORT 5009

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("must provide arg for connecting to fork or pthread server\n");
        printf("usage: %s <f/p>\n", argv[0]);
        return -1;
    }
    int port;
    char ch = argv[1][0];
    while (ch != 'f' && ch != 'p') {
        printf("invalid argument!\n");
        printf("please select fork or pthread server [f/p]: ");
        scanf("%c", &ch);
        getchar();
    }
    if (ch == 'f') { port = FPORT; }
    else if (ch == 'p') { port = PPORT; }

    struct sockaddr_in serv;
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    printf("trying to connect to server...\n");
    if (connect(sfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("invalid connection ");
        return -1;
    }
    
    msg_struct msg;
    msg.id = getpid();
    srand(time(NULL));
    msg.service_time = abs(rand()) % 10;
    sprintf(msg.buf, "hello from client at %ld", time(NULL));
    int wr = write(sfd, &msg, sizeof(msg));
    printf("sent %d bytes to server\n", wr);
    char buf[128];
    int rd = read(sfd, &buf, sizeof(buf));
    printf("msg from server (%d bytes): %s\n", rd, buf);

    close(sfd);
    return 0;
}

/*
Sample Execution:

-- first terminal (server)
$ runc 33_socket_comm.c s
listening at port 5007...

-- second terminal (client)
$ runc 33_socket_comm.c
trying to connect to server...
sent 128 bytes to server

-- first terminal (server)
msg from client (128 bytes): hello from client at 1726988542
sent 128 bytes to client

-- second terminal (client)
msg from server (128 bytes): hello from server at 1726988542

*/