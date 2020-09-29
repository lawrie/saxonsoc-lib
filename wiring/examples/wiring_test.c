#include <stdio.h>
#include "wiring.h"

int main() {
  int i;

  export(0);

  pinMode(0, OUTPUT);

  for(i=0;i<10;i++) {
    digitalWrite(0, i % 2);
    delay(1000);
  }

  return 0;
}
  

