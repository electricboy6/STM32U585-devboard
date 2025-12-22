#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_
#endif

#ifdef __cplusplus
extern "C" {
#endif

// pin defs
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
#define PA11 32
#define PA12 33
#define PA13 34
#define PA14 37
#define PA15 38
#define PB0  18
#define PB1  19
#define PB2  20
#define PB3  39
#define PB4  40
#define PB5  41
#define PB6  42
#define PB7  43
#define PB8  45
#define PB9  46
#define PB10 21
#define PB11 22
#define PB12 25
#define PB13 26
#define PB14 27
#define PB15 28


#define NUM_DIGITAL_PINS 32
#define NUM_ANALOG_INPUTS 2

// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE TIM6
#define TIMER_SERVO TIM7

#define SERIAL_UART_INSTANCE 1

#define PIN_SERIAL_RX 31
#define PIN_SERIAL_TX 30

// sd defs
#define SDCARD_MOSI_PIN PB15
#define SDCARD_MISO_PIN PB14
#define SDCARD_SCK_PIN PB13
#define SDCARD_SS_PIN PB12

// hal modules
#define HAL_I2C_MODULE_DISABLED

#ifdef __cplusplus
}
#endif
