#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Holds the state and gains for a PID controller.
typedef struct {
    // Controller gains that determine its response characteristics.
    double Kp; // Proportional gain
    double Ki; // Integral gain
    double Kd; // Derivative gain

    // Time delta (in seconds) between updates, crucial for calculations.
    double dt;

    // Internal state variables used for calculations.
    double integral;       // Stores the accumulated error.
    double previous_error; // Stores the error from the last cycle for the derivative term.

} PIDController;

// Initializes a PID controller with specified gains and time step.
void pid_init(PIDController *pid, double Kp, double Ki, double Kd, double dt);

// Computes the control signal using the PID algorithm.
double pid_update(PIDController *pid, double setpoint, double actual_value);

#endif // PID_CONTROLLER_H