/* 
 * File:   classification.h
 * Author: David Keltgen
 *
 * Created on November 10, 2014, 1:42 PM
 */

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
int ** class_matrix;

int class_size;   /*Could be read in from header file */
int num_classes;   /*Could be read in from header file */

/* prototypes */
int parseClassParams(void);

#endif	/* CLASSIFICATION_H */

