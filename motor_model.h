#ifndef MOTOR_MODEL_H
#define MOTOR_MODEL_H

// Represents the physical properties and state of a simulated DC motor.
typedef struct {
    // Physical properties of the motor.
    double inertia;     // Resistance to change in speed.
    double friction;    // Speed loss over time.
    
    // State variable of the motor.
    double current_speed; // The current rotational speed of the motor.

} MotorModel;

// Initializes the motor model with its physical properties.
void motor_init(MotorModel *motor, double inertia, double friction);

// Updates the motor's speed based on the control signal and time step.
void motor_update(MotorModel *motor, double control_signal, double dt);

#endif // MOTOR_MODEL_H