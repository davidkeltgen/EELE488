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
#include "standards.h"
#include "classification.h"
#include "datacube.h"

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
	char msg[256];
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
    
    printf("server: waiting for connections...\n");

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

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            
            while(count <1)
            {
                printf("inside count\n");
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

            //uint32_t header =  htonl(MEANS_MATRIX_SIZE);
           // sprintf(msg,"means");
           // write(new_fd, msg, sizeof(msg));
            
            /* Send means data */

           // write(new_fd, means_v, sizeof(uint32_t) * MEANS_MATRIX_SIZE);
            
            /* Send standard deviation header*/
            //sprintf(msg,"standards");
            //write(new_fd, msg, 256);
            /* Send standard deviation data*/

            //write(new_fd, standards_v, sizeof(uint32_t) * STANDARDS_MATRIX_SIZE);
            /* Send coefficient header*/

            //header =  htonl(CLASSIFICATION_MATRIX_SIZE);
            //sprintf(msg,"class");
            //write(new_fd, msg, sizeof(msg));
            /* Send send coefficient data*/
            
            //int value = write(new_fd, class_v, sizeof(uint32_t) * CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES);

            //printf("# of bytes written: %d", value);
            /* Send dark datacube header */

            sprintf(msg,"dark datacube");
            write(new_fd, msg, sizeof(msg));
            
            /* Send dark datacube data*/
            int i,j;
            uint32_t * small_dark = malloc(sizeof(uint32_t) * 640);
           // for(i = 0;i < 30; i++)
           // {
             //   for(j = 0; j < 240; j++)
             //   {
                small_dark = dark_matrix[0][0];
                for(i = 0; i < 640; i++)
                {
                    //printf("sd %d\n", small_dark[i]);
                }
                printf("wrote %d bytes\n", write(new_fd, small_dark, sizeof(uint32_t) * 640));
             //   }
           // }
            
            //write(new_fd, dark_matrix, sizeof(uint32_t) * dark_cube->lines * dark_cube->bands * dark_cube->samples);
            
            
            /* Send light datacube header */
            
            //sprintf(msg,"light datacube");
            //write(new_fd, msg, sizeof(msg));
            
            /* Send light datacube data*/
            //write(new_fd, response_matrix, sizeof(uint32_t) * response_cube.lines * response_cube.bands * response_cube.samples);
            
            count++;
            //sleep(1);
            //}
            //close(new_fd);
            //exit(0);
            }
        }
       while(1)
       {
           
       }
        close(new_fd);  // parent doesn't need this
        exit(0);
    }

    return 0;
}
