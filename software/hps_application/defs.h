
 
 /****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: defs.h                                                        *
 * Date:  January 25 2015                                                   *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/

#ifndef DEFS_H
#define	DEFS_H

#ifdef	__cplusplus
extern "C" {
#endif
#define  MEANS_MATRIX_SIZE                      512
#define  STANDARDS_MATRIX_SIZE                  512
#define  CLASS_MATRIX_SIZE						512
#define  NUM_CLASSES                            50

enum matrix_type {
means,
standards,
classes
};

uint32_t standards_fixed[STANDARDS_MATRIX_SIZE];
uint32_t class_fixed[CLASS_MATRIX_SIZE][NUM_CLASSES];
uint32_t means_fixed[MEANS_MATRIX_SIZE];




#define SHIFT_AMOUNT_MEANS 16 // 2^16 = 65536
#define SHIFT_AMOUNT_STANDARDS 8 //2^8 = 255
#define SHIFT_AMOUNT_CLASSES 8 //2^7 = 127

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
uint32_t ** dark_matrix;
/* response matrix */
uint32_t ** response_matrix;


#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

