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
    int standards_size = 1088;  /*Could be read in from header file */
    int i, var;
    char c1,c2,c3,c4;
    
    /*Allocate space for class parameters*/
    standards_matrix = (int *) malloc(standards_size * sizeof (int));/*Allocate space for class parameters*/

    file = fopen(STANDARDS_PATH, "r");
    printf("%s  %d\n", STANDARDS_PATH, file);
    
    var = 0;
    for(i = 0; i < standards_size; i++)
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
        standards_matrix[i] = var;
    }
    return 0;
}
