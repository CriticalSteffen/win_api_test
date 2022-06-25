/* Common functions header. */

#ifndef UTIL_H
#define UTIL_H

// log.cpp
void close_log();
void log(char *message);
void logf(char *format, ...);
void log_delay(char *message);
void log_error(const char *func_name);
void log_split(char *message);

// timing.cpp
void pause();

#endif /* UTIL_H */