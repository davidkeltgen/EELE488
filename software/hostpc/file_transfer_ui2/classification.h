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
#include "fixed_point.h"

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/ 
#define  CLASSIFICATION_PATH         	"/resonon/input/class/class.csv"
#define  CLASSIFICATION_MATRIX_SIZE     1088   /*Could be read in from header file */
#define  NUM_CLASSES			50

/* global vars */

/* 2D classification matrix*/
double ** class_matrix;
fixed **class_fixed;

uint32_t class_v[CLASSIFICATION_MATRIX_SIZE][NUM_CLASSES];

int class_size;   /*Could be read in from header file */
int num_classes;   /*Could be read in from header file */

/* prototypes */
int parseClassParams(void);

#endif	/* CLASSIFICATION_H */

