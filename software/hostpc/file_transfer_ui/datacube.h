  /****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: datacube.h                                                    *
 * Date:  November 9 2014                                                   *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef DATACUBE_H
#define	DATACUBE_H

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
#define  DARK_BINARY_PATH         "/resonon/input/dark/darkCube.bil"
#define  DARK_HEADER_PATH         "/resonon/input/dark/darkCube.bil.hdr"
#define  RESPONSE_BINARY_PATH     "/resonon/input/response/responseCube.bil"
#define  RESPONSE_HEADER_PATH     "/resonon/input/response/responseCube.bil.hdr"

#define  BIP                      "bip"
#define  BIL                      "bil"
#define  BSQ                      "bsq"

#define  BIP                      "bip"
#define  BIL                      "bil"
#define  BSQ                      "bsq"



enum datacube_type 
        { 
          dark,
          response 
        }; 

typedef struct {
    char            description[1000];
    unsigned int    reflectance_scale_factor;
    double          framerate;
    double          shutter;
    double          gain;
    unsigned int    samples;
    unsigned int    lines;
    unsigned int    bands;
    unsigned int    header_offset;
    char            file_type[256];
    unsigned int    data_type;
    char            interleave[3];
    char            sensor_type[256];
    unsigned int    byte_order;
    unsigned int    x_start;
    unsigned int    y_start;
    double          wavelength[1000];
    unsigned int    bit_depth;
    
 
} datacube;

/* global vars */

datacube * dark_cube;
datacube * response_cube;

/*NOTE: need to create 16 bit datatype to make this program portable*/
/* dark matrix */
uint32_t *** dark_matrix;
/* response matrix */
uint32_t *** response_matrix;

uint32_t *** temp_matrix;



/* prototypes */
int parseHdr(int cube_type);
int parseBin(int cube_type);
void printHdr(int cube_type);

#endif	/* DATACUBE_H */

