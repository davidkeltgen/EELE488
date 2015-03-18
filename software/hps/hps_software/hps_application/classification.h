/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fixed_point.h                                                 *
 * Date:  November 10, 2014                                                 *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef CLASSIFICATION_H
#define	CLASSIFICATION_H

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
#define  CLASSIFICATION_PATH         "/resonon/input/class/class.csv"

/* global vars */

/* 2D classification matrix*/
double ** class_matrix;

int class_size;   /*Could be read in from header file */
int num_classes;   /*Could be read in from header file */

/* prototypes */
int parseClassParams(void);

#endif	/* CLASSIFICATION_H */

