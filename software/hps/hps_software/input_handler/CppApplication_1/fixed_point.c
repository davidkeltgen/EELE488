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
 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SHIFT_AMOUNT_MEANS 8 // 2^16 = 65536

//#define SHIFT_MASK_MEANS ((1 << SHIFT_AMOUNT) - 1) // 65535 (all LSB set, all MSB clear)
/*
 * 
 */
struct fixed {
    int integer;
    float fraction;
    int final_value;
};

int main(int argc, char** argv) {

    //Mean - 32 byte with 8 for integer and 16 for fraction
    //example number is 102.875 (0x0066E000 in the fixed point representation)
                             //(0x0066 for integer, 0xE000 for fraction)
    struct fixed fxd_num;
    printf("hello\n");
     float var = 102.875;
     int max_frac_val = pow(2, SHIFT_AMOUNT_MEANS);//65536; //2^16
     
     fxd_num.integer = (int)var;
     
     /* Extract the fraction portion of the */
     fxd_num.fraction = var-(long)var;
     
     
     fxd_num.final_value = fxd_num.integer << SHIFT_AMOUNT_MEANS;
     
     int frac = max_frac_val * fxd_num.fraction;
     fxd_num.final_value = fxd_num.final_value + frac; // this is the value that will be written to the register
     printf("number to be written to register 0x%8X, %d", fxd_num.final_value, fxd_num.final_value); // should be 0x0066E000 
    
     return (EXIT_SUCCESS);
}

