// robot_control.c
#include "robot_control.h"

// Initialize global variables
int target_speed = 0;
uint16_t Batt_value = 0;
volatile char cnt_adc_scan = 0;
volatile uint16_t FL_value = 0, BL_value = 0, FR_value = 0, BR_value = 0;
int d_right = 100, d_left = 100;  // Initial values for sensor readings
int speed_left = 0, speed_right = 0;
bool period_elapsed = false;

// Function to handle obstacle avoidance based on IR sensors
void capteur_mur() {
    bool avoidance_ended = false;
    int diff;

    // Continue avoidance maneuver while GO flag is true
    while (!avoidance_ended && GO) {
        diff = d_left - d_right;  // Calculate difference between left and right sensors

        // If blocked from both sides (corner case), move backward
        if (d_left <= dist_detection && d_right <= dist_detection) {
            HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, 0);  // Motor right direction
            HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, 0);  // Motor left direction
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, nominal_target_speed_counter);  // Left motor
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, nominal_target_speed_counter);  // Right motor
        }
        // If obstacle is on the right, turn left
        else if (diff >= 0) {
            HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, 1);  // Right motor forward
            HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, 0);  // Left motor backward
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, nominal_target_speed_counter);  // Left motor speed
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, nominal_target_speed_counter);  // Right motor speed
        }
        // If obstacle is on the left, turn right
        else {
            HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, 0);  // Right motor backward
            HAL_GPIO_WritePin(DIR2_GPIO_Port, DIR2_Pin, 1);  // Left motor forward
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, nominal_target_speed_counter);  // Left motor speed
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, nominal_target_speed_counter);  // Right motor speed
        }

        // If no obstacles, end avoidance
        if (d_right > dist_detection && d_left > dist_detection) {
            avoidance_ended = true;
        }
    }
}

// Function to compute speed changes with acceleration limits
int compute_speed(int currentSpeed, int speedTarget) {
    int nextSpeed;
    int diff = abs(speedTarget - currentSpeed);  // Calculate the speed difference

    // If we are speeding up
    if (speedTarget > currentSpeed) {
        if (diff > MAX_ACCEL) {
            diff = MAX_ACCEL;  // Limit acceleration to max allowed
        }
        nextSpeed = currentSpeed + diff;
    }
    // If we are slowing down
    else if (speedTarget < currentSpeed) {
        if (diff > MAX_ACCEL) {
            diff = MAX_ACCEL;  // Limit deceleration to max allowed
        }
        nextSpeed = currentSpeed - diff;
    }
    else {
        nextSpeed = currentSpeed;  // Maintain current speed if no difference
    }

    return nextSpeed;
}

// Function to convert speed into PWM register values (ARR)
int speed_to_ARR(int speed) {
    int nominal_target_speed_counter = VMAX_COUNTER * abs(speed) / VMAX;
    return nominal_target_speed_counter;
}

// Function to determine the direction of the motor based on speed
bool get_direction(int speed) {
    return speed > 0 ? 1 : 0;  // Return 1 if forward, 0 if backward
}
