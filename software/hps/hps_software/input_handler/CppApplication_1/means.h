/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: means.h                                                       *
 * Date:  January 3 2015                                                    *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef MEANS_H
#define	MEANS_H

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
#define  MEANS_PATH         "/resonon/input/means/means.csv"

#define  MEANS_BASE_ADDRESS 

/* global vars */

/* 2D classification matrix*/
double * means_matrix;
int means_size;  /*Could be read in from header file */



//struct fixed * means_fixed; 

/* prototypes */
int parseMeans(void);

#endif	/* MEANS_H */