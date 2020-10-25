#include <stdint.h>
#include <fcntl.h>

#include "termbits.h"

#define _IOC_WRITE    1U
#define _IOC_READ     2U

#define _IOC_NRBITS     8
#define _IOC_TYPEBITS   8
#define _IOC_SIZEBITS  14
#define _IOC_DIRBITS    2

#define _IOC_NRSHIFT    0
#define _IOC_TYPESHIFT  (_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT  (_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT   (_IOC_SIZESHIFT+_IOC_SIZEBITS)

#define _IOC_TYPECHECK(t) (sizeof(t))

#define _IOC(dir,type,nr,size) \
        (((dir)  << _IOC_DIRSHIFT) | \
         ((type) << _IOC_TYPESHIFT) | \
         ((nr)   << _IOC_NRSHIFT) | \
         ((size) << _IOC_SIZESHIFT))

#define _IOR(type,nr,size)     _IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOW(type,nr,size)     _IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))

#define TCGETS2               _IOR('T', 0x2A, struct termios2)
#define TCSETS2               _IOW('T', 0x2B, struct termios2)

int uartBegin(int port, int speed)
{
    struct termios2 tty;
    char portname[32];
    int fd;

    if (port > 9)
        return -1;

    strncpy(portname, "/dev/ttySL0", sizeof(portname));
    portname[10] += port;

    fd = open(portname, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        return -1;
    }

    if (ioctl(fd, TCGETS2, &tty) != 0) {
        close(fd);
        return -1;
    }
    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* custom baudrate setting */
    tty.c_cflag &= ~CBAUD;
    tty.c_cflag |= BOTHER;
    tty.c_ispeed = speed;
    tty.c_ospeed = speed;

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available, block forever as needed */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (ioctl(fd, TCSETS2, &tty) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}
