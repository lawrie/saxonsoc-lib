#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

extern void delay(int msec);
extern void pinMode(int pin, int mode);
extern void digitalWrite(int pin, int value);
extern void export(int pin);
extern void unexport(int pin);
