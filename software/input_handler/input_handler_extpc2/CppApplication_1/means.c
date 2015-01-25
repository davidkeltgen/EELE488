/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: means.c                                                       *
 * Date:  January 3 2015                                                    *
 * Description:        *
 ****************************************************************************/

#include "means.h"

int parseMeans() {
    
    record("Inside parse means\n");
    
    FILE* file;
    
    int i;
    double var;
    means_size = 1088;
    
    /*Allocate space for class parameters*/
    means_matrix = (double *) malloc(means_size * sizeof (double));/*Allocate space for class parameters*/
    
    struct fixed means_fixed[means_size];
    
    file = fopen(MEANS_PATH, "r");
//    printf("File info: %s  %d\n", MEANS_PATH, (int)file);
    
    var = 0;
    for(i = 0; i < means_size; i++)
    {
        if(i == means_size -1)
        {
            fscanf(file, "%lf", &var);
            means_matrix[i] = var;
            means_fixed[i].type = means;
        }
        else 
        {
            fscanf(file, "%lf,", &var);
            means_matrix[i] = var;
            means_fixed[i].type = means;
        }
        //printf("means: %lf\n",var);
        
        
    }
    close(file);
    
    /*Convert the value to fixed*/
    for(i = 0; i < means_size; i++)
    {
        float2fixed(means_matrix[i], means_fixed[i]);
    }
    
    //free the raw value matrix....
    free(means_matrix);
    
    
    
    return 0;
}
