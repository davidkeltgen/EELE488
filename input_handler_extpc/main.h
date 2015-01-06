
#ifndef MAIN_H
#define	MAIN_H

/*
*********************************************************************************************************
*                                                 INCLUDE FILES
*********************************************************************************************************
*/ 

#include "system.h"
#include "logger.h"
#include "means.h"
#include "standards.h"
#include "classification.h"
#include "datacube.h"

/* Filepaths for datacube files. */
/* For now, just starting with one response cube and one dark cube
 * of known type(bil). Later, will implement more dynamic way to find and load these files */

int main(int argc, char** argv);


#endif	/* MAIN_H */

