#include "system.h"

#define SHIFT_AMOUNT_MEANS 8 // 2^16 = 65536

uint32_t float2fixed (double in_double, struct fixed in_value)
{
    //int shift_num = 
    if(in_value.type == means)
    {   // 8 integer bits 15 fraction bits
        // do something
    }
    if(in_value.type == standards)
    {
        // 16 integer bits, 8 fraction bits
        // do something
    }
    if(in_value.type == classes)
    {
        // 1 sign bit, 15 int bits, 8 fraction bits
        // do something
        
        // for now lets ignore the sign bit, and treat
        // it as 16 integer bits
    }
}

