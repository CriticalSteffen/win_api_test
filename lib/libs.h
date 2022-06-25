/* Log library header. */

#ifndef LOG_H
#define LOG_H

void close_log();
void log(char *message);
void logf(char *format, ...);
void log_delay(char *message);
void log_error(const char *func_name);
void log_split(char *message);

#endif /* LOG_H */