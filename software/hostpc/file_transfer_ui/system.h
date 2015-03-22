/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: system.h                                                      *
 * Date:  March 17 2015                                                     *
 * Description: Lists all of the required C library includes. These are     * 
 *				placed in one header file so that the other header files    *
 *				only have to include system.h                               *
 ****************************************************************************/

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
//#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include "logger.h"
#include "defs.h"



#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

