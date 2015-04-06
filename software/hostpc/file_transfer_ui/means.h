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
#define  MEANS_PATH_CSV        	 	"/resonon/input/means/means.csv"
#define  MEANS_PATH_MATLAB              ""
#define  MEANS_BASE_ADDRESS             
#define  MEANS_MATRIX_SIZE		512   /*Could be read in from header file */

/* global vars */

/* Array of structs used to parse an int/double to fixed point notation*/
fixed means_fixed[MEANS_MATRIX_SIZE];

/* Vector to be sent to the HPS*/
uint32_t means_v[MEANS_MATRIX_SIZE];

/* prototypes */
int parseMeans(void);

#endif	/* MEANS_H */
