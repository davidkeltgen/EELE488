/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: standards.h                                                   *
 * Date:  January 3 2015                                                    *
 * Description:          *                                           *
 ****************************************************************************/

#ifndef STANDARDS_H
#define	STANDARDS_H

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
#define  STANDARDS_PATH         "/resonon/input/standards/standard.csv"

#define  STANDARDS_BASE_ADDRESS

/* global vars */

/* 2D classification matrix*/
double * standards_matrix;
int standards_size; /*Could be read in from header file */

/* prototypes */
int parseStandards(void);

#endif	/* STANDARDS_H */

