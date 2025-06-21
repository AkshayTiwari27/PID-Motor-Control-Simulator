#include "motor_model.h"
#include <stddef.h> // For NULL

// Initializes the motor model with given physical properties.
void motor_init(MotorModel *motor, double inertia, double friction) {
    if (motor == NULL) {
        return;
    }
    motor->inertia = inertia;
    motor->friction = friction;
    motor->current_speed = 0.0; // Motor starts from a standstill.
}

// Updates the motor's speed based on a simplified physics model.
void motor_update(MotorModel *motor, double control_signal, double dt) {
    if (motor == NULL) {
        return;
    }
    
    // Acceleration is the control signal (force) divided by inertia (mass).
    double acceleration = control_signal / motor->inertia;
    
    // Update speed based on acceleration over the time step.
    motor->current_speed += acceleration * dt;
    
    // Apply friction, which reduces speed proportionally to the current speed.
    if (motor->current_speed > 0) {
        motor->current_speed -= motor->friction * motor->current_speed * dt;
    } else if (motor->current_speed < 0) {
        // Handle negative speed, ensuring friction always opposes motion.
        motor->current_speed += motor->friction * -motor->current_speed * dt;
    }
}