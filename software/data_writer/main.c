/* 
 * File:   main.c
 * Author: Team Ross
 *
 * Created on January 3, 2015, 2:45 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 *  Simple program that is creating data files for the means, standard deviations, and classification parameters
 *  Will receive this information from resonon, but for now, the data being generated is just a counting pattern.
 *  and will be written as CSVs. 
 */
int main(int argc, char** argv) {
    char * MEANS_FILEPATH = "/resonon/input/means/mean.csv";
    char * STANDARDS_FILEPATH = "/resonon/input/standards/standard.csv";
    char * CLASS_FILEPATH = "/resonon/input/class/class.csv";
    FILE *outfile; // for writing
    int means_size = 1088;
    int standards_size = 1088;
    int num_classes = 50;
    int class_size = 1089;
    int var = 0;
    int i,j;
    
    int ** class_matrix;
    class_matrix = (int **) malloc(num_classes * class_size * sizeof (int));
    for( i=0; i < class_size; i++)
    {
        class_matrix[i] = (int *) malloc(num_classes * sizeof(int));
    }
    int counter = 0;
    for(i = 0; i < class_size; i++)
    {
        for( j = 0; j < num_classes; j++)
        {
            class_matrix[i][j] = counter;
            counter++;
        }
    }
    
    int means[means_size];
    int standards[standards_size];
    printf("size of an int %d\n", sizeof(var));
    
    for(i=0; i < means_size; i++)
    {
        means[i] = i;
    }
    
    for(i=0; i < standards_size; i++)
    {
        standards[i] = i;
    }
    
    /* Write the Means to a text file, should be ~4.3KB*/
    outfile = fopen(MEANS_FILEPATH, "a"); // write to this file
    for(i = 0; i < means_size; i++)
    {
        char msg[100];
        strstr(msg,"hello");
        if(i == standards_size -1)
        {
            sprintf(msg, "%d", means[i]);
            //fwrite(&standards[i], sizeof(int), 1, outfile);
            
        }
        else
        {
            sprintf(msg, "%d,",means[i]);
        }
        printf("flag1\n");
        printf(msg);
        fwrite(msg, 1, strlen(msg), outfile);
    }
    fclose(outfile);
    printf("flag2\n");
    
    /* Write the Standard Deviations to a text file, should be ~4.3KB*/
    outfile = fopen(STANDARDS_FILEPATH, "a"); // write to this file
    for(i = 0; i < standards_size; i++)
    {
        char msg[100];
        if(i == standards_size -1)
        {
            sprintf(msg, "%d", standards[i]);
            //fwrite(&standards[i], sizeof(int), 1, outfile);
            
        }
        else
        {
            sprintf(msg, "%d,",standards[i]);
        }
        fwrite(msg, sizeof (msg[0]), strlen(msg), outfile);
        
    }
    fclose(outfile);
    
    /* Write the Classification Coefficients to a text file, should be ~217KB*/
    //int counter = 0;
    int temp_counter;
    printf("flag1\n");
    outfile = fopen(CLASS_FILEPATH, "a"); // write to this file
    for(i = 0; i < class_size; i++) //class size is the number of columns
    {
        for(j = 0; j < num_classes; j++)
        {
            
                    char msg[100];
        if(i == (class_size* num_classes) -1)
        {
            sprintf(msg, "%d", class_matrix[i][j]);
            
        }
        else
        {
            sprintf(msg, "%d,",class_matrix[i][j]);
        }
                    
                    
        fwrite(msg,1,strlen(msg), outfile);
        printf(msg);    
            
            
            
            //temp_counter = counter;
            //temp_counter = temp_counter >> 3;
            //printf("%4x", temp_counter);
            //fwrite(&temp_counter, sizeof(int), 1, outfile);
            //counter++;
        }
    }
    fclose(outfile);
    printf("flag2\n");
    
    
    
    return (EXIT_SUCCESS);
}

