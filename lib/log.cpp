/* Log library implementation. */

#include <windows.h>
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

void logf(char *format, ...)
{
    char message[256] = {0};
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);
    log(message);
}

void log_error(const char *func_name)
{
    logf("(%s) Failed with error code: %d.", func_name, GetLastError());
}
