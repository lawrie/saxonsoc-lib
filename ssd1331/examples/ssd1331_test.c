#include <stdio.h>

int main() {
  int i;
  printf("SSD1331Begin\n");
  SSD1331Begin();

  printf("Clear\n");
  SSD1331Clear(0x00);

  //for(i=0; i<64; i++) SSD1331DrawPixel(i, i, 0xF800); 

  printf("String\n");
  SSD1331String(0,0,"Hello World!", 0xF800);

  printf("Display\n");
  SSD1331Display();

  return 0;
}

