#include "wiring.h"
#include "spi.h"
#include "ssd1331.h"
#include <stdio.h>
#include <string.h>

#define DC 26
#define RST 27

unsigned char buffer[OLED_WIDTH * OLED_HEIGHT * 2];

static void command(unsigned char cmd) {
  digitalWrite(DC, LOW);
  spiWrite(&cmd, 1);
}

void SSD1331Begin() {
  printf("spiBegin\n");
  spiBegin();

  printf("Exports\n");
  export(RST);
  export(DC);

  printf("pinModes\n");

  pinMode(RST, OUTPUT);
  pinMode(DC, OUTPUT);

  printf("Reset\n");

  digitalWrite(RST, HIGH);
  delay(10);
  digitalWrite(RST, LOW);
  delay(10);
  digitalWrite(RST, HIGH);

  printf("Commands\n");
 
  command(DISPLAY_OFF);                  //Display off
  command(SET_CONTRAST_A);               //Set contrast for color A
  command(0xFF);                         //145 0x91
  command(SET_CONTRAST_B);               //Set contrast for color B
  command(0xFF);                         //80 0x50
  command(SET_CONTRAST_C);               //Set contrast for color C
  command(0xFF);                         //125 0x7D
  command(MASTER_CURRENT_CONTROL);       //master current control
  command(0x06);                         //6
  command(SET_PRECHARGE_SPEED_A);        //Set Second Pre-change Speed For ColorA
  command(0x64);                         //100
  command(SET_PRECHARGE_SPEED_B);        //Set Second Pre-change Speed For ColorB
  command(0x78);                         //120
  command(SET_PRECHARGE_SPEED_C);        //Set Second Pre-change Speed For ColorC
  command(0x64);                         //100
  command(SET_REMAP);                    //set remap & data format
  command(0x72);                         //0x72              
  command(SET_DISPLAY_START_LINE);       //Set display Start Line
  command(0x0);
  command(SET_DISPLAY_OFFSET);           //Set display offset
  command(0x0);
  command(NORMAL_DISPLAY);               //Set display mode
  command(SET_MULTIPLEX_RATIO);          //Set multiplex ratio
  command(0x3F);
  command(SET_MASTER_CONFIGURE);         //Set master configuration
  command(0x8E);
  command(POWER_SAVE_MODE);              //Set Power Save Mode
  command(0x00);                         //0x00
  command(PHASE_PERIOD_ADJUSTMENT);      //Phase 1 and 2 period adjustment
  command(0x31);                         //0x31
  command(DISPLAY_CLOCK_DIV);            //Display clock divider/oscillator frequency
  command(0xF0);
  command(SET_PRECHARGE_VOLTAGE);        //Set Pre-Change Level
  command(0x3A);
  command(SET_V_VOLTAGE);                //Set vcomH
  command(0x3E);
  command(DEACTIVE_SCROLLING);           //Disable scrolling
  command(NORMAL_BRIGHTNESS_DISPLAY_ON); //Set display on
}

void SSD1331Clear(int color) {
  memset(buffer,color,sizeof(buffer));
}

void SSD1331Display() {
  int txLen = 512;
  int remain = sizeof(buffer);
  unsigned char *pBuffer = buffer;

  command(SET_COLUMN_ADDRESS);
  command(0);               //column start address
  command(OLED_WIDTH - 1);  //column end address
  command(SET_ROW_ADDRESS);
  command(0);               //page atart address
  command(OLED_HEIGHT - 1); //page end address
  digitalWrite(DC, HIGH);
  
  while (remain > txLen) {
    spiWrite(pBuffer, txLen);
    remain -= txLen;
    pBuffer += txLen;
  }
  spiWrite(pBuffer, remain);
}


void SSD1331DrawPixel(int x, int y, unsigned short hwColor) {
  if(x >= OLED_WIDTH || y >= OLED_HEIGHT) return;
  buffer[x * 2 + y * OLED_WIDTH * 2] = hwColor >> 8;
  buffer[x * 2 + y * OLED_WIDTH * 2 + 1] = hwColor;
}
