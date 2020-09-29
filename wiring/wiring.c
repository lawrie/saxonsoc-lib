#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include "wiring.h"

#define GPIO_BASE 480

static char gpio[4];
static char dev[] = "/sys/class/gpio/";
static char buf[34];

static void error(char *msg, int r) {
  if (r < 0) {
    printf("errno from %s is %d\n", msg, errno);
    abort();
  }
}

static void send(char *fname, char *val) {
  int f = open(fname, O_WRONLY);
  error(fname, f);

  write(f, val, strlen(val));
  close(f);
}

void export(int pin) {
  sprintf(buf,"%sexport", dev);
  sprintf(gpio, "%d", GPIO_BASE + pin);
  send(buf, gpio);
}

void unexport(int pin) {
  sprintf(buf,"%sunexport", dev);
  sprintf(gpio, "^d", GPIO_BASE + pin);
  send(buf, gpio);
}

void pinMode(int pin, int value) {
  sprintf(gpio, "%d", GPIO_BASE + pin);
  sprintf(buf,"%sgpio%s/direction", dev, gpio);
  send(buf,"out");
}

void digitalWrite(int pin, int value) {
  sprintf(gpio, "%d", GPIO_BASE + pin);
  sprintf(buf,"%sgpio%s/value", dev, gpio);
  send(buf, value ? "1" : "0"); 
}

void delay(int msec) {
  usleep(msec * 1000);
}

