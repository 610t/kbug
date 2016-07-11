#!/bin/sh

pos=0
pos_max=239
wait_time=1

sudo ./osc2016kyoto -c

while true
do
  avg=`uptime|awk '{print $10}' | sed 's/,//'`
  echo ${pos} ${avg}

  sudo ./osc2016kyoto ${pos} ${avg}

  pos=`expr ${pos} + 1`
  if [ ${pos} -gt ${pos_max} ]; then
    pos=0
  fi
  sleep ${wait_time}
done
