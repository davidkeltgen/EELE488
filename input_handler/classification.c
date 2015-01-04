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
    int class_size = 1089;
    int num_classes = 50;
    int i, j, var;
     
    /*Allocate space for class parameters*/
    class_matrix = (int **) malloc(num_classes * class_size * sizeof (int));
    for(i = 0; i < class_size; i++)
    {
        class_matrix[i] = (int *) malloc(num_classes * sizeof(int));
    }
    
    
    file = fopen(CLASSIFICATION_PATH, "r");
    printf("%s  %d\n", CLASSIFICATION_PATH, file);
    char c1,c2,c3,c4;
    var = 0;
    int var2;
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
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
            class_matrix[i][j] = var;
            if(i < 10)
            {
            //printf("%c %c %c %c ", c1,c2,c3,c4);
            //printf("%d %d\n", var, class_matrix[i][j]);
            }
        }
        //printf("\n");
    }
    
    /*Print value to verify it read properly*/
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
            if(i < 10)
            {
            printf("%d ",class_matrix[i][j]);
            }
        }
        printf("\n");
    }
}