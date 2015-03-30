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

#define MAXDATASIZE 1049 // max number of bytes we can get at once 

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
    char buf[1088 * 50];
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
        
//        /* Receive Header */
//        if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
//            perror("recv");
//            exit(1);
//        }
//         //printf("means client h : received numbytes         '%d'\n",numbytes);
//         //printf("%s\n", buf);
//         
//         
//        /* Receive Data */ 
//        if ((numbytes = recv(sockfd, buf, sizeof(uint32_t) * MEANS_MATRIX_SIZE, 0)) == -1) {
//            perror("recv");
//            exit(1);
//        }
//         //printf("means client d : received numbytes         '%d'\n",numbytes);
//        
//        uint32_t number;
//        
//        int n = 0;
//        int count = 0;
//        while(n < numbytes)
//        {
//                number = buf[n++]; number = number << 8;
//                number = number + buf[n++]; number = number << 8;
//                number = number + buf[n++]; number = number << 8;
//                number = number + buf[n++];
//        
//                
//                means_fixed[count] = number; 
//                //sprintf(msg,"means number is: %08X   %d\n", means_fixed[count], count);
//                //record(msg);
//                count++;
//        }
//        
//        /* Receive Header */
//        if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
//            perror("recv");
//            exit(1);
//        }
//         //printf("standards client h : received numbytes         '%d'\n",numbytes);
//         //printf("%s\n", buf);
//         
//         
//        /* Receive Data */ 
//        if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * STANDARDS_MATRIX_SIZE, 0)) == -1) {
//            perror("recv");
//            exit(1);
//        }
//        //printf("standards client d : received numbytes         '%d'\n",numbytes);
//        //printf("%s\n", buf);
//        n = 0;
//        count = 0;
//        while(n < numbytes)
//        {
//                number = buf[n++]; number = number << 8;
//                number = number + buf[n++]; number = number << 8;
//                number = number + buf[n++]; number = number << 8;
//                number = number + buf[n++];
//                
//                standards_fixed[count] = number; 
//                //sprintf(msg,"standards number is: %08X   %d\n", standards_fixed[count], count); record(msg);
//                count++;
//        }
//        
//                /* Receive Header */
//        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
//            perror("recv");
//            exit(1);
//        }
//         //printf("class header client : received numbytes         '%d'\n",numbytes);
//         //printf("%s\n", buf);
//         
//         
//        /* Receive Data */ 
//         int i;
//         for(i = 0; i < 1088; i++)
//         {
//            //if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES, 0)) == -1) {
//                if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * 50, 0)) == -1) {
//                perror("recv");
//                exit(1);
//            }
//            //sprintf(msg,"class data client: received numbytes         '%d' %d\n",numbytes, i); record(msg);
//
//            n = 0;
//            count = 0;
//            while(n < numbytes)
//            {
//                    number = buf[n++]; number = number << 8;
//                    number = number + buf[n++]; number = number << 8;
//                    number = number + buf[n++]; number = number << 8;
//                    number = number + buf[n++];
//
//                    class_fixed[i][count] = number; 
//                    //sprintf(msg,"class number is: %08X   %d  %d\n", class_fixed[i][count], i, count); record(msg);
//                    
//                    count++;
//            }
//         }
    
    
    
    
        uint32_t number;
     
        int n = 0;
        int count = 0;
        //char msg[256];
    
             /* Receive Header */
        if ((numbytes = recv(sockfd, buf, 256, 0)) == -1) {
            perror("recv");
            exit(1);
        }
         printf("class header client : received numbytes         '%d'\n",numbytes);
         printf("%s\n", buf);
         
         
        /* Receive Data */ 
         int i,j;
         /* For each line */
         //for(i = 0; i < 30; i++)
        // {
            // for(j = 0; j < 240; j++)
            // {
            //if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES, 0)) == -1) {
                if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * 640, 0)) == -1) {
                perror("recv");
                exit(1);
                }
                printf("class data client: received numbytes '%d' should be 2560\n",numbytes);// record(msg);

                n = 0;
                count = 0;
                while(n < numbytes)
                {
                    printf("in while\n");
                        //printf("%02X\n",(int)buf[n]);
                        number = buf[n++]; number = number << 8;
                        number = number + buf[n++]; number = number << 8;
                        number = number + buf[n++]; number = number << 8;
                        number = number + buf[n++];
                        //printf("%08X\n", number);
                        dark_matrix[0][0][count] = number; 
                        //sprintf(msg,"class number is: %08X   %d  %d\n", class_fixed[i][count], i, count); record(msg);

                        count++;
                }
                

                    
            // }
        // }
                         printf("Printing off datacube values in client\n");
                
                for(i = 0; i < 640;i++)
                {
                    sprintf(msg,"datacube[0][0][%d] number is: %08X\n", i, dark_matrix[0][0][i]); record(msg);
                }
    
    
    
    
    
    
    
    
    
    
    
    
 //       printf("Done reading classification vectors\n");
        /* */

 //           int j;
 //           for(i = 0; i < 1088; i++)
 //           {
 //               sprintf(msg,"meansfixed[%d]:     %08X\n", i, means_fixed[i]); record(msg);
 //               sprintf(msg,"standardsfixed[%d]:  %08X\n", i, standards_fixed[i]); record(msg);
 //               for(j = 0; j < 50; j++)
 //               {
 //                   sprintf(msg,"classfixed[%d][%d]:  %08X\n", i,j, class_fixed[i][j]); record(msg);
//                }
//            }
 //           printf("done printing\n");
            while(1)
            {
            
            }
    close(sockfd);

    return 0;
}
