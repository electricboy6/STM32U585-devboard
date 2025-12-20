#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Pin defs
#define PA0  10
#define PA1  11
#define PA2  12
#define PA3  13
#define PA4  14
#define PA5  15
#define PA6  16
#define PA7  17
#define PA8  29
#define PA9  30
#define PA10 31
#define PB0  18
#define PB1  19
#define PB3  39
#define PB4  40
#define PB5  41
#define PB6  42
#define PB7  43
#define PB13 26
#define PB14 27
#define PB15 28

#define NUM_DIGITAL_PINS 21
#define NUM_ANALOG_INPUTS 0

#define LED_BUILTIN 40

// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE TIM6
#define TIMER_SERVO TIM7

#define SERIAL_UART_INSTANCE 2

#define PIN_SERIAL_RX 13
#define PIN_SERIAL_TX 12

// hal modules
#define HAL_SPI_MODULE_DISABLED

#ifdef __cplusplus
}
#endif
