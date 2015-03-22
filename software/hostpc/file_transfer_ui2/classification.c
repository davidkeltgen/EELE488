/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: classification.c                                              *
 * Date:  November 9 2014                                                   *
 * Description:        *
 ****************************************************************************/

#include "classification.h"
#include "fixed_point.h"

int parseClassParams() {
    
    record("CLASSIFICATION: inside parseClassParams\n");
    
    FILE* file;
    int i, j;
     
    fixed **class_fixed;

    class_fixed = (fixed **)malloc(sizeof(fixed*) * CLASSIFICATION_MATRIX_SIZE);
    for(i = 0; i < CLASSIFICATION_MATRIX_SIZE; i++)
    {
    	class_fixed[i] = (fixed *)malloc(NUM_CLASSES * sizeof(fixed));
    }
    
    //struct fixed class_fixed[CLASSIFICATION_MATRIX_SIZE][NUM_CLASSES];
    
    /* Read in Values from CSV */
    file = fopen(CLASSIFICATION_PATH, "r");
    
    for(i = 0; i < CLASSIFICATION_MATRIX_SIZE; i++)
    {
        for(j = 0; j < NUM_CLASSES; j++)
        {
            if(i * j < (CLASSIFICATION_MATRIX_SIZE * NUM_CLASSES - 1))
            {
            	fscanf(file, "%f", &class_fixed[i][j].input);
            }
            else
            {
                fscanf(file, "%f,", &class_fixed[i][j].input);

            }
            class_fixed[i][j].type = classes;

            /*Convert the value to fixed*/
            float2fixed(class_fixed[i][j]);
        }
    }
    
    close(file);
    
    /* standards_fixed now has the final values to be written to fpga memory */
    return 0;

    

}