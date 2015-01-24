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
 */
int main(int argc, char** argv) {
    char * MEANS_FILEPATH = "D:/David/c_code/EELE488/input_handler/resonon/input/means/mean.txt";
    char * STANDARDS_FILEPATH = "D:/David/c_code/EELE488/input_handler/resonon/input/standards/standard.txt";
    char * CLASS_FILEPATH = "D:/David/c_code/EELE488/input_handler/resonon/input/class/class.txt";
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
        fwrite(&means[i], sizeof(int), 1, outfile);
    }
    fclose(outfile);
    
    /* Write the Standard Deviations to a text file, should be ~4.3KB*/
    outfile = fopen(STANDARDS_FILEPATH, "a"); // write to this file
    for(i = 0; i < means_size; i++)
    {
        fwrite(&standards[i], sizeof(int), 1, outfile);
    }
    fclose(outfile);
    
    /* Write the Classification Coefficients to a text file, should be ~217KB*/
    int counter = 0;
    int temp_counter;
    
    outfile = fopen(CLASS_FILEPATH, "a"); // write to this file
    for(i = 0; i < class_size; i++)
    {
        for(j = 0; j < num_classes; j++)
        {
            temp_counter = counter;
            //temp_counter = temp_counter >> 3;
            printf("%4x", temp_counter);
            fwrite(&temp_counter, sizeof(int), 1, outfile);
            counter++;
        }
    }
    fclose(outfile);
    
    
    
    
    return (EXIT_SUCCESS);
}

