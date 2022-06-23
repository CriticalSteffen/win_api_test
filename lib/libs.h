/* Log library header. */

#ifndef LOG_H
#define LOG_H

void close_log();
void log(char *message);
void log_error(const char *func_name);

#endif /* LOG_H */