// robot_control.h
#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H

#include "main.h"  // Include main HAL and STM32 libraries

// Constants for robot speed and limits
#define VMAX_COUNTER 2000      // Maximum counter for speed control
#define VMAX 2780              // Maximum speed in um/s (micro meters per second)
#define MAX_ACCEL 10           // Maximum acceleration in um/10ms (i.e., 1 cm/s)

// Global variables
extern int target_speed;       // Desired target speed
extern uint16_t Batt_value;    // Current battery level
extern volatile char cnt_adc_scan;  // Counter for ADC scan sequence
extern volatile uint16_t FL_value, BL_value, FR_value, BR_value;  // Sensor readings for IR
extern int d_right, d_left;    // Distance readings for right and left sensors
extern int speed_left, speed_right;  // Speed for left and right motors
extern bool period_elapsed;    // Flag for timing periods

// Function prototypes
void capteur_mur(void);          // Function for obstacle avoidance
bool get_direction(int speed);   // Determine motor direction based on speed
int compute_speed(int currentSpeed, int speedTarget);  // Calculate the next speed
int speed_to_ARR(int speed);     // Convert speed to PWM counter value

#endif // ROBOT_CONTROL_H
