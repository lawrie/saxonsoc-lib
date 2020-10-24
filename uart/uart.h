#ifndef H_UART
#define H_UART

/**
 * Initialize SaxonSoc UART *port*, set the baudrate to the provided speed.
 * Assumes 8 data bits and one stop bit, no parity, no flow control.
 *
 * Returns a file descriptor that can be used to read from or write to the
 * UART, or a negative value in case of an error.
 */
extern int uartBegin(int port, int speed);

#endif
