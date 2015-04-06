/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: standards.c                                                   *
 * Date:  January 3 2015                                                    *
 * Description: *
 *				*
 *				*
 ****************************************************************************/

#include "standards.h"
#include "fixed_point.h"

int parseStandards() {

    record("MEANS: Inside parse standards\n");

    FILE* file;
    int i;
    char msg[256];
    
    //if(matlab == 1)
    //{
    //    
    //}
    
    //else
    //{
    
    /* Read in Values from CSV */
    file = fopen(STANDARDS_PATH, "r");
    sprintf(msg, "%s  %d\n", STANDARDS_PATH, (int)file); record(msg);


    for(i = 0; i < STANDARDS_MATRIX_SIZE; i++)
    {


    	if(i == STANDARDS_MATRIX_SIZE -1)
        {
            fscanf(file, "%f", &standards_fixed[i].input);

        }
        else
        {
            fscanf(file, "%f,", &standards_fixed[i].input);
        }

    	standards_fixed[i].type = standards;

    	/*Convert the value to fixed*/
    	float2fixed(&standards_fixed[i]);
        standards_v[i] = htonl(standards_fixed[i].final_value);

    }

    close(file);
    
    //}
    
    /* standards_fixed now has the final values to be written to fpga memory */
    return 0;
}
