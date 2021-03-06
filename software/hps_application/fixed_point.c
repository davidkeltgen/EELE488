/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fixed_point.c                                                 *
 * Date:  March 17 2015                                                     *
 * Description: *  
 *				*
 *				*
 *				*
 ****************************************************************************/
 
#include "system.h"
#include "fixed_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SHIFT_AMOUNT_MEANS 8 // 2^16 = 65536

//#define SHIFT_MASK_MEANS ((1 << SHIFT_AMOUNT) - 1) // 65535 (all LSB set, all MSB clear)
/*
 * 
 */


int float2fixed(fixed in_value) {

	char msg[256];
	record("FIXEDPOINT: start float2fixed\n");
	sprintf(msg, "double that will be converted: %lf\n", in_value.input); record(msg);

    int shift_num;

    if(in_value.type == means)
    {   // 8 integer bits 16 fraction bits
        record("FIXEDPOINT: means value being converted\n");
        shift_num = SHIFT_AMOUNT_MEANS;


    }
    if(in_value.type == standards)
    {
        // 16 integer bits, 8 fraction bits
        record("FIXEDPOINT: standards value being converted\n");
        shift_num = SHIFT_AMOUNT_STANDARDS;
    }
    if(in_value.type == classes)
    {
        record("FIXEDPOINT: classes value being converted\n");
        // 1 sign bit, 15 int bits, 8 fraction bits
        // do something
        shift_num = SHIFT_AMOUNT_CLASSES;
        // for now lets ignore the sign bit, and treat
        // it as 16 integer bits
    }

    //Mean - 32 byte with 8 for integer and 16 for fraction
    //example number is 102.875 (0x0066E000 in the fixed point representation)
                              //(0x0066 for integer, 0xE000 for fraction)

     //float var = 102.875;
    float var = in_value.input;
	int max_frac_val = pow(2, shift_num);//65536; //2^16
     
	/*Subtract the fraction */
    in_value.integer = (int)var;
     
     /* Extract the fraction portion of the integer */
    in_value.fraction = var-(long)var;
     
    in_value.final_value = in_value.integer << shift_num;
     
    int frac = max_frac_val * in_value.fraction;
    in_value.final_value = in_value.final_value + frac; // this is the value that will be written to the register
    sprintf(msg, "FIXEDPOINT: Number to be written to register 0x%8X, %d", in_value.final_value, in_value.final_value); // should be 0x0066E000
    record(msg);
     /*Since pointer to the fixed number struct was passed in, that is what will be updated */
     
     return (EXIT_SUCCESS);
}

