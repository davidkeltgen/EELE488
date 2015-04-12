/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: logger.c                                                      *
 * Date:  November 4 2014                                                   *
 * Description: Contains functions that record behaviour of the program.    *
 *              Writes to the FILEPATH variable defined in logger.h         *
 ****************************************************************************/

#include "logger.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

void record(const char* message) {

    FILE *outfile; // for writing
    outfile = fopen(FILEPATH, "a"); // write to this file
    time_t now;
    time(&now);
    char theTime[255];

    /*micro time*/
    struct  timeval tv;
    struct  timezone tz;
    struct  tm *tm_s_log = malloc(sizeof (struct tm));
    gettimeofday(&tv, &tz);
    tm_s_log = (struct tm *)localtime(&tv.tv_sec);
    sprintf(theTime, "%d:%02d:%02d:%03d", tm_s_log->tm_hour, tm_s_log->tm_min, tm_s_log->tm_sec, (int)(tv.tv_usec / 1000));

    /*write the date and the message to the file*/
    fwrite("[", 1, 1, outfile);
    fwrite(theTime, sizeof (theTime[0]), strlen(theTime), outfile);
    fwrite("] ", 1, 2, outfile);

    char * delim = " : ";
    fwrite(delim, sizeof (char), strlen(delim), outfile);

    fwrite(message, sizeof (message[0]), strlen(message), outfile);

    /* we are done with file, close it */
    fclose(outfile);
}
