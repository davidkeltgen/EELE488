/* 
 * File:   logger.h
 * Author: David Keltgen
 *
 * Created on May 21, 2014, 6:06 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <stdio.h>
#include <string.h>


#define  FILEPATH   "hps_log.txt"

void record(const char* message);

#endif	/* LOGGER_H */

