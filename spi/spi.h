#define 	SPI_CPHA   0x01 /* clock phase */
#define 	SPI_CPOL   0x02 /* clock polarity */
#define 	SPI_MODE_0   (0|0) /* (or
#define 	SPI_MODE_3   (SPI_CPOL|SPI_CPHA)
#define 	SPI_CS_HIGH   0x04 /* chipselect active high? */
#define 	SPI_LSB_FIRST   0x08 /* per-word bits-on-wire */

extern void spiBegin(void);
extern int spiWrite(unsigned char *data, int len);

