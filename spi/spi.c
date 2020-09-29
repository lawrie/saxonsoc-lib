#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "spi.h"

static int f;
static char *dev = "/dev/spidev0.2";

static void error(char *msg, int r) {
  if (r < 0) {
    printf("errno from %s is %d\n", msg, errno);
    abort();
  }
}

void spiBegin() {
  f = open(dev, O_WRONLY);
  printf("f is %d\n", f);
  error(dev, f);
}


int spiWrite(unsigned char *buf, int len) {
  int r = write(f, buf, len);
  
  error("writing", r);
  return r;
}


  
