/* 
 * File:   classification.h
 * Author: David Keltgen
 *
 * Created on January 3, 2015, 5:35 PM
 */

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
#define  CLASSIFICATION_PATH         "resonon/input/class/class.txt"

/* global vars */

/* 2D classification matrix*/
int ** class_matrix;

/* prototypes */
int parseClassParams(void);

#endif	/* CLASSIFICATION_H */