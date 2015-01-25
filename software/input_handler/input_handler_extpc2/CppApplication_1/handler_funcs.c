#include "system.h"

#define SHIFT_AMOUNT_MEANS 16 // 2^16 = 65536
#define SHIFT_AMOUNT_STANDARDS 8 //2^8 = 255
#define SHIFT_AMOUNT_CLASSES 8 //2^7 = 127
void float2fixed (double in_double, struct fixed in_value)
{
    printf("start float2fixed\n");
    printf("double that will be converted: %lf\n", in_double);
    int shift_num; 
    
    if(in_value.type == means)
    {   // 8 integer bits 16 fraction bits
        printf("means value being converted\n");
        shift_num = SHIFT_AMOUNT_MEANS;
        
        
    }
    if(in_value.type == standards)
    {
        // 16 integer bits, 8 fraction bits
        printf("standards value being converted\n");
        shift_num = SHIFT_AMOUNT_STANDARDS;
    }
    if(in_value.type == classes)
    {
        printf("classes value being converted\n");
        // 1 sign bit, 15 int bits, 8 fraction bits
        // do something
        shift_num = SHIFT_AMOUNT_CLASSES;
        // for now lets ignore the sign bit, and treat
        // it as 16 integer bits
    }
    int max_frac_val = pow(2, shift_num);
    in_value.integer = (int)in_double;
     
    in_value.final_value = in_value.integer << SHIFT_AMOUNT_MEANS;
     
     /* Extract the fraction portion of the */
    in_value.fraction = in_double-(long)in_double;
    
    int frac = max_frac_val * in_value.fraction;
    in_value.final_value = in_value.final_value + frac; // this is the value that will be written to the register
    printf("number to be written to register 0x%8X, %d\n", in_value.final_value, in_value.final_value); // should be 0x0066E000
}

