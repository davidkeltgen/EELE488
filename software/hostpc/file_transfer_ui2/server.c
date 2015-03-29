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

#include "means.h"

#define PORT "3490"  // the port users will be connecting to

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

int sendall(int s, char *buf, int *len)
{
    printf("in sendall\n");
    printf("length: %d\n", *len);
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        printf("number of bytes sent: %d\n", n);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}

int server(void)
{
	record("SERVER: Server started\n");
	char msg[255];
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
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

    
    //   char array[10000];
    //    strcpy(array, "");
    //   char temp[10];
    //   int i;
    //   for(i = 0; i < 125; i++)
    //   {
    //       sprintf(temp, "%d", i);
    //       printf("%s\n", temp);
    //       strcat(array, temp);
    //       //array[10 * i] = temp;
    //   }
    //   printf("%s\n", array);
    //   for(i = 0; i < 4096; i++)
    //   {
           //printf("%c", array[i]);
    //   }
    //   printf("\n");
    
    //printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
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
        

       int count = 0;
       /*micro time*/
       struct timeval tv;
       struct timezone *tz;
       struct tm *tm;
       
       /* Send means header */
       
       
       /* Send means data */
       
       /* Send standard deviation header*/
       
       /* Send standard deviation data*/
       
       /* Send coefficient header*/
       
       /* Send send coefficient data*/
       
       /* Send dark datacube header*/
       
       /* Send dark datacube data*/
       
       //uint32_t smallarr[50];
       //int i;
       //for(i = 0; i < 50; i++)
       //{
       //     smallarr[i] = htonl(means_fixed[i].final_value);
       //}


        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            
            //while(count <1)
            //{
            gettimeofday(&tv, &tz);
            tm = localtime(&tv.tv_sec);
            sprintf(msg, "%02d:%02d:%02d:%03d %d\0", tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(tv.tv_usec / 1000), count);
            //sprintf(msg, "%X", )
           // printf("%s\n", msg);
            //if (send(new_fd, msg, 255, 0) == -1)
            //{
            //   perror("send");
            //}
            sleep(3);
            
            /* Send means header */
       
            int means_matrix_size = 1088;
            uint32_t value2 =  htonl(means_matrix_size);
            printf("means size: %08d", value2);
            write(new_fd, &value2, sizeof(means_matrix_size));
       
            /* Send means data */

            write(new_fd, means_v, sizeof(uint32_t) * MEANS_MATRIX_SIZE );
            
            /* Send standard deviation header*/

            /* Send standard deviation data*/

            /* Send coefficient header*/

            /* Send send coefficient data*/

            /* Send dark datacube header*/

            /* Send dark datacube data*/
            
            
            
            
            
            
            
            
            
            
            
            
            
            //printf("%X\n", means_fixed[49].final_value);
            //uint32_t value =  htonl(means_fixed[49].final_value);
            //printf("%X\n", value);
            //printf("%X\n", ntohl(value));
            //printf("%X\n",means_fixed[49].final_value);
            //printf("sizeof final_value: %d", sizeof(means_fixed[49].final_value));
            //if (send(new_fd, &means_fixed[49].final_value, sizeof(uint32_t), NULL) == -1)
            //if (send(new_fd, &value, sizeof(uint32_t), NULL) == -1)
            // {
            //   perror("send");
            //}
            
            
            //sleep(1);
            
            //write(new_fd, &means_matrix_size, sizeof(means_matrix_size));
            
            //write(new_fd, MEANS_MATRIX_SIZE, sizeof(MEANS_MATRIX_SIZE));
                    
            // sleep(1);       
            
            
            
            //int var = 10000;
            //printf("send all: %d\n", sendall(new_fd, (char)means_fixed_sending, &MEANS_MATRIX_SIZE));
            
            //count++;
            //sleep(1);
            //}
            close(new_fd);
            exit(0);
            
        }
       
       //while(1)
       //{
       //    
       //}
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
