/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: logger.h                                                      *
 * Date:  March 17 2015                                                     *
 * Description: * 
 *              *  
 ****************************************************************************/

#ifndef LOGGER_H
#define	LOGGER_H

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

#define  FILEPATH   "C:/log/hps_log.log"

/* global vars */

/* prototypes */
void record(const char* message);

#endif	/* LOGGER_H */

