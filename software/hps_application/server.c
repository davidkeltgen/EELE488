/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: server.c                                                      *
 * Date:  March 17 2015                                                     *
 * Description: *
 * 				*
 *				*
 *				*
 *				*
 *				*
 ****************************************************************************/

/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <arpa/inet.h>


#include "server.h"

#define PORT "3491"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold

ssize_t write(int fd, const void *buf, size_t count);

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//int sendall(int s, char *buf, int *len)
//{
//    printf("in sendall\n");
//    printf("length: %d\n", *len);
//    int total = 0;        // how many bytes we've sent
//    int bytesleft = *len; // how many we have left to send
//    int n;
//
//    while(total < *len) {
//        n = send(s, buf+total, bytesleft, 0);
//        printf("number of bytes sent: %d\n", n);
//        if (n == -1) { break; }
//        total += n;
//        bytesleft -= n;
//    }
//
//    *len = total; // return number actually sent here
//
//    return n==-1?-1:0; // return -1 on failure, 0 on success
//}

int server(void)
{
    //Start of setup
    record("SERVER: Server started\n");
    char msg[256];
    int sockfd;  // listen on sock_fd,
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    int connection = 0;
    while(!connection) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);
        connection = 1;

       // if (!fork()) { // this is the child process
       //     close(sockfd); // child doesn't need the listener
        //}
    } //end server
}

int sendAck(void)
{

	/* Arbitrary aknowledgement character */
	char a = 'a';
    /* Send acknowledge */
    write(new_fd, &a, 1);

}

int sentFrameNum(uint32_t num_frames)
{
	write(new_fd, &num_frames, sizeof(uint32_t));
}





int closeServer(void)
{
    close(new_fd);  // parent doesn't need this
}
