
 
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

struct fixed {
    int integer;
    float fraction;
    uint32_t final_value;
    int type;
};




#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */
