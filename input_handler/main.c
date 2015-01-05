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
    int var, i;

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
    
    parseClassParams();
    
    parseMeans();
    
    parseStandards();
    
    printf("Printing off parsed values\n");
    
    printf("means and standard devation and classification paramters...\n");
    for (i = 65; i < 91; i++)
    {
        printf("%d %d %d\n", means_matrix[i], standards_matrix[i], class_matrix[0][i] );
    }
    

    /* Send matrices over DMA */


    return (EXIT_SUCCESS);
}

