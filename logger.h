#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h> // For FILE*

// Opens a log file for writing and writes the CSV header.
FILE* logger_init(const char* filename);

// Logs a single time-step of data to the console and the file.
void logger_log_data(FILE* log_file, int cycle, double target_speed, double actual_speed, double error, double control_signal);

// Closes the log file to ensure all data is saved.
void logger_close(FILE* log_file);

#endif // LOGGER_H