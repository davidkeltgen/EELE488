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
#include "fixed_point.h"

int parseMeans() {
    
    record("MEANS: Inside parse means\n");
    char msg[256];
    FILE* file;
    int i;
    float var;

    //if(matlab == 1)
    //{
    //    
    //}
    
    //else{
    
	/* Read in Values from CSV */
    file = fopen(MEANS_PATH_CSV, "r");
    record(msg);
    
    for(i = 0; i < MEANS_MATRIX_SIZE; i++)
    {

    	if(i == MEANS_MATRIX_SIZE -1)
        {
            fscanf(file, "%f", &means_fixed[i].input);
            sprintf(msg,"MEANS: i: %d  value %f\n",i, means_fixed[i].input); record(msg);

        }
        else 
        {
            fscanf(file, "%f,", &means_fixed[i].input);
            sprintf(msg,"MEANS: i: %d  value %f\n",i, means_fixed[i].input); record(msg);
        }

    	means_fixed[i].type = means;

    	/*Convert the value to fixed*/
    	float2fixed(&means_fixed[i]);
        means_v[i] = htonl(means_fixed[i].final_value);
        
    }
    close(file);
    
    //}
    
    /* means_v now has the final values to be written to fpga memory */
    return 0;
}
