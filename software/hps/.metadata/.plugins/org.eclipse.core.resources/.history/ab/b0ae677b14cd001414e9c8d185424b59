/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: means.c                                                       *
 * Date:  January 3 2015                                                    *
 * Description: *
 *				*
 *				*
 
 ****************************************************************************/

#include "means.h"

int parseMeans() {
    
    record("MEANS: Inside parse means\n");
    
    FILE* file;
    int i;
    float var;

    struct fixed means_fixed[MEANS_MATRIX_SIZE];
	/* Read in Values from CSV */
    file = fopen(MEANS_PATH, "r");
//    printf("File info: %s  %d\n", MEANS_PATH, (int)file);
    
    var = 0;
    for(i = 0; i < MEANS_MATRIX_SIZE; i++)
    {


    	if(i == MEANS_MATRIX_SIZE -1)
        {
            fscanf(file, "%f", &means_fixed[i].input);

        }
        else 
        {
            fscanf(file, "%f,", &means_fixed[i].input);
        }

    	means_fixed[i].type = means;

    	/*Convert the value to fixed*/
    	float2fixed(means_fixed[i]);
        
    }
    close(file);
    
    /* means_fixed now has the final values to be written to fpga memory */
    return 0;
}
