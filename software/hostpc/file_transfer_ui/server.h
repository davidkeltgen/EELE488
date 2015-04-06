/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: server.h                                                      *
 * Date:  March 17 2015                                                     *
 * Description:                                                             * 
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef SERVER_H
#define	SERVER_H

/*
*********************************************************************************************************
*                                                 INCLUDE FILES
*********************************************************************************************************
*/ 

#include "system.h"

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/ 

/* global vars */

int new_fd; //new connection on new_fd

/* prototypes */
int server(void);
int sendMeans(void);
int sendStandards(void);
int sendClass(void);
int sendDatacube(int cube_type);
int closeServer();

#endif	/* SERVER_H */