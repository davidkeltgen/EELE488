/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fpgamem.h                                                     *
 * Date:  March 17 2015                                                     *
 * Description: * 
 *              *  
 ****************************************************************************/

#ifndef FPGAMEM_H
#define	FPGAMEM_H

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
#define MAP_SIZE 0x800000
#define MAP_MASK (MAP_SIZE - 1)

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

/*global vars*/


/* Prototypes */
void record(const char* message);

#endif	/* LOGGER_H */

