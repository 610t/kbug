#!/bin/sh

LEDNUM=6
LOAD_MUL=3
SUDO=/usr/pkg/bin/sudo

while true
do
  loadavg=`uptime | awk '{print $(NF-2)}' | sed -e 's/,//'`
  led_num=`echo ${loadavg} \* ${LOAD_MUL} | bc | awk '{printf "%d",$1}'`
  echo ${loadavg} ${led_num}
  if [ ${led_num} -gt ${LEDNUM} ]; then
    led_num=${LEDNUM}
  fi
  l=0
  while [ ${l} -lt ${led_num} ]
  do
    led="led"${l}
    gpioctl /dev/gpio0 ${led} 0 > /dev/null
    gpioctl /dev/gpio0 ${led} 1 > /dev/null
    l=`expr ${l} + 1`
  done
  while [ ${l} -lt ${LEDNUM} ]
  do
    led="led"${l}
    gpioctl /dev/gpio0 ${led} 0 > /dev/null
    l=`expr ${l} + 1`
  done
done
