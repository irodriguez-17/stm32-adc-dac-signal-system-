#include "stm32l4xx_hal.h"
extern ADC_HandleTypeDef hadc1;

// Read 12-bit ADC value from potentiometer on PA1
uint16_t ADC_Read(void) {
    HAL_ADC_PollForConversion(&hadc1, 10);
    return (uint16_t)HAL_ADC_GetValue(&hadc1); // 0..4095
}
