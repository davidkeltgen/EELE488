/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fpgamem.h                                                     *
 * Date:  March 17 2015                                                     *
 * Description: * 
 *              *  
 ****************************************************************************/

#ifndef FPGAMEM_H
#define	FPGAMEM_H

/*
*********************************************************************************************************
*                                                 INCLUDE FILES
*********************************************************************************************************
*/
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "system.h"

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/ 
/*Mask size should cover everything for means, standard deviation, and classification parameters */
#define FPGA_BASE_LW		(0xFC000000)
#define REGRESSION_MAP_SIZE (0x40000000)
#define REGRESSION_MAP_MASK (REGRESSION_MAP_SIZE - 1)
#define HW_REGS_BASE 		( ALT_STM_OFST )
#define HW_REGS_SPAN 		( 0x04000000 )
#define HW_REGS_MASK 		( HW_REGS_SPAN - 1 )
#define MYBASE 0x21000

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

/*global vars*/


/* Prototypes */


#endif	/* FPGAMEM_H */

