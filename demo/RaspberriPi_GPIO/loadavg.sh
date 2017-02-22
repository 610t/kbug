#!/bin/sh

LEDNUM=6
LOAD_MUL=3
SUDO=/usr/pkg/bin/sudo
MIN=0
MAX=0

while true
do
  # Get loadavg
  loadavg=`uptime | awk '{print $(NF-2)}' | sed -e 's/,//'`
  if [ `echo "${MAX} <= ${loadavg}"|bc` = 1 ]; then
    MAX=${loadavg}
  fi
  led_num=`echo ${loadavg} \* ${LEDNUM} / ${MAX} | bc | awk '{printf "%d",$1}'`
  echo ${loadavg} ${led_num} "(${MIN},${MAX})"
  if [ ${led_num} -gt ${LEDNUM} ]; then
    led_num=${LEDNUM}
  fi

  # clean all LED
  l=`expr ${LEDNUM} - 1`
  while [ ${l} -ge 0 ]
  do
    led="led"${l}
    gpioctl /dev/gpio0 ${led} 0 > /dev/null
    l=`expr ${l} - 1`
  done

  # Light on
  l=0
  while [ ${l} -lt ${LEDNUM} ]
  do
    led="led"${l}
    if [ ${l} -lt ${led_num} ]; then
      gpioctl /dev/gpio0 ${led} 1 > /dev/null
    else
      gpioctl /dev/gpio0 ${led} 0 > /dev/null
    fi
    l=`expr ${l} + 1`
  done
done
