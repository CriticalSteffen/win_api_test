/* Log library header. */

#ifndef LOG_H
#define LOG_H

void close_log();
void log(char *message);
void logf(char *format, ...);
void log_error(const char *func_name);

#endif /* LOG_H */