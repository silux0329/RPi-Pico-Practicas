#ifndef _LCD_2IN_H
#define _LCD_2IN_H

// ********** Library Includes ********** //
#include "libslx.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// ********** LCD Includes ********** //
#define LCD_2IN_HEIGHT 240
#define LCD_2IN_WIDTH 320

#define HORIZONTAL 0
#define VERTICAL 1

// ********** LCD Variables ********** //
// LCD Attributes sctruct
typedef struct{
  UWORD WIDTH;
  UWORD HEIGHT;
  UBYTE SCAN_DIR;
}LCD_2IN_ATTRIBUTES;

LCD_2IN_ATTRIBUTES LCD_2IN;

// *********** Functions ********** //
// Hardware Reset
static void LCD_2IN_Reset(void){
  DEV_Digital_Write(LCD_RST_PIN,1);
  DEV_Delay_ms(100);
  DEV_Digital_Write(LCD_RST_PIN,0);
  DEV_Delay_ms(100);
  DEV_Digital_Write(LCD_RST_PIN,1);
  DEV_Delay_ms(100);
}

// Send Command
static void LCD_2IN_SendCommand(UBYTE Reg){
  DEV_Digital_Write(LCD_DC_PIN, 0);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  DEV_SPI_WriteByte(Reg);
  DEV_Digital_Write(LCD_CS_PIN, 1);
}

// Send Data
static void LCD_2IN_SendData_8Bit(UBYTE Data){  // 8 Bits
  DEV_Digital_Write(LCD_DC_PIN, 1);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  DEV_SPI_WriteByte(Data);
  DEV_Digital_Write(LCD_CS_PIN, 1);
}

static void LCD_2IN_SendData_16Bit(UWORD Data){  // 16 BIts
  DEV_Digital_Write(LCD_DC_PIN, 1);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  DEV_SPI_WriteByte((Data >> 8) & 0xFF);
  DEV_SPI_WriteByte(Data & 0xFF);
  DEV_Digital_Write(LCD_CS_PIN, 1);
}

// Initialize the LCD Register
static void LCD_2IN_InitReg(void){
  LCD_2IN_SendCommand(0x36);
  LCD_2IN_SendData_8Bit(0x00);

  LCD_2IN_SendCommand(0x3A);
  LCD_2IN_SendData_8Bit(0x05);

  LCD_2IN_SendCommand(0x21);
  
  LCD_2IN_SendCommand(0x2A);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0x01);
  LCD_2IN_SendData_8Bit(0x3F);
  
  LCD_2IN_SendCommand(0x2B);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0xEF);
  
  LCD_2IN_SendCommand(0xB2);
  LCD_2IN_SendData_8Bit(0x0C);
  LCD_2IN_SendData_8Bit(0x0C);
  LCD_2IN_SendData_8Bit(0x00);
  LCD_2IN_SendData_8Bit(0x33);
  LCD_2IN_SendData_8Bit(0x33);

  LCD_2IN_SendCommand(0xB7);
  LCD_2IN_SendData_8Bit(0x35);

  LCD_2IN_SendCommand(0xBB);
  LCD_2IN_SendData_8Bit(0x1F);

  LCD_2IN_SendCommand(0xC0);
  LCD_2IN_SendData_8Bit(0x2C);

  LCD_2IN_SendCommand(0xC2);
  LCD_2IN_SendData_8Bit(0x01);

  LCD_2IN_SendCommand(0xC3);
  LCD_2IN_SendData_8Bit(0x12);
  
  LCD_2IN_SendCommand(0xC4);
  LCD_2IN_SendData_8Bit(0x20);

  LCD_2IN_SendCommand(0xC6);
  LCD_2IN_SendData_8Bit(0x0F);

  LCD_2IN_SendCommand(0xD0);
  LCD_2IN_SendData_8Bit(0xA4);
  LCD_2IN_SendData_8Bit(0xA1);

  LCD_2IN_SendCommand(0xE0);
  LCD_2IN_SendData_8Bit(0xD0);
  LCD_2IN_SendData_8Bit(0x08);
  LCD_2IN_SendData_8Bit(0x11);
  LCD_2IN_SendData_8Bit(0x08);
  LCD_2IN_SendData_8Bit(0x0C);
  LCD_2IN_SendData_8Bit(0x15);
  LCD_2IN_SendData_8Bit(0x39);
  LCD_2IN_SendData_8Bit(0x33);
  LCD_2IN_SendData_8Bit(0x50);
  LCD_2IN_SendData_8Bit(0x36);
  LCD_2IN_SendData_8Bit(0x13);
  LCD_2IN_SendData_8Bit(0x14);
  LCD_2IN_SendData_8Bit(0x29);
  LCD_2IN_SendData_8Bit(0x2D);

  LCD_2IN_SendCommand(0xE1);
  LCD_2IN_SendData_8Bit(0xD0);
  LCD_2IN_SendData_8Bit(0x08);
  LCD_2IN_SendData_8Bit(0x10);
  LCD_2IN_SendData_8Bit(0x08);
  LCD_2IN_SendData_8Bit(0x06);
  LCD_2IN_SendData_8Bit(0x06);
  LCD_2IN_SendData_8Bit(0x39);
  LCD_2IN_SendData_8Bit(0x44);
  LCD_2IN_SendData_8Bit(0x51);
  LCD_2IN_SendData_8Bit(0x0B);
  LCD_2IN_SendData_8Bit(0x16);
  LCD_2IN_SendData_8Bit(0x14);
  LCD_2IN_SendData_8Bit(0x2F);
  LCD_2IN_SendData_8Bit(0x31);
  LCD_2IN_SendCommand(0x21);

  LCD_2IN_SendCommand(0x11);
  LCD_2IN_SendCommand(0x29);
}

// Set Resolution and scanning method of the screen
static void LCD_2IN_SetAttributes(UBYTE Scan_Dir){
  // Get screen scan direction
  LCD_2IN.SCAN_DIR = Scan_Dir;
  UBYTE MemoryAccessReg = 0x00;

  //Get GRAM and LCD width and height
  if(Scan_Dir == HORIZONTAL){
    LCD_2IN.HEIGHT = LCD_2IN_WIDTH;
    LCD_2IN.WIDTH = LCD_2IN_HEIGHT;
    MemoryAccessReg = 0x70;
  }
  else{
    LCD_2IN.HEIGHT = LCD_2IN_HEIGHT;
    LCD_2IN.WIDTH = LCD_2IN_WIDTH;
    MemoryAccessReg = 0x00;
  }

  // Set the read/write scan direction of the frame memory
  LCD_2IN_SendCommand(0x36); // MX, MY, RGB mode
  LCD_2IN_SendData_8Bit(MemoryAccessReg); // 
}

void LCD_2IN_Init(UBYTE Scan_Dir){
  DEV_SET_PWM(90);

  // Hardware reset
  LCD_2IN_Reset();

  // Set the resolution and screen direction
  LCD_2IN_SetAttributes(Scan_Dir);

  // Initialize LCD Register
  LCD_2IN_InitReg();
}

// Set the start position and size of the display area
void LCD_2IN_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend){
  // Set the X coordinates
  LCD_2IN_SendCommand(0x2A);
  LCD_2IN_SendData_8Bit(Xstart >> 8);
  LCD_2IN_SendData_8Bit(Xstart & 0xff);
  LCD_2IN_SendData_8Bit((Xend - 1) >> 8);
  LCD_2IN_SendData_8Bit((Xend - 1) & 0xff);

  // Set the Y coordinates
  LCD_2IN_SendCommand(0x2B);
  LCD_2IN_SendData_8Bit(Ystart >> 8);
  LCD_2IN_SendData_8Bit(Ystart & 0xff);
  LCD_2IN_SendData_8Bit((Yend - 1) >> 8);
  LCD_2IN_SendData_8Bit((Yend - 1) & 0xff);

  LCD_2IN_SendCommand(0x2C);
}

// Clear Screen
void LCD_2IN_Clear(UWORD xColor){
  UWORD i;
  UWORD image[LCD_2IN_HEIGHT];
  for(i=0; i<LCD_2IN_HEIGHT; i++){
    image[i] = xColor >> 8 | (xColor & 0xff) << 8;
  }

  UBYTE *p = (UBYTE *)(image);
  LCD_2IN_SetWindows(0,0,LCD_2IN_HEIGHT, LCD_2IN_WIDTH);
  DEV_Digital_Write(LCD_DC_PIN, 1);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  for(i = 0; i<LCD_2IN_WIDTH; i++){
    DEV_SPI_Write_nByte(p, LCD_2IN_HEIGHT*2);
  }
  DEV_Digital_Write(LCD_CS_PIN, 1);
}

// Send image buffer in RAM to displays
void LCD_2IN_Display(UBYTE *Image){
  UWORD j;
  LCD_2IN_SetWindows(0,0,LCD_2IN.WIDTH, LCD_2IN.HEIGHT);
  DEV_Digital_Write(LCD_DC_PIN, 1);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  for(j=0; j<LCD_2IN.WIDTH; j++){
    DEV_SPI_Write_nByte((UBYTE *)Image+LCD_2IN.HEIGHT*2*j,LCD_2IN.HEIGHT*2);
  }
  DEV_Digital_Write(LCD_CS_PIN, 1);
  LCD_2IN_SendCommand(0x29);
}

void LCD_2IN_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image){
  // display
  UDOUBLE Addr = 0;

  UWORD j;
  LCD_2IN_SetWindows(Xstart,Ystart,Xend,Yend);
  DEV_Digital_Write(LCD_DC_PIN, 1);
  DEV_Digital_Write(LCD_CS_PIN, 0);
  for(j = Ystart; j < Yend-1; j++){
    Addr = Xstart + j * LCD_2IN.WIDTH;
    DEV_SPI_Write_nByte((uint8_t *)&Image[Addr], (Xend-Xstart)*2);
  }
  DEV_Digital_Write(LCD_CS_PIN, 1);
}

void LCD_2IN_DisplayPoint(UWORD X, UWORD Y, UWORD xColor){
  LCD_2IN_SetWindows(X,Y,X,Y);
  LCD_2IN_SendData_16Bit(xColor);
}

void Handler_2IN_LCD(int signo){
  // System Exit
  debug("Handler: program stop");
  DEV_Module_Exit();
  exit(0);
}
#endif
