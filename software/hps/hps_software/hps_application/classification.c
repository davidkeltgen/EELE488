/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: classification.c                                              *
 * Date:  November 9 2014                                                   *
 * Description:        *
 ****************************************************************************/

#include "classification.h"

int parseClassParams() {
    
    record("inside parseClassParams\n");
    
    FILE* file;
    int i, j;
    double var;
    //char c1,c2,c3,c4;
    
    class_size= 1089;
    num_classes = 50; 
     
    /*Allocate space for class parameters*/
    class_matrix = (double **) malloc(num_classes * class_size * sizeof (double));
    for(i = 0; i < class_size; i++)
    {
        class_matrix[i] = (double *) malloc(num_classes * sizeof(double));
    }
    
    struct fixed class_fixed[class_size][num_classes];
    
    file = fopen(CLASSIFICATION_PATH, "r");
    printf("%s  %d\n", CLASSIFICATION_PATH, (int)file);
    
    var = 0;
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
            if(i * j < (class_size * num_classes - 1))
            {
                
            }
            else
            {
                fscanf(file, "%lf,", &var);
                class_matrix[i][j] = var;
                class_fixed[i][j].type = classes;
                //printf("class %lf\n",var);
            }
        }
    }
    
    close(file);
    
    float2fixed(class_matrix[0][0], class_fixed[0][0]);
    
        /*Convert the value to fixed*/
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
            //float2fixed(class_matrix[i][j], class_fixed[i][j]);
        }
    }
    
    //free the raw value matrix
        for(i = 0; i < class_size; i++)
    {
        class_matrix[i] = (double *) malloc(num_classes * sizeof(double));
    }
    return 0;

    

}