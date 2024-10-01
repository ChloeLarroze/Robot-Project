#include "robot_control.h" // Include robot control functions
#include "config.h"       // Include configuration settings
#include "main.h"         // Include HAL and peripheral definitions

// Global variable to track the robot's operational state
bool GO = false;

// Main application entry point
int main(void) {
    // Initialize the robot's hardware components
    Robot_Init();

    // Start receiving commands via UART for Bluetooth control
    HAL_UART_Receive_IT(&huart3, &Rx_buffer, 1); // Start UART reception

    // Main loop
    while (1) {
        // Check if the robot is active
        if (GO) {
            // Monitor obstacles and control robot movement
            Robot_CheckObstacles(); // Check for obstacles in the path
        } else {
            // Stop motors if the robot is inactive
            Robot_SetSpeed(0, 0); // Stop both motors
        }
    }
}

// UART Reception Complete Callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    // Handle received UART data
    if (huart->Instance == USART3) {
        // Process the received command to control the robot
        Robot_ControlMotors(Rx_buffer); // Call function to control motors based on input
        // Prepare to receive the next byte
        HAL_UART_Receive_IT(&huart3, &Rx_buffer, 1); // Restart UART reception
    }
}

// Button Press Interrupt Callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Toggle the operational state of the robot
    if (GPIO_Pin == BP_Pin) { // Check if the interrupt was triggered by the button
        GO = !GO; // Toggle GO state
    }
}

// Check the battery status and take necessary actions
void Robot_CheckBattery(void) {
    // Implement battery monitoring logic
    // Turn on alert LED if the battery is low
    if (Batt_value < LOW_BATTERY_THRESHOLD) {
        HAL_GPIO_WritePin(Alert_batt_GPIO_Port, Alert_batt_Pin, GPIO_PIN_SET); // Turn on alert LED
    } else {
        HAL_GPIO_WritePin(Alert_batt_GPIO_Port, Alert_batt_Pin, GPIO_PIN_RESET); // Turn off alert LED
    }
}

// Handle the obstacle detection and avoidance logic
void Robot_CheckObstacles(void) {
    // Example logic for obstacle detection
    if (d_left < DISTANCE_THRESHOLD || d_right < DISTANCE_THRESHOLD) {
        // Execute obstacle avoidance
        Robot_AvoidObstacle();
    } else {
        // No obstacles detected, continue moving
        Robot_SetSpeed(speed_left, speed_right);
    }
}

// Function to avoid obstacles
void Robot_AvoidObstacle(void) {
    // Example logic to determine which way to turn
    if (d_left < d_right) {
        // Turn right
        Robot_SetSpeed(nominal_speed, -nominal_speed);
    } else {
        // Turn left
        Robot_SetSpeed(-nominal_speed, nominal_speed);
    }
}
/*Explanation of Key Sections
 - Includes: The file starts by including necessary header files, including robot_control.h for the robot control functions, config.h for configuration settings, and main.h for HAL and peripheral definitions.
 
 - Global Variables: A global variable GO is used to track whether the robot is active or inactive.
 
 - Main Function:
Initializes hardware.
Enters an infinite loop where it checks the robot's operational state and controls movement based on detected obstacles.

 - UART and Button Callbacks:
HAL_UART_RxCpltCallback processes received commands and restarts UART reception.
HAL_GPIO_EXTI_Callback toggles the operational state of the robot when the button is pressed.

 - Battery and Obstacle Functions:
Robot_CheckBattery monitors the battery status and controls the alert LED.
Robot_CheckObstacles handles obstacle detection and invokes avoidance maneuvers.*/
