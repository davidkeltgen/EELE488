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
#define  STANDARDS_PATH         "resonon/input/standards/standard.txt"

/* global vars */

/* 2D classification matrix*/
int * standards_matrix;

/* prototypes */
int parseStandards(void);

#endif	/* STANDARDS_H */

