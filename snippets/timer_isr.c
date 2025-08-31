// Simplified Timer ISR for 20 kHz DAC update
// (see README for full explanation)

void TIM2_IRQHandler(void) {
    if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) &&
        __HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE)) {
        
        __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);

        uint16_t gain  = ADC_Read();                // 0..4095
        uint16_t raw   = wavetable[phase16 >> 4];   // 1024-entry wavetable
        uint16_t out   = (raw * gain) >> 12;        // scale by gain/4096

        DAC_Write12(out);                           // send to DAC

        phase16 += phaseInc16;                      // increment phase
        phase16 &= ((1024 << 4) - 1);               // wrap phase
    }
}
