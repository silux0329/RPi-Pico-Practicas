#include "libslx.h"
#include "LCD_2in.h"
#include "GUI_Paint.h"
#include "fonts.h"


void setup() {
  DEV_Delay_ms(5000);
  Serial.begin(115200);

  Serial.println("WareShare Pico LCD 2 Test");

  if(DEV_Module_Init() != 0){
    Serial.println("DEV_Module_Init Fail");
    return;
  }

  DEV_SET_PWM(50);
  Serial.println("Initializing Test");
  LCD_2IN_Init(HORIZONTAL);
  LCD_2IN_Clear(WHITE);

  UDOUBLE ImageSize = LCD_2IN_HEIGHT * LCD_2IN_WIDTH * 2;
  UWORD *BlackImage;

  if((BlackImage = (UWORD*)malloc(ImageSize)) == NULL){
    Serial.println("Failed to apply for black memory");
    return;  
  }

  Paint_NewImage((UBYTE *)BlackImage, LCD_2IN.WIDTH, LCD_2IN.HEIGHT, ROTATE_180, WHITE);
  Paint_SetScale(65);
  Paint_Clear(WHITE);
  Serial.println("Drawing");

  Paint_DrawPoint(2,1, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);//240 240
  Paint_DrawPoint(2,6, BLACK, DOT_PIXEL_2X2,  DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,11, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,16, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
  Paint_DrawPoint(2,21, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
  Paint_DrawLine( 10,  5, 40, 35, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
  Paint_DrawLine( 10, 35, 40,  5, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  Paint_DrawLine( 80,  20, 110, 20, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine( 95,   5,  95, 35, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

  Paint_DrawRectangle(10, 5, 40, 35, RED, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(45, 5, 75, 35, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);

  Paint_DrawCircle(95, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(130, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);


    Paint_DrawNum (50, 40 ,9.87654321, &Font20,5,  WHITE,  BLACK);
    Paint_DrawString_EN(1, 40, "ABC", &Font20, 0x000f, 0xfff0);
    Paint_DrawString_CN(1, 60, "»¶Ó­Ê¹ÓÃ",  &Font24CN, WHITE, BLUE);
    Paint_DrawString_EN(1, 100, "WaveShare", &Font16, RED, WHITE); 

    Paint_DrawString_EN(1,120, "253 HOL", &Font12, WHITE, BLUE);

    // /*3.Refresh the picture in RAM to LCD*/
  LCD_2IN_Display((UBYTE *)BlackImage);
}

void loop() {
  
}
