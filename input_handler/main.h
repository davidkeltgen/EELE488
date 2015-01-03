
#ifndef MAIN_H
#define	MAIN_H

/*
*********************************************************************************************************
*                                                 INCLUDE FILES
*********************************************************************************************************
*/ 

#include <stdio.h>
#include "logger.h"

/* Filepaths for datacube files. */
/* For now, just starting with one response cube and one dark cube
 * of known type(bil). Later, will implement more dynamic way to find and load these files */

int main(int argc, char** argv);

enum datacube_type 
        { 
          dark,
          response 
        };

#endif	/* MAIN_H */

