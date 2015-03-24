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

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 1460 // max number of bytes we can get at once 

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
    printf("hello1\n");
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    char msg2[256];

    //if (argc != 2) {
    //    fprintf(stderr,"usage: client hostname\n");
    //    exit(1);
    //}

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    printf("hello2\n");
    if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
printf("hello3\n");
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
    printf("flag1\n");
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr_client((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure
    int numbytes_total = 0;
    while(1)
    {
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        numbytes_total = numbytes_total + numbytes;
        char msg[256];
        printf("%d", (int)buf);
        int var = ntohl(buf);
        printf("var is %d", var);
        buf[numbytes] = '\0';

        if(numbytes == 0)
        {
            //close(sockfd);
            
        }
        else
        {
            printf("client: received buf              '%s'\n",buf);
            printf("client: received numbytes         '%d'\n",numbytes);
            printf("client: received numbytes total   '%d'\n",numbytes_total);
            
        }
        
        int i;
        for(i = 0; i < numbytes_total; i++)
        {   
            
            sprintf(msg2,"i: %d char int buf:%d\n", i,(int)buf[i]);
            record(msg2);
            //sprintf(msg2,"int buf:%d\n", (int)buf[i]);
            //record(msg2);
        }
    }

    close(sockfd);

    return 0;
}
