#include "logger.h"
#include <stdio.h>

// Opens and prepares the log file, then writes the CSV header.
FILE* logger_init(const char* filename) {
    // Open the file in write mode, which creates or overwrites it.
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        // If opening fails, report an error.
        perror("Error opening log file");
        return NULL;
    }
    // Write the header row for the CSV file.
    fprintf(file, "cycle,target_speed,actual_speed,error,control_signal\n");
    return file;
}

// Logs data to both the console and the specified file.
void logger_log_data(FILE* log_file, int cycle, double target_speed, double actual_speed, double error, double control_signal) {
    // Print a formatted status line to the console for real-time monitoring.
    printf("[Cycle %03d] Target: %.2f | Speed: %.2f | Error: %.2f | Output: %.2f\n",
           cycle, target_speed, actual_speed, error, control_signal);

    // Write the same data as a comma-separated row to the log file.
    if (log_file != NULL) {
        fprintf(log_file, "%d,%.4f,%.4f,%.4f,%.4f\n",
                cycle, target_speed, actual_speed, error, control_signal);
    }
}

// Closes the log file stream.
void logger_close(FILE* log_file) {
    // Check for a valid file pointer before attempting to close.
    if (log_file != NULL) {
        fclose(log_file);
    }
}