/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: standards.c                                                   *
 * Date:  January 3 2015                                                    *
 * Description:                                                         *
 ****************************************************************************/

#include "standards.h"

int parseStandards() {

    record("Inside parse standards\n");

    FILE* file;
    
    int i;
    double var;
    char c1, c2, c3, c4;
    
    standards_size = 1088;

    /*Allocate space for class parameters*/
    standards_matrix = (int *) malloc(standards_size * sizeof (int)); /*Allocate space for class parameters*/
    struct fixed standards_fixed[standards_size];
    
    file = fopen(STANDARDS_PATH, "r");
    printf("%s  %d\n", STANDARDS_PATH, file);

    for (i = 0; i < standards_size; i++) {
        if (i == standards_size - 1) {
            fscanf(file, "%lf", &var);
            standards_matrix[i] = var;
            standards_fixed[i].type = standards;
        } else {
            fscanf(file, "%lf,", &var);
            standards_matrix[i] = var;
            standards_fixed[i].type = standards;
        }

        printf("standard: %lf\n", var);
    }

close(file);

    /*Convert the value to fixed*/
    for(i = 0; i < standards_size; i++)
    {
        float2fixed(standards_matrix[i], standards_fixed[i]);
    }

//free the raw value matrix
free(standards_matrix);
return 0;
}
