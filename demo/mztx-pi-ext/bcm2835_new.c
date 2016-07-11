#include "bcm2835.h"

#include <fcntl.h>
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
#include <sys/gpio.h>

int pin, val, fd;
char ctrlfile[]="/dev/gpioc0";

int bcm2835_init()
{
  if ( (fd = open(ctrlfile, O_RDONLY)) < 0 )  {
    perror("open");
    exit(1);
  }
  
  return 1;
}

void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode)
{
  struct gpio_pin gpiopin;
  
  gpiopin.gp_pin = pin;
  if(mode==BCM2835_GPIO_FSEL_OUTP)
    {
      gpiopin.gp_flags = GPIO_PIN_OUTPUT;
    } 
  if ( ioctl(fd, GPIOSETCONFIG, &gpiopin) < 0 )  {
    perror("ioctl(GPIOSETCONFIG)");
    exit(1);
  }  
}

void bcm2835_gpio_write(uint8_t pin,uint8_t val)
{
  struct gpio_req gpioreq;

  gpioreq.gp_pin = pin;
  gpioreq.gp_value = val;
  if ( ioctl(fd, GPIOSET, &gpioreq) < 0 )  {
    perror("ioctl(GPIOWRITE)");
    exit(1);
  }  
}

void bcm2835_gpio_clr(uint8_t pin)
{
  bcm2835_gpio_write(pin,0);
}

void bcm2835_gpio_set(uint8_t pin)
{
  bcm2835_gpio_write(pin,1);
}

// Some convenient arduino like functions
// milliseconds
void bcm2835_delay(unsigned int millis)
{
  struct timespec sleeper;

  sleeper.tv_sec  = (time_t)(millis / 1000);
  sleeper.tv_nsec = (long)(millis % 1000) * 1000000;
  nanosleep(&sleeper, NULL);
}
