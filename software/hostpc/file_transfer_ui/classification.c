/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: classification.c                                              *
 * Date:  November 9 2014                                                   *
 * Description:        *
 ****************************************************************************/

#include "classification.h"

int parseClassParams() {
    
    record("CLASSIFICATION: inside parseClassParams\n");
    
    FILE* file;
    int i, j;
    char msg[256];
    
    //if(matlab == 1)
    //{
    //    class_v[i][j]
    //}
     
    //else {
    
    /* Allocate space for fixed point struct array */
    class_fixed = (fixed **)malloc(sizeof(fixed*) * CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES);
    for(i = 0; i < CLASSIFICATION_MATRIX_SIZE; i++)
    {
    	class_fixed[i] = (fixed *)malloc(NUM_CLASSES * sizeof(fixed));
    }
   
    /* Read in Values from CSV */
    
    file = fopen(CLASSIFICATION_PATH, "r");
   
    for(i = 0; i < CLASSIFICATION_MATRIX_SIZE; i++)
    {
        
        for(j = 0; j < NUM_CLASSES; j++)
        {
            
             //sprintf(msg, "%s  %d\n", CLASSIFICATION_PATH, (int)file); record(msg);
            //printf("inside for\n");
            if((i * j) == (CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES - 1))
            {
                //printf("inside if\n");
            	fscanf(file, "%f", &class_fixed[i][j].input);
                //sprintf(msg,"CLASS: i: %d  value %f\n",i, class_fixed[i][j].input); record(msg);
                
            }
            else
            {
                fscanf(file, "%f,", &class_fixed[i][j].input);
            }
            
            float2fixed(&class_fixed[i][j]);
            class_v[i][j] = htonl(class_fixed[i][j].final_value);
        }
    }
    
    close(file);
    
    
    //}
    
    /* class_v now has the final values to be written to fpga memory */
    return 0;

    

}
