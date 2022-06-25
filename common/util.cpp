/* Log library implementation. */

#include "util.h"

#include <windows.h> /* GetLastError, Sleep */
#include <stdio.h> /* fclose, fflush, fopen, fprintf, printf, vsprintf */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <string.h> /* strlen */
#include <time.h> /* gmtime, strftime, time */

const int DELAY_MS = 2000;
FILE *LOG_FILE;

void close_log()
{
    if (LOG_FILE)
    {
        fclose(LOG_FILE);
        LOG_FILE = NULL;
    }
}

void log(char *message)
{
    if (LOG_FILE == NULL)
    {
        LOG_FILE = fopen("log.txt", "w");
    }

    // Create timestamp.
    time_t tTime = time(NULL);
    struct tm tStruct = *gmtime(&tTime);
    char timeStamp[21];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%dT%H:%M:%SZ", &tStruct);

    // Print log line.
    printf("%s :: %s\n", timeStamp, message);

    // Write to log file.
    fprintf(LOG_FILE, "%s :: %s\n", timeStamp, message);
    fflush(LOG_FILE);
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

void log_split(char *message)
{
    int messageLength = strlen(message);
    messageLength += 5;
    char dashes[56] = {0};
    for (int i = 0; i < (56 - messageLength); i++)
    {
        dashes[i] = '-';
    }
    logf("---(%s)%s", message, dashes);
}

void pause()
{
    Sleep(DELAY_MS);
}