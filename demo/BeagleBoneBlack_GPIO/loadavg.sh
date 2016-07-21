#!/bin/sh

c=0
while true
do
  load=`uptime|awk '{printf "%s",$(NF-2)}'|sed -e 's/,//'`
  led_on=`echo "${load} * 4 / 2"|bc`
  echo "Load:"${load}",LED:"${led_on}
  c=0
  for d in heartbeat mmc0 usr2 usr3
  do
        dev=/dev/led/beaglebone:green:${d}

        if [ ${c} -lt ${led_on} ]; then
          echo 1 > ${dev}
        else
          echo 0 > ${dev}
        fi
        echo 0 > ${dev}
        c=`expr ${c} + 1`
  done
done
