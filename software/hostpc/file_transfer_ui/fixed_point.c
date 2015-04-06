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


int float2fixed(fixed * in_value) {

	char msg[256];
	//record("FIXEDPOINT: start float2fixed\n");
	//sprintf(msg, "FIXEDPOINT: Double that will be converted: %lf\n", in_value.input); record(msg);
        //in_value->input = 102.875;
    int shift_num;
    //printf("FIXEDPOINT: type %d\n", in_value->type);
    //printf("means %d\n", means);
    if(in_value->type == means)
    {   // 8 integer bits 16 fraction bits
        //record("FIXEDPOINT: means value being converted\n");
        shift_num = SHIFT_AMOUNT_MEANS;


    }
    if(in_value->type == standards)
    {
        // 16 integer bits, 8 fraction bits
        //record("FIXEDPOINT: standards value being converted\n");
        shift_num = SHIFT_AMOUNT_STANDARDS;
    }
    if(in_value->type == classes)
    {
        //record("FIXEDPOINT: classes value being converted\n");
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
    float var = in_value->input;
	int max_frac_val = pow(2, shift_num);//65536; //2^16
     
	/*Subtract the fraction */
    in_value->integer = (int)var;
     
     /* Extract the fraction portion of the integer */
    in_value->fraction = var-(long)var;
     //printf("FIXEDPOINT: fraction %f\n", in_value->fraction);
     //printf("FIXEDPOINT: shift_num %f\n", shift_num);
    in_value->final_value = in_value->integer << shift_num;
     
    int frac = max_frac_val * in_value->fraction;
    //printf("FIXEDPOINT: frac %d\n", frac);
    in_value->final_value = in_value->final_value + frac; // this is the value that will be written to the register
    //printf("FIXEDPOINT: final %d\n", in_value->final_value);
    //printf("FIXEDPOINT: integer %d\n", in_value->integer);
    //sprintf(msg, "FIXEDPOINT: Number to be written to register 0x%8X, %d\n", in_value.final_value, in_value.final_value); // should be 0x0066E000
   // record(msg);
     /*Since pointer to the fixed number struct was passed in, that is what will be updated */
     
     return 0;
}

int fixed2float(uint32_t * in_value) {
    
    /* Assuming the number is an unsigned integer*/
    /* number can range from 0 to 2^32*/
    
    //example 0x00000A0A0
    
}

