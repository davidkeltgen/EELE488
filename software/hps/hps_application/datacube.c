/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: datacube.c                                                    *
 * Date:  November 4 2014                                                   *
 * Description: Responsible for parsing the data cube files saved onto the  *
 * 				SD Card into RAM                                            *
 *				*
 *				*
 *				*
 *				*
 ****************************************************************************/


#include "datacube.h"

int parseHdr(int cube_type) {
    record("DATACUBE:  Inside parseHdr.\n");
    datacube * temp_cube = malloc(sizeof (datacube));
    char input_data[1000];
    char filepath[100];
    char msg[256];
    int i, rc;

    if (cube_type == dark) {
        strcpy(filepath, DARK_HEADER_PATH);
    } else if (cube_type == response) {
        strcpy(filepath, RESPONSE_HEADER_PATH);
    }

    FILE* file;

    file = fopen(filepath, "r");
    sprintf(msg, "DATACUBE: %s  %d\n", filepath, (int)file);
    record(msg);

    rc = fscanf(file, "%s\n", temp_cube->description); //scan description
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, " %s %s = %d\n", input_data, input_data, &temp_cube->header_offset); //scan offset
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s %s %s = %d\n", input_data, input_data, input_data, &temp_cube->reflectance_scale_factor); //scan scale factor
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->framerate); //scan framerate
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->bands); //scan bands
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->lines); //scan lines
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->shutter); //scan shutter
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %s\n", input_data, (char *)&temp_cube->interleave); //scan interleave
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %lf\n", input_data, &temp_cube->gain); //scan gain
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->samples); //scan samples
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s %s = %d\n", input_data, input_data, &temp_cube->data_type); //scan data_type
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s %s = %d\n", input_data, input_data, &temp_cube->byte_order); //scan byte_order
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    rc = fscanf(file, "%s {", input_data); //sca
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

    for (i = 0; i < temp_cube->bands; i++) { //scan each wavelength
        if (i != temp_cube->bands - 1) {
            rc = fscanf(file, "%lf, ", &temp_cube->wavelength[i]);
        } else {
            rc = fscanf(file, "%lf", &temp_cube->wavelength[i]);
        }
    }

    rc = fscanf(file, "%s = %d\n", input_data, &temp_cube->bit_depth); //scan bit depth
    if (rc < 0) record("DATACUBE: Error reading sequence\n");

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



    record("DATACUBE: Inside parseBin\n");

    datacube * temp_cube = malloc(sizeof (datacube));
    FILE* file;
    char c1, c2;
    char filepath[100];
    char msg[256];
    int i, j, k;
    int counter = 0;
    int num_values = 0;
    uint16_t var;

    //char * value = malloc(2 * sizeof (char));

    /*Allocate memory for matrices */
    if (cube_type == dark) {
        strcpy(filepath, RESPONSE_BINARY_PATH);
        temp_cube = dark_cube;
        
        num_values = dark_cube->lines * dark_cube->bands * dark_cube->samples;
        dark_matrix = (uint32_t ***) malloc(num_values * sizeof (uint16_t));
        for (i = 0; i < dark_cube->lines; i++) {
            dark_matrix[i] = (uint32_t **) malloc(dark_cube->bands * sizeof (uint16_t *));
            for (j = 0; j < temp_cube->bands; j++) {
                dark_matrix[i][j] = (uint32_t *) malloc(dark_cube->samples * sizeof (uint16_t));
            }
        }
    } else if (cube_type == response) {
        strcpy(filepath, DARK_BINARY_PATH);
        temp_cube = response_cube;
        
        response_matrix = (uint16_t ***) malloc(num_values * sizeof (uint16_t));
        for (i = 0; i < temp_cube->lines; i++) {
            temp_matrix[i] = (uint16_t **) malloc(temp_cube->bands * sizeof (uint16_t *));
            for (j = 0; j < temp_cube->bands; j++) {
                temp_matrix[i][j] = (uint16_t *) malloc(temp_cube->samples * sizeof (uint16_t));
            }
    }
    }

    num_values = temp_cube->lines * temp_cube->bands * temp_cube->samples;

    temp_matrix = (uint32_t ***) malloc(num_values * sizeof (uint16_t));
    for (i = 0; i < temp_cube->lines; i++) {
        temp_matrix[i] = (uint32_t **) malloc(temp_cube->bands * sizeof (uint16_t *));
        for (j = 0; j < temp_cube->bands; j++) {
            temp_matrix[i][j] = (uint32_t *) malloc(temp_cube->samples * sizeof (uint16_t));
        }
    }

    file = fopen(filepath, "r");

    if (strstr(BIL, temp_cube->interleave)) {
        record("DATACUBE: inside bil\n");
        for (i = 0; i < temp_cube->lines; i++) {
            for (j = 0; j < temp_cube->bands; j++) {
                for (k = 0; k < temp_cube->samples; k++) {
                    
                    fscanf(file, "%c%c", &c1, &c2);         /* Scan in two characters */
                    var = c1;                               /* Set to first character */ 
                    var = var << 8;                         /* Shift var over 8 */                    
                    var = var + c2;                         /* Add second character to var (LS 8 bits)*/
                    temp_matrix[i][j][k] = var;             /* Store it to matrix */
                    sprintf(msg, "datacube: %d\n", var); record(msg);

                }
            }
        }
    }
    sprintf(msg, "DATACUBE: Counter is: %d, Num_values: %d\n", counter, num_values);
    record(msg);

    if (cube_type == dark)
    {
        dark_matrix = temp_matrix;
    }
    else if (cube_type == response)
    {
        response_matrix = temp_matrix;
    }
    return 1;
}

/*Will print out the values of the datacube struct. This is just to verify that the
  parsing function read in all of the values correctly*/
void printHdr(int cube_type) {
	char msg[256];
    record("DATACUBE: Inside printHdr\n");
    
    datacube * temp_cube = malloc(sizeof (datacube));
    int i;

    /* Assign to temp cube so print functions work for all cube types*/
    if (cube_type == dark) {
        temp_cube = dark_cube;
    } else if (cube_type == response) {
        temp_cube = response_cube;
    }
    
    sprintf(msg, "DATACUBE: Description: %s\n", temp_cube->description); record(msg);
    sprintf(msg, "DATACUBE: header offset = %d\n", temp_cube->header_offset); record(msg);
    sprintf(msg, "DATACUBE: reflectance scale factor = %d\n", temp_cube->reflectance_scale_factor); record(msg);
    sprintf(msg, "DATACUBE: framerate = %f\n", temp_cube->framerate); record(msg);
    sprintf(msg, "DATACUBE: bands = %d\n", temp_cube->bands); record(msg);
    sprintf(msg, "DATACUBE: lines = %d\n", temp_cube->lines); record(msg);
    sprintf(msg, "DATACUBE: shutter = %f\n", temp_cube->shutter); record(msg);
    sprintf(msg, "DATACUBE: interleave = %s\n", temp_cube->interleave); record(msg);
    sprintf(msg, "DATACUBE: gain = %f\n", temp_cube->gain); record(msg);
    sprintf(msg, "DATACUBE: samples = %d\n", temp_cube->samples); record(msg);
    sprintf(msg, "DATACUBE: data type = %d\n", temp_cube->data_type); record(msg);
    sprintf(msg, "DATACUBE: byte order = %d\n", temp_cube->byte_order); record(msg);
    record("DATACUBE: wavelength= {");
    for (i = 0; i < temp_cube->bands; i++) {
    	sprintf(msg, "%f, ", temp_cube->wavelength[i]); record(msg);
    }
    record("}\n");
    sprintf(msg, "DATACUBE: bit depth = %d\n", temp_cube->bit_depth);
}
