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
    //printf("hello1\n");
    int sockfd, numbytes;  
    char buf[4];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    char msg[256];

    //if (argc != 2) {
    //    fprintf(stderr,"usage: client hostname\n");
    //    exit(1);
    //}

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    //printf("hello2\n");
    if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &servinfo)) != 0) {
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
    int numbytes_total = 0;
    //while(1)
    //{
        
        /* Receive Header */
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
         printf("client: received numbytes         '%d'\n",numbytes);
         
         
        /* Receive Header */ 
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
         printf("client: received numbytes         '%d'\n",numbytes);
         //printf("number is: %08X\n", buf);
         //printf("number is: %s\n", buf);
        
        uint32_t number;
        
        int n = 0;
        int count = 0;
        while(n < numbytes)
        {
                number = buf[n++]; number = number << 8;
                number = number + buf[n++]; number = number << 8;
                number = number + buf[n++]; number = number << 8;
                number = number + buf[n++];
        
                printf("number is: %08X\n", number);
                means_fixed[count] = number;               
                count++;
        }
        
        //char c1,c2,c3,c4;
        
       // fscanf(file, "%c%c", &c1, &c2);         /* Scan in two characters */
//                    var = c1;                               /* Set to first character */ 
//                    var = var << 8;                         /* Shift var over 8 */                    
//                    var = var + c2;
        //numbytes_total = numbytes_total + numbytes;
        //char msg[256];
        //printf("int representation: %08X\n", (uint32_t)*buf);
       // printf("buf is %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n",buf[0], buf[1], buf[2], buf[3],buf[4], buf[5], buf[6], buf[7],buf[8], buf[9], buf[10], buf[11]);
        //uint32_t var = ntohl(buf);
        //printf("var is %08X", var);
        //printf("buf is %02X %02X %02X %02X %c %c %c %c\n",var[0], var[1], var[2], var[3], (int)var[0], (int)var[1], (int)var[2], (int)var[3]);
        //buf[numbytes] = '\0';

        if(numbytes == 0)
        {
            printf("inside numbytes = 0\n");
            int i;
            for(i = 0; i < 1088; i++)
            {
                sprintf(msg,"meansfixed[%d]: %08X\n", i, means_fixed[i]);
                record(msg);
            }
            close(sockfd);
            
        }
        else
        {
        //    printf("client: received buf              '%s'\n",buf);
        //    printf("client: received numbytes         '%d'\n",numbytes);
        //    printf("client: received numbytes total   '%d'\n",numbytes_total);
            //
        }
        
       // int i;
       // for(i = 0; i < numbytes_total; i++)
        //{   
            
            //sprintf(msg2,"i: %d char int buf:%X\n", i,(int)buf[i]);
            //record(msg2);
            //sprintf(msg2,"int buf:%d\n", (int)buf[i]);
            //record(msg2);
        //}
    //}

    close(sockfd);

    return 0;
}
