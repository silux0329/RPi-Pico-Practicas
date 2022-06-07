#ifndef _LIBSLX_H
#define _LIBSLX_H

// ********** Library Includes ********** //
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "stdio.h"

// ********** Aditional Defines
#define DEBUGON 1
#ifdef DEBUGON
  #define debug(...) Serial.println(__VA_ARGS__)
#else
  #define debug(...)
#endif

// ********** Data Types ********** //
#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t

// ********** Port Configuration ********** //
#define SPI_PORT spi1

// ********** LCD Pin Configuration ********** //
#define LCD_RST_PIN 12
#define LCD_DC_PIN 8
#define LCD_BL_PIN 13

#define LCD_CS_PIN 9
#define LCD_CLK_PIN 10
#define LCD_MOSI_PIN 11

// ********** Other variables ********** //
uint slice_num;

// ********** Fucntions ********** //
// GPIO Functions
void DEV_Digital_Write(UWORD Pin, UBYTE Value){
  gpio_put(Pin,Value);
}

UBYTE DEV_Digital_Read(UWORD Pin){
  return gpio_get(Pin);
}

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode){
  gpio_init(Pin);
  if(Mode == 0 || Mode == GPIO_IN)
    gpio_set_dir(Pin,GPIO_IN);
  else
    gpio_set_dir(Pin,GPIO_OUT);
}

// Pico LCD Pins configuration
void DEV_KEY_Config(UWORD Pin){
  gpio_init(Pin);
  gpio_pull_up(Pin);
  gpio_set_dir(Pin,GPIO_IN);
}

void DEV_GPIO_Init(void){
  DEV_GPIO_Mode(LCD_RST_PIN,1);
  DEV_GPIO_Mode(LCD_DC_PIN,1);
  DEV_GPIO_Mode(LCD_CS_PIN,1);
  DEV_GPIO_Mode(LCD_BL_PIN,1);

  DEV_Digital_Write(LCD_CS_PIN,1);
  DEV_Digital_Write(LCD_DC_PIN,0);
  DEV_Digital_Write(LCD_BL_PIN,1);
}

void DEV_SET_PWM(UBYTE Value){
  if( Value < 0 || Value > 100)
    debug("DEV_SET_PWM Error \n");
  else
    pwm_set_chan_level(slice_num,PWM_CHAN_B,Value);
}

// Time Delays
void DEV_Delay_ms(UDOUBLE xms){
  sleep_ms(xms);
}

void DEV_Delay_us(UDOUBLE xus){
  sleep_us(xus);
}

// Module Configurations
UBYTE DEV_Module_Init(void){
  // stdio_init_all();
  // SPI Config
  spi_init(SPI_PORT, 10000 * 1000);
  gpio_set_function(LCD_CLK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);

  // GPIO Config
  DEV_GPIO_Init();

  // PWM Config
  gpio_set_function(LCD_BL_PIN, GPIO_FUNC_PWM);
  slice_num = pwm_gpio_to_slice_num(LCD_BL_PIN);
  pwm_set_wrap(slice_num,100);
  pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
  pwm_set_enabled(slice_num, true);

  debug("DEV_Module_Init OK");
  return 0;  
}

void DEV_Module_Exit(void){
  
}

// SPI Communications
void DEV_SPI_WriteByte(UBYTE Value){
  spi_write_blocking(SPI_PORT, &Value, 1);
}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len){
  spi_write_blocking(SPI_PORT, pData, Len);
}

#endif
