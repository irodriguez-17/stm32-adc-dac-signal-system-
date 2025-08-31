# STM32 ADC/DAC Signal System
This project was developed as part of coursework at Santa Clara University and is shared for portfolio demonstration. It is not intended for reuse in academic submissions.

Built an embedded signal generator on **STM32L476** that outputs sine or sawtooth on the DAC at **20 kHz** sample rate, with real-time volume control from a potentiometer via **ADC**.

## Key Skills Applied
- Embedded C programming (timer ISRs, peripherals)
- STM32 **DAC**, **ADC**, **TIM** configuration with HAL
- Wavetable synthesis & fixed-point scaling
- Validation with oscilloscope and structured documentation

## Tech Stack
- **Hardware:** STM32L476 Discovery Board (DAC on PA5, ADC CH6 on PA1)
- **Software:** C (HAL), Keil/CubeMX
- **Tools:** Oscilloscope, Git

## Implementation Highlights
- **TIM2 ISR @ 20 kHz** advances a 1024-entry wavetable (sine or saw)
- **ADC** reads a 12-bit pot value (0–4095) and scales output amplitude
- **Phase accumulator** uses 1/16th indexing for flexible frequency (e.g., 600 Hz)
- Output verified on scope for amplitude tracking and correct frequency
- Sine (≈600 Hz) and sawtooth waveforms at the DAC output (PA5)
- Potentiometer smoothly adjusts amplitude in real time

* If I locate scope captures later, I’ll add them under /screenshots.

## Representative Snippet
```c
// Timer ISR (simplified)
void TIM2_IRQHandler(void){
  if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) &&
      __HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE)) {
    __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
    uint16_t gain  = ADC_Read();                  // 0..4095
    uint16_t raw   = wavetable[phase16 >> 4];     // 1024-entry
    uint16_t out   = (raw * gain) >> 12;          // scale by gain/4096
    DAC_Write12(out);                             // 12-bit DAC
    phase16 += phaseInc16;                        // fs=20k, f0~600 Hz
    phase16 &= ((1024 << 4) - 1);
  }
}


