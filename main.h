// main.h
#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"  // STM32 HAL header
#include <stdbool.h>        // For boolean types

// GPIO pins for motor control and IR sensors (placeholder)
#define DIR1_GPIO_Port GPIOA
#define DIR1_Pin GPIO_PIN_1
#define DIR2_GPIO_Port GPIOB
#define DIR2_Pin GPIO_PIN_2
#define TIM_CHANNEL_1 1
#define TIM_CHANNEL_4 4

// Placeholder variables for sensor thresholds and speed
extern int dist_detection;
extern int nominal_target_speed_counter;

#endif // MAIN_H
