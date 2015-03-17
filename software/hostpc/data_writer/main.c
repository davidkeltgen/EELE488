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
    char * MEANS_FILEPATH = "/resonon/input/means/means.csv";
    char * STANDARDS_FILEPATH = "/resonon/input/standards/standards.csv";
    char * CLASS_FILEPATH = "/resonon/input/class/class.csv";
    FILE *outfile; // for writing
    int means_size = 1088;
    int standards_size = 1088;
    int num_classes = 50;
    int class_size = 1089;
    int var = 0;
    int i,j,temp_counter;
    
    /* Write to class.csv*/
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
    printf("size of an int blahblabhlabh %d\n", sizeof(var));
    
    for(i=0; i < means_size; i++)
    {
        means[i] = i;
    }
    
    for(i=0; i < standards_size; i++)
    {
        standards[i] = i;
    }
    printf("flag1\n");
    temp_counter = 0;
    /* Write the Means to a text file*/
    outfile = fopen(MEANS_FILEPATH, "a+"); // write to this file
    for(i = 0; i < means_size; i++)
    {
        if(i == means_size -1)
        {
            fprintf(outfile, "%d", means[i]);
            
        }
        else
        {
            fprintf(outfile, "%d,",means[i]);
        }
        temp_counter++;
    }
    fclose(outfile);
    printf("Means temp_counter is %d\n", temp_counter);
    
    
    temp_counter = 0;
    /* Write the Standard Deviations to a text file, should be ~4.3KB*/
    outfile = fopen(STANDARDS_FILEPATH, "a+"); // write to this file
    for(i = 0; i < standards_size; i++)
    {
        char msg[100];
        if(i == standards_size -1)
        {
            fprintf(outfile, "%d", standards[i]);
        }
        else
        {
            fprintf(outfile, "%d,",standards[i]);
        }
        temp_counter++;
    }
    fclose(outfile);
    printf("Standards temp_counter is %d\n", temp_counter);
    
    temp_counter = 0;
    /* Write the Classification Coefficients to a csv file*/

    outfile = fopen(CLASS_FILEPATH, "a+"); // write to this file
    for(i = 0; i < class_size; i++) //class size is the number of columns
    {
        for(j = 0; j < num_classes; j++)
        {
            char msg[100];
            if(i == (class_size* num_classes) -1)
            {
                fprintf(outfile, "%d", class_matrix[i][j]); 
            }
            else
            {
                fprintf(outfile, "%d,",class_matrix[i][j]);
            }
            temp_counter++;
        }
    }
    fclose(outfile);
    printf("Classification temp_counter is %d\n", temp_counter);
    
    
    
    return (EXIT_SUCCESS);
}

