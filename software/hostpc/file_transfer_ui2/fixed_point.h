/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fixed_point.h                                                 *
 * Date:  March 17 2015                                                     *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef FIXED_POINT_H
#define	FIXED_POINT_H

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


/* global vars */

 typedef struct{
    float input;
    int integer;
    float fraction;
    uint32_t final_value;
    int type;
}fixed;

/* prototypes */
int float2fixed(fixed * in_value);

#endif	/* FIXED_POINT_H */
