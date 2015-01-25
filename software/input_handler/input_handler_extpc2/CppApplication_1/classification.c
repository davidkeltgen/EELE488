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
    char c1,c2,c3,c4;
    
    class_size= 1089;
    num_classes = 50; 
     
    /*Allocate space for class parameters*/
    class_matrix = (int **) malloc(num_classes * class_size * sizeof (int));
    for(i = 0; i < class_size; i++)
    {
        class_matrix[i] = (int *) malloc(num_classes * sizeof(int));
    }
    
    file = fopen(CLASSIFICATION_PATH, "r");
    printf("%s  %d\n", CLASSIFICATION_PATH, file);
    
    var = 0;
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
        fscanf(file, "%lf,", &var);
        class_matrix[i][j] = var;
        //printf("class %lf\n",var);
        }
    }
    
        /*Convert the value to fixed*/
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
            //float2fixed(class_matrix[i][j], class_fixed[i][j]);
        }
    }
    
    //free the raw value matrix
    return 0;

    

}
