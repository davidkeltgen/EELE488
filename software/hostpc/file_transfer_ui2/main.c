/* 
 * File:   main.c
 * Author: david
 *
 * Created on January 24, 2015, 12:48 PM
 */

 #include "main.h"

/*
 * 
 */
int main(int argc, char** argv) {
    printf("program started\n");
    record("MAIN: Program started.\n");
    
    int var, i, j;
    
    /* Load all the files */
    
    /* Parse the header file for dark. */
    var = parseHdr(dark);                                                       
    if (var == 0) {
        record("MAIN: Dark datacube header parsed correctly.\n");
        printHdr(dark);
        /* Parse the binary file. */
        parseBin(dark); 

    } else {
        record("MAIN: Dark datacube header did not parse correctly!\n");
    }
    record("MAIN: Dark datacube parsed\n");
    /* Parse the header file for response. */
    var = parseHdr(response); 

    if (var == 0) {
        record("MAIN: Response datacube parsed correctly.\n");
        printHdr(response);

        /* Parse the binary file. */
        var = parseBin(response);
    } else {
        record("MAIN: Response datacube did not parse correctly!\n");
    }
    
    parseMeans();
    
    parseStandards();
    
    parseClassParams();
    
    printf("MAIN: Printing off parsed values\n");
    
    printf("MAIN: means and standard deviation and classification parameters(first row)...\n");
    for (i = 0; i < 50; i++)
    {
        printf("%lf %lf %lf\n", means_matrix[i], standards_matrix[i], class_matrix[0][i] );
    }
    
    /* Send the files over the network */
    

    return (EXIT_SUCCESS);
}

