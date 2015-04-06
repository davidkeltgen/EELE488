/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include "means.h"
#include "standards.h"
#include "classification.h"
#include "datacube.h"

#define PORT "3490" // the port client will be connecting to 

#define HEADER_SIZE 256 // max number of bytes we can get at once 

int sockfd;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr_client(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int client(char * argv)
{
    printf("started client connection\n");
    printf("%s\n", argv);
    //printf("hello1\n");
    int numbytes;  
    char buf[512 * 50];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    char msg[512];

    //if (argc != 2) {
    //    fprintf(stderr,"usage: client hostname\n");
    //    exit(1);
    //}

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    //printf("hello2\n");
    if ((rv = getaddrinfo(argv, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
//printf("hello3\n");
    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }
    //printf("flag1\n");
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr_client((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure
    
    // End of client setup
    int total_frames = 0;
    /* Keep on collecting data indefinitely */
    /* Polling every one second */
    for(;;)
    {
        /* Receive Frame CounterData */ 
        if ((numbytes = recv(sockfd, buf, sizeof(uint32_t) * 1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        
        sprintf(msg,"buf[0-3]: %c %c %c %c\n",buf[0], buf[1], buf[2], buf[3]); record(msg);
        sprintf(msg,"Frame count is: %d\n", buf); record(msg);
        
        sleep(1);
    }
    
     
     while(1)
     {
        usleep(20000);
     }
    
     close(sockfd);

    return 0;
}

int closeClient(void)
{
    close(sockfd);  // parent doesn't need this
}
