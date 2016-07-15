#!/bin/sh

while true
do
  l=0
  while [ ${l} -lt 6 ]
  do
    led="led"${l}
    sudo gpioctl /dev/gpio0 ${led} 1
    sudo gpioctl /dev/gpio0 ${led} 0
    l=`expr ${l} + 1`
  done
done
