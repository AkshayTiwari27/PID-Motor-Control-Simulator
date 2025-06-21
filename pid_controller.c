#include "pid_controller.h"
#include <stddef.h> // For NULL

// Initializes the PID controller struct with provided values.
void pid_init(PIDController *pid, double Kp, double Ki, double Kd, double dt) {
    if (pid == NULL) {
        return;
    }
    // Assign gains and time step.
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->dt = dt;
    // Reset internal state variables.
    pid->integral = 0.0;
    pid->previous_error = 0.0;
}

// Calculates the new control signal based on the current system state.
double pid_update(PIDController *pid, double setpoint, double actual_value) {
    if (pid == NULL) {
        return 0.0;
    }

    // Calculate the difference between the desired and actual values.
    double error = setpoint - actual_value;

    // --- Proportional Term ---
    // Responds directly to the magnitude of the current error.
    double p_term = pid->Kp * error;

    // --- Integral Term ---
    // Accumulates error over time to eliminate steady-state error.
    pid->integral += error * pid->dt;
    double i_term = pid->Ki * pid->integral;

    // --- Derivative Term ---
    // Responds to the rate of error change to dampen oscillations.
    double derivative = (error - pid->previous_error) / pid->dt;
    double d_term = pid->Kd * derivative;

    // Save the current error for the next derivative calculation.
    pid->previous_error = error;

    // Sum the terms to get the final control output.
    double output = p_term + i_term + d_term;

    return output;
}