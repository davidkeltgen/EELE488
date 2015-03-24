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
#include "fixed_point.h"

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/ 
#define  MEANS_PATH        	 	"/resonon/input/means/means.csv"
#define  MEANS_BASE_ADDRESS
#define  MEANS_MATRIX_SIZE		1088   /*Could be read in from header file */

/* global vars */

/* 2D classification matrix*/
double * means_matrix;
fixed means_fixed[MEANS_MATRIX_SIZE];


/* prototypes */
int parseMeans(void);

#endif	/* MEANS_H */
