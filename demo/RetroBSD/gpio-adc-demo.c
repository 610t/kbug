#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <machine/adc.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/gpio.h>

int fd[16];
int value[16];

void putsym(int c, int count)
{
    while (count-- > 1)
        putchar(c);
}

int main(int argc, char **argv)
{
    char buf[100];
    int i, opt;
    long flags;
    unsigned long delay_msec = 100;
    int gpiooutfd,gpioinfd;
    const char *devout = "/dev/porte";
    const char *devin = "/dev/portd";
    int out=0,in;

    while ((opt = getopt(argc, argv, ":d:")) != -1) {
        switch (opt) {
            case 'd':
                delay_msec = strtol(optarg, 0, 0);
                break;
        }
    }

    /* Init GPIO */
    gpiooutfd = open (devout, 1);
    if (gpiooutfd < 0) {
        perror (devname);
        return -1;
    }
    gpioinfd = open (devin, 1);
    if (gpioinfd < 0) {
        perror (devin);
        return -1;
    }
    ioctl(gpiooutfd, GPIO_PORTE | GPIO_CONFOUT, 0xff);
    ioctl(gpioinfd, GPIO_PORTD | GPIO_CONFIN, 0xff);

    /* Blink LED */
    for(i=0;i<8;i++) {
        ioctl(gpiooutfd,GPIO_PORTE|GPIO_CLEAR,0xff);
        usleep(delay_msec * 1000);
        ioctl(gpiooutfd,GPIO_PORTE|GPIO_SET,0xff);
        usleep(delay_msec * 1000);
    }

    /* Init ADC */
    for (i=0; i<5; i++) {
        sprintf(buf, "/dev/adc%d", i);
        fd[i] = open(buf, O_RDWR);
        if (fd[i] < 0) {
            perror(buf);
            return -1;
        }
        fcntl(fd[i], F_GETFD, &flags);
        flags |= O_NONBLOCK;
        fcntl(fd[i], F_SETFD, &flags);
    }

    /* Clear screen. */
    printf("\33[2J");

    for (;;) {

        /* Top of screen. */
        printf("\33[H");

        /* GPIO output */
        printf("LED output:");
        for(i=0; i<8; i++) {
            if(out & 1<<i) {
              putchar('1');
              ioctl(gpiooutfd,GPIO_PORT(4)|GPIO_SET,1<<i);
            } else {
              putchar('0');
              ioctl(gpiooutfd,GPIO_PORT(4)|GPIO_CLEAR,1<<i);
            }
        }
        printf("\n");

        /* GPIO input */
        in=ioctl(gpioinfd,GPIO_PORTD|GPIO_POLL,0xff);
        printf("LED input:");
        if(in & 0x1) putchar('1'); else putchar('0');
        if(in & 0x2) putchar('1'); else putchar('0');
        printf("\n");

        /* ADC input */
        for (i=0; i<5; i++) {
            if (read(fd[i], buf, 20) > 0) {
                value[i] = strtol(buf, 0, 0);
            }
            printf("adc%-2d %4d  ", i, value[i]);
            putsym('=', value[i] >> 4);

            /* Clear to end of line. */
            printf("\33[K");
            printf("\n");
        }
        usleep(delay_msec * 1000);

        out++;
        if(out>255) out=0;
    }
}
