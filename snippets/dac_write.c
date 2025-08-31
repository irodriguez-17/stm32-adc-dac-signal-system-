#include "stm32l4xx_hal.h"
extern DAC_HandleTypeDef hdac1;

// Initialize DAC channel 2 (PA5)
void DAC_Init(void) {
    HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
}

// Write a 12-bit sample to DAC output
static inline void DAC_Write12(uint16_t v) {
    HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, v & 0x0FFF);
}
