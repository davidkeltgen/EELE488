/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University:                              *
 * File Name: datacube.c                                                    *
 * Date:  November 4 2014                                                       *
 * Description: Contains functions that record behavior of the program.
 *              Writes to the FILEPATH variable defined in logger.h                                                    *
 ****************************************************************************/

#include "datacube.h"

int parseHdr(int cube_type) {
    record("inside parseHdr\n");
    datacube * temp_cube = malloc(sizeof (datacube));
    char input_data[1000];
    char filepath[100];
    char msg[256];
    int  i,rc;
    
     if (cube_type == dark) {
        strcpy(filepath, DARK_HEADER_PATH);
    } else if (cube_type == response) {
        strcpy(filepath, RESPONSE_HEADER_PATH);  
    }
    
    FILE* file;
    
    file = fopen(filepath, "r");
    record("%s  %d\n", filepath, file);
    
    rc = fscanf(file, "%s\n", temp_cube->description); //scan description
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, " %s %s = %d\n", input_data, input_data,&temp_cube->header_offset); //scan offset
    record("%s\n", input_data);
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s %s %s = %d\n", input_data, input_data, input_data, &temp_cube->reflectance_scale_factor); //scan scale factor
    record("%s___%d\n", input_data, temp_cube->reflectance_scale_factor);
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->framerate); //scan framerate
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->bands); //scan bands
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->lines); //scan lines
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->shutter); //scan shutter
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %s\n", input_data, &temp_cube->interleave); //scan interleave
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->gain); //scan gain
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->samples); //scan samples
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s %s = %d\n", input_data, input_data, &temp_cube->data_type); //scan data_type
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s %s = %d\n", input_data, input_data, &temp_cube->byte_order); //scan byte_order
    if (rc < 0) record("Error reading sequence\n");
    
    rc = fscanf(file, "%s {", input_data); //scan 
    record("%s\n", input_data);
    if (rc < 0) record("Error reading sequence\n");
    
    for (i = 0; i < temp_cube->bands; i++) {       //scan each wavelength
        if(i != temp_cube->bands - 1)  {
                rc = fscanf(file, "%lf, ", &temp_cube->wavelength[i]);
        } else {
                rc = fscanf(file, "%lf", &temp_cube->wavelength[i]);
        }
    }
    
    rc = fscanf(file, "%s = %d\n",input_data, &temp_cube->bit_depth); //scan bit depth
    if (rc < 0) record("Error reading sequence\n");
    
        if (cube_type == dark) {
        dark_cube = temp_cube;
    } else if (cube_type == response) {
        response_cube = temp_cube; 
    }
    
    return 0;
}

int parseBin(int cube_type) {
    
    /*pseudocode */
    /*For line in num_lines:
    for band in num_bands:
       for sample in n num_samples:
           data[line, band, sample] = next 2 byte integer from file */
    
    
    
    record("inside parseBin\n");
    
    datacube * temp_cube = malloc(sizeof (datacube));
    FILE* file;
    char * c1;
    char * c2;
    char value[2];
    char filepath[100];
    char msg[256];
    int counter = 0;;
    
    
    
    if (cube_type == dark) {
        strcpy(filepath, RESPONSE_BINARY_PATH);
        /*Allocate space for matrix*/
        record(sprintf(msg,"total number of values: %d\n", (dark_cube->lines * dark_cube->bands * dark_cube->samples)));
        dark_matrix = malloc((dark_cube->lines * dark_cube->bands * dark_cube->samples) * sizeof(int)); 
      
        
    } else if (cube_type == response) {
        strcpy(filepath, DARK_BINARY_PATH);
        /*Allocate space for matrix*/
        record(sprintf(msg,"total number of values: %d\n", (response_cube->lines * response_cube->bands * response_cube->samples)));
        dark_matrix = malloc((response_cube->lines * response_cube->bands * response_cube->samples) * sizeof(int)); 
        
    }
    
    file = fopen(filepath, "r");
    record("%s  %d\n", filepath, file);
    
    do {
        fscanf(file,"%c%c", c1, c2);
        record("%c%c\n",c1,c2);
        strcat(value,(char *)c1);
        strcat(value,(char *)c2);
        counter++;
        record("Counter is : %d\n", counter);
        
        
        
        
    } while((c1 != EOF) && (c2 != EOF));
    
    return 0;
}

/*Will print out the values of the datacube struct. This is just to verify that the
  parsing function read in all of the values correctly*/
void printHdr(int cube_type) {
    record("inside printHdr\n");
    datacube * temp_cube = malloc(sizeof (datacube));

    if (cube_type == dark) {
        
    } else if (cube_type == response) {
        
    }

    int i, j;
    record("Description: %s\n", temp_cube->description);
    record("header offset = %d\n", temp_cube->header_offset);
    record("reflectance scale factor = %d\n", temp_cube->reflectance_scale_factor);
    record("framerate = %f\n", temp_cube->framerate);
    record("bands = %d\n", temp_cube->bands);
    record("lines = %d\n", temp_cube->lines);
    record("shutter = %f\n", temp_cube->shutter);
    record("interleave = %s\n", temp_cube->interleave);
    record("gain = %f\n", temp_cube->gain);
    record("samples = %d\n", temp_cube->samples);
    record("data type = %d\n", temp_cube->data_type);
    record("byte order = %d\n", temp_cube->byte_order);
    record("wavelength= {");
    for (i = 0; i < temp_cube->bands; i++) {
        record("%f, ", temp_cube->wavelength[i]);
    }

    record("}\n");
    record("bit depth = %d\n", temp_cube->bit_depth);
}