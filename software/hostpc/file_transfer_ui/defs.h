
 
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

enum matrix_type {
means,
standards,
classes
};

#define SHIFT_AMOUNT_MEANS 16 // 2^16 = 65536
#define SHIFT_AMOUNT_STANDARDS 8 //2^8 = 255
#define SHIFT_AMOUNT_CLASSES 8 //2^7 = 127

#define MATLAB  1

#define GOPSPERFRAME


#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

