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

#include "defs.h"
#include "server.h"

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
    int numbytes = 0;
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
    if ((rv = getaddrinfo(argv, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    int is_connected = 0;
    while(!is_connected)
    {
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
    	if( p!= NULL)
    		is_connected = 1;
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
    
    // End of client setup
    int i,j;
    int n = 0;
    int count = 0;
    uint32_t number;

    while(1)
    {

    /* Receive Header */
    if ((numbytes = recv(sockfd, buf, HEADER_SIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }
     printf("Header : received numbytes '%d'\n",numbytes);
     printf("%s\n", buf);

     //send ack back
     printf("Sending acknowledgement after receiving header\n");
     sendAck();


     if (strcmp(buf,"means") == 0)
     {
    	 record("Received means header\n");
    	 int target_bytes = (sizeof(uint32_t) * MEANS_MATRIX_SIZE);
    	 int received_bytes = 0;
    	 while(received_bytes < target_bytes)
    	 {
			  	/* Receive Data */
				if ((numbytes = recv(sockfd, buf, sizeof(uint32_t) * MEANS_MATRIX_SIZE, 0)) == -1) {
					perror("recv");
					exit(1);
				}
				received_bytes = received_bytes + numbytes;
				printf("means data: received numbytes: %d   %d\n",numbytes, received_bytes);


				while(n < numbytes)
				{
					number = buf[n++]; number = number << 8;
					number = number + buf[n++]; number = number << 8;
					number = number + buf[n++]; number = number << 8;
					number = number + buf[n++];

					means_fixed[count] = number;
					count++;
				}
    	 } // end while received is less

        record("Received means data.\n");

        printf("Sending acknowledgement after means data\n");
        sendAck();
     }
     else if(strcmp(buf,"standards") == 0)
     {

    	 int target_bytes = (sizeof(uint32_t) * STANDARDS_MATRIX_SIZE);
    	 int received_bytes = 0;
    	 count = 0;
    	 n = 0;
        /* Receive Data */

    	 while(received_bytes < target_bytes)
		 {
				/* Receive Data */
				if ((numbytes = recv(sockfd, buf, sizeof(uint32_t) * STANDARDS_MATRIX_SIZE, 0)) == -1) {
					perror("recv");
					exit(1);
				}
				received_bytes = received_bytes + numbytes;
				printf("standards data: received numbytes: %d   %d\n",numbytes, received_bytes);


				while(n < numbytes)
				{
					number = buf[n++]; number = number << 8;
					number = number + buf[n++]; number = number << 8;
					number = number + buf[n++]; number = number << 8;
					number = number + buf[n++];

					standards_fixed[count] = number;
					//printf("CLIENT STANDARDS: %d\n",standard)
					count++;
				}
		 } // end while received is less

         record("Received standard deviation data.\n");

         printf("Sending acknowledgement after standard deviation data\n");
         sendAck();
     }
//     else if(strcmp(buf,"class") == 0)
//     {
//                 /* Receive Data */
//         int i;
//         for(i = 0; i < CLASS_MATRIX_SIZE; i++)
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
//         record("Received classification coefficient data.\n");
//     }
//     else if(strcmp(buf,"dark") == 0)
//     {
//          /* Receive Data */
//
//        datacube * dark_cube = malloc(sizeof (datacube));
//        dark_cube->lines = 30;
//        dark_cube->bands = 240;
//        dark_cube->samples = 640;
//        int num_values = dark_cube->bands * dark_cube->samples;
//
//        dark_matrix = (uint32_t **) malloc(num_values * sizeof (uint32_t));
//        for (i = 0; i < dark_cube->bands; i++) {
//            dark_matrix[i] = (uint32_t *) malloc(dark_cube->samples * sizeof (uint32_t));
//         }
//         /* For each band */
//             for(i = 0; i < 240; i++)
//             {
//                if ((numbytes = recv(sockfd, buf,  sizeof(uint32_t) * dark_cube->samples, 0)) == -1) {
//                perror("recv");
//                exit(1);
//                }
//                printf("class data client: received numbytes '%d' should be 2560\n",numbytes);// record(msg);
//
//
//
//                n = 0;
//                count = 0;
//                while(n < numbytes)
//                {
//                        number = buf[n++]; number = number << 8;
//                        number = number + buf[n++]; number = number << 8;
//                        number = number + buf[n++]; number = number << 8;
//                        number = number + buf[n++];
//                        dark_matrix[i][count] = number;
//
//                        count++;
//                }
//             }
//
//         record("Received dark datacube data.\n");
//     }
//     else if(strcmp(buf,"response") != 0)
//     {
//         record("Received response datacube data.\n");
//     }

          else if(strcmp(buf,"done") == 0)
          {
              record("Done Receving data.\n");
              return 0;
          }
     else
     {
         record("didnt receive anything appropriate header type\n");
     }
    } // end while 1


    // record("Printing off datacube values in client\n");

    // for(i = 0; i < 640;i++)
    // {
    //     sprintf(msg,"datacube[0][%d] number is: %08X\n", i, dark_matrix[0][i]); record(msg);
    // }
     record("Done printing\n");
     
     //while(1)
     //{
     //   usleep(20000);
     //}
    
     close(sockfd);

    return 0;
}

int closeClient(void)
{
    close(sockfd);  // parent doesn't need this
    return 0;
}
