/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       22 September 2024

33. Write a program to communicate between two machines using socket.
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

#define PORT 5007

int server_main() {
    struct sockaddr_in serv, cli;
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(sfd, (void*)&serv, sizeof(serv));
    listen(sfd, 5);
    printf("listening at port %d...\n", PORT);
    socklen_t clisize = sizeof(socklen_t);
    int cfd = accept(sfd, (void*)&cli, &clisize);

    char buf[128];
    int rd = read(cfd, buf, 128);
    printf("msg from client (%d bytes): %s\n", rd, buf);
    sprintf(buf, "hello from server at %ld", time(NULL));
    int wr = write(cfd, buf, 128);
    printf("sent %d bytes to client\n", wr);

    shutdown(sfd, SHUT_RDWR);
    close(sfd);
    return 0;
}

int client_main() {
    struct sockaddr_in serv;
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    serv.sin_family = AF_UNIX;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(5007);
    printf("trying to connect to server...\n");
    connect(sfd, (struct sockaddr*)&serv, sizeof(serv));
    
    char buf[128];
    sprintf(buf, "hello from client at %ld", time(NULL));
    int wr = write(sfd, buf, 128);
    printf("sent %d bytes to server\n", wr);
    int rd = read(sfd, buf, 128);
    printf("msg from server (%d bytes): %s\n", rd, buf);

    shutdown(sfd, SHUT_RDWR);
    close(sfd);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 1) return client_main();
    return server_main();
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