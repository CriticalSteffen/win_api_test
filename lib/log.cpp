/* Log library implementation. */

#include <stdio.h>
#include <time.h>

#include "libs.h"

FILE *logFile;

void close_log()
{
    if (logFile)
    {
        fclose(logFile);
        logFile = NULL;
    }
}

void log(char *message)
{
    if (logFile == NULL)
    {
        logFile = fopen("log.txt", "w");
    }

    // Create timestamp.
    time_t tTime = time(NULL);
    struct tm tStruct = *gmtime(&tTime);
    char timeStamp[21];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%dT%H:%M:%SZ", &tStruct);

    // Print log line.
    printf("%s :: %s\n", timeStamp, message);

    // Write to log file.
    fprintf(logFile, "%s :: %s\n", timeStamp, message);
    fflush(logFile);
}
