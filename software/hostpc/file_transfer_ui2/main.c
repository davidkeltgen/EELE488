/* 
 * File:   main.c
 * Author: david
 *
 * Created on January 24, 2015, 12:48 PM
 */

#include "main.h"
#include "fixed_point.h"

/*
 * 
 */
int main(int argc, char** argv) {
    printf("program started\n");
    record("MAIN: Program started.\n");
    char msg[256];
    
    int var, i, j;
    
    /* Load all the files */
    
    /* Parse the header file for dark. */
    var = parseHdr(dark);                                                       
    if (var == 0) {
        record("MAIN: Dark datacube header parsed correctly.\n");
        //printHdr(dark);
        /* Parse the binary file. */
        var = parseBin(dark); 
        printf("parsebin returned: %d\n", var);

    } else {
        record("MAIN: Dark datacube header did not parse correctly!\n");
    }
    record("MAIN: Dark datacube parsed\n");
    /* Parse the header file for response. */
    //var = parseHdr(response); 

   // if (var == 0) {
   //     record("MAIN: Response datacube parsed correctly.\n");
        //printHdr(response);

        /* Parse the binary file. */
   //     parseBin(response);
   // } else {
     //   record("MAIN: Response datacube did not parse correctly!\n");
    //}
    
    printf("Printing dark cube hex values");
    
    for(i = 0; i < 640;i++)
    {
        sprintf(msg,"Hex value is: datacube[0][0][%d]%08X  %d %s\n",i,dark_matrix[0][0][i], dark_matrix[0][0][i], (char)(dark_matrix[0][0][i]) );
        record(msg);
    }
    
    //parseMeans();
    
    //parseStandards();
    
    //parseClassParams();
    
   // printf("MAIN: Printing off parsed values\n");
    
    //printf("MAIN: means and standard deviation and classification parameters(first row)...\n");
    //for (i = 0; i < 1088; i++)
    //{
    //            sprintf(msg,    "meansfixed[%d]:          %08X\n", i, means_v[i]); record(msg);
    //            sprintf(msg,    "standardsfixed[%d]:      %08X\n", i, standards_v[i]); record(msg);
    //            for(j = 0; j < 50; j++)
    //            {
    //                sprintf(msg,"classfixed[%d][%d]:      %08X\n", i,j, class_v[i][j]); record(msg);
    //            }
    //}
    
    /* Send the files over the network */
    
    server();  
    
    

    return (EXIT_SUCCESS);
}

