/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: main.c                                                        *
 * Date:  March 17 2015                                                     *
 * Description: Will provide the timeline for reading and parsing the 
 *              the different file types need to be sent to the FPGA.                           *  
 ****************************************************************************/



#include "main.h"

int main(int argc, char** argv) {
    record("MAIN: Program started.\n");
    int var, i, j;

    /* get data*/
    var = client("127.0.0.1");
    printf("var: %d\n",var);
    
/////////////////////////////////////////////////////////////////////////////////////////////////////
    /* Send means, standard deviation and coefficient matrices over the fullweight bridge */
    
    for(i = 0; i < MEANS_MATRIX_SIZE;i++)
    {
        //means_fixed[i].final_value;
    }
    
    
    for(i = 0; i < STANDARDS_MATRIX_SIZE;i++)
    {
        //standards_fixed[i].final_value;
    }
    
    for(i = 0; i < MEANS_MATRIX_SIZE;i++)
    {
        for(j = 0; j < NUM_CLASSES;j++)
        {
            //class_fixed[i][j];
        }
    }
    
    /* Done with writing classification parameters to onchip memory, tell regression component it can start computing */

    // send datacube values using the SGDMA module
    
    /* Done with writing light and dark matrices to DDR3 memory, inform the controller that can move on. */

    /* Now all the program needs to do is wait for classification results from the regression model and send
     * those results over the network */

    //init server
    //poll
    //send stuff


    return (EXIT_SUCCESS);
}
