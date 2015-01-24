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
    int class_size = 1089;  /*Could be read in from header file */
    int num_classes = 50;   /*Could be read in from header file */
    int i, j, var;
    char c1,c2,c3,c4;
     
    /*Allocate space for class parameters*/
    class_matrix = (int **) malloc(num_classes * class_size * sizeof (int));
    for(i = 0; i < class_size; i++)
    {
        class_matrix[i] = (int *) malloc(num_classes * sizeof(int));
    }
    
    file = fopen(CLASSIFICATION_PATH, "r");
    printf("%s  %d\n", CLASSIFICATION_PATH, file);
    char msg[100];
    var = 0;
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
            sprintf(msg,"%d, %d, %d \n", class_matrix[i][j], i , j);
            record(msg);
        }

    }
    
    return 0;

    

}
