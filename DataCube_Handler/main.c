/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                       *
 * File Name: main.c                                                        *
 * Date:  June 4 2014                                                       *
 * Description: Will provide the timeline for reading and parsing the 
 *              the different file types need to be sent to the FPGA.                           *  
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "main.h"


int main(int argc, char** argv) {
    record("program started\n");
    int var;
    /* Parse the header file for dark. */
    var = parseHdr(dark);
    if (var == 0) {
        record("Dark datacube parsed correctly.\n");
        printHdr(dark);
        /* Parse the binary file. */
        parseBin(dark);

    } else {
        record("Dark datacube did not parse correctly!\n");
    }

    /* Parse the header file for response. */
    var = parseHdr(response);

    if (var == 0) {
        record("Response datacube parsed correctly.\n");
        printHdr(response);
        /* Parse the binary file. */
        parseBin(response);
    } else {
        record("Response datacube did not parse correctly!\n");
    }

    /* Send matrices over DMA */


    return (EXIT_SUCCESS);
}

