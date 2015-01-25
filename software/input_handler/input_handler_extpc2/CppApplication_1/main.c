/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                       *
 * File Name: main.c                                                        *
 * Date:  June 4 2014                                                       *
 * Description: Will provide the timeline for reading and parsing the 
 *              the different file types need to be sent to the FPGA.                           *  
 ****************************************************************************/



#include "main.h"

int main(int argc, char** argv) {
    printf("Starting.....\n");
    record("Program started.\n");
    int var, i, j;

    var = parseHdr(dark);                                                       /* Parse the header file for dark. */
    if (var == 0) {
        record("Dark datacube parsed correctly.\n");
        printHdr(dark);
        parseBin(dark); /* Parse the binary file. */

    } else {
        record("Dark datacube did not parse correctly!\n");
    }


    var = parseHdr(response); /* Parse the header file for response. */

    if (var == 0) {
        record("Response datacube parsed correctly.\n");
        printHdr(response);


        var = parseBin(response); /* Parse the binary file. */
        if (var == 1) {

        }
    } else {
        record("Response datacube did not parse correctly!\n");
    }
    
    parseMeans();
    
    parseStandards();
    
    parseClassParams();
    
    printf("Printing off parsed values\n");
    
    printf("means and standard deviation and classification parameters(first row)...\n");
    for (i = 0; i < 50; i++)
    {
        printf("%lf %lf %lf\n", means_matrix[i], standards_matrix[i], class_matrix[0][i] );
    }
    

    /* Send means, standard deviation and coefficient matrices over the bridge */
    
    for(i = 0; i < means_size;i++)
    {
        //means_fixed[i].final_value;
    }
    
    
    for(i = 0; i < standards_size;i++)
    {
        //standards_fixed[i].final_value;
    }
    
    for(i = 0; i < class_size;i++)
    {
        //standards_fixed[i].final_value;
        for(j = 0; j < num_classes;j++)
        {
            //class_fixed[i][j];
        }
    }
    
    // send datacube values
    


    return (EXIT_SUCCESS);
}

