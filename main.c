#include <stdio.h>
#include "pid_controller.h"
#include "motor_model.h"
#include "logger.h"
#include "utils.h"

// --- Simulation Parameters ---
#define SIMULATION_DURATION_CYCLES 200 // Defines how long the simulation runs.
#define TIME_STEP_S 0.05               // Sets the time interval for each simulation step (50ms).
#define TARGET_SPEED 100.0             // The desired speed for the motor to reach (in RPM).

// --- PID Gains ---
// These constants are crucial for tuning the controller's performance.
#define KP 0.5  // Proportional gain: scales with the current error.
#define KI 0.1  // Integral gain: accumulates past errors to correct steady-state offset.
#define KD 0.02 // Derivative gain: dampens oscillations by reacting to the rate of error change.

// --- Motor Physical Properties ---
#define MOTOR_INERTIA 0.1  // Models the motor's resistance to changes in speed.
#define MOTOR_FRICTION 0.05 // Simulates energy loss due to friction.

int main() {
    // 1. Initialization
    PIDController pid; // Create a PID controller instance.
    MotorModel motor;   // Create a motor model instance.
    
    // Set up the PID controller with the defined gains and time step.
    pid_init(&pid, KP, KI, KD, TIME_STEP_S);
    // Initialize the motor with its physical properties.
    motor_init(&motor, MOTOR_INERTIA, MOTOR_FRICTION);
    
    // Set up the logger to save data to a CSV file.
    const char* log_filename = "log.csv";
    FILE* log_file = logger_init(log_filename);
    if (log_file == NULL) {
        // Handle cases where the log file cannot be opened.
        fprintf(stderr, "Failed to open log file. Continuing without file logging.\n");
    }

    // Print initial simulation settings to the console.
    printf("Starting PID Motor Control Simulation...\n");
    printf("Target Speed: %.2f RPM\n", TARGET_SPEED);
    printf("PID Gains: Kp=%.2f, Ki=%.2f, Kd=%.2f\n", KP, KI, KD);
    printf("Logging data to %s\n\n", log_filename);
    
    // 2. Simulation Loop
    // This loop runs for a fixed number of cycles, simulating the control process over time.
    for (int i = 0; i < SIMULATION_DURATION_CYCLES; ++i) {
        // Calculate the required control signal based on the target and actual speed.
        double control_signal = pid_update(&pid, TARGET_SPEED, motor.current_speed);
        
        // Apply the control signal to the motor to update its speed.
        motor_update(&motor, control_signal, TIME_STEP_S);

        // Record the current state of the system to the console and log file.
        double current_error = TARGET_SPEED - motor.current_speed;
        logger_log_data(log_file, i, TARGET_SPEED, motor.current_speed, current_error, control_signal);

        // Pause execution to simulate real-time behavior.
        sleep_ms((int)(TIME_STEP_S * 1000));
    }

    // 3. Cleanup
    // Close the log file to ensure all data is written to disk.
    logger_close(log_file);
    
    printf("\nSimulation finished. Data saved to %s\n", log_filename);
    printf("To visualize, open %s in a spreadsheet program or use a plotting script.\n", log_filename);

    return 0;
}