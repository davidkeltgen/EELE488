/* 
 * File:   stats.h
 * Author: david
 *
 * Created on November 10, 2014, 1:41 PM
 */

#ifndef STATS_H
#define	STATS_H

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
#define  STATS_PATH         "resonon/input/stats/stat.txt"

/* global vars */

/* 2D classification matrix*/
int ** class_matrix;

/* prototypes */
int parseClassParams(void);

#endif	/* STATS_H */

