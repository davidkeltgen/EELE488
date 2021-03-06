/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: standards.h                                                   *
 * Date:  January 3 2015                                                    *
 * Description:                                                             * 
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef STANDARDS_H
#define	STANDARDS_H

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
#define  STANDARDS_PATH        	 "/resonon/input/standards/standards.csv"
#define  STANDARDS_BASE_ADDRESS
#define  STANDARDS_MATRIX_SIZE	 1088   /*Could be read in from header file */

/* global vars */

/* 2D classification matrix*/
double * standards_matrix;
fixed standards_fixed[STANDARDS_MATRIX_SIZE];

uint32_t standards_v[STANDARDS_MATRIX_SIZE];

/* prototypes */
int parseStandards(void);

#endif	/* STANDARDS_H */

