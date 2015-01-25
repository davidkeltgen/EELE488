/* 
 * File:   defs.h
 * Author: david
 *
 * Created on January 25, 2015, 2:32 PM
 */

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
    int final_value;
    int type;
};




#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

