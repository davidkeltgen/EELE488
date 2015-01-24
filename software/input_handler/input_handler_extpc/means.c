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
    int means_size = 1088;  /*Could be read in from header file */
    int i, var;
    char c1,c2,c3,c4;
    
    /*Allocate space for class parameters*/
    means_matrix = (int *) malloc(means_size * sizeof (int));/*Allocate space for class parameters*/

    file = fopen(MEANS_PATH, "r");
//    printf("File info: %s  %d\n", MEANS_PATH, (int)file);
    
    var = 0;
    for(i = 0; i < means_size; i++)
    {
        fscanf(file, "%c%c%c%c", &c1,&c2,&c3,&c4);
        var = c1;                               /* Set to first character */ 
        var = var << 8;                         /* Shift var over 8 */                    
        var = var + c2;                         /* Add second character to var (LS 8 bits)*/
        var = var << 8;                         /* Shift var over 8 */                    
        var = var + c3;
        var = var << 8;                         /* Shift var over 8 */                    
        var = var + c4;
        var = var >> 24;
        means_matrix[i] = var;
       // printf("%c%c%c%c %d %d\n",c1,c2,c3,c4, means_matrix[i], var);
    }
    close(file);
    return 0;
}
