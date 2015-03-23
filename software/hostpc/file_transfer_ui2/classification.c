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
     
    

    class_fixed = (fixed **)malloc(sizeof(fixed*) * CLASSIFICATION_MATRIX_SIZE);
    for(i = 0; i < CLASSIFICATION_MATRIX_SIZE; i++)
    {
    	class_fixed[i] = (fixed *)malloc(NUM_CLASSES * sizeof(fixed));
    }
    
    //struct fixed class_fixed[CLASSIFICATION_MATRIX_SIZE][NUM_CLASSES];
    float var;
    /* Read in Values from CSV */
    
    file = fopen(CLASSIFICATION_PATH, "r");
    //fscanf(file, "%d,", &var);
    //printf("var: %d\n", var);
    //fscanf(file, "%d,", &var);
    //printf("var: %d\n", var);
    //fscanf(file, "%d,", &var);
    //printf("var: %d\n", var);
    
   
    
    int counter = 0;
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
                
            }
            else
            {
                //sprintf(msg,"File info: %s  %d\n", CLASSIFICATION_PATH, (int)file);
                fscanf(file, "%f,", &class_fixed[i][j].input);
               // sprintf(msg,"inside else %d %d %d %d \n", i,j,var, (int)file); record(msg);
                //sprintf(msg,"var :%f\n", class_fixed[i][j].input); record(msg);

            }
            //class_fixed[i][j].type = classes;
            //printf("%d\n", counter++);
            /*Convert the value to fixed*/
            float2fixed(&class_fixed[i][j]);
        }
    }
    
    close(file);
    
    /* class_fixed now has the final values to be written to fpga memory */
    return 0;

    

}
