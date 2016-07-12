#!/bin/sh
# BTN (RA4, RA5)
echo ----------ii---- > /dev/confa
# LED (RG6, RD4, RB11, RG15)
echo o--------o------ > /dev/confg
echo -----------o---- > /dev/confd
echo ----o----------- > /dev/confb
while true
do
  BTN=`cat /dev/porta|cut -c 11-12`
  echo 'BTN:'${BTN}
  if [ x`echo ${BTN}|cut -c 1` = "x1" ]; then
    echo ----1----------- > /dev/portb
  else
    echo ----0----------- > /dev/portb
  fi
  if [ x`echo ${BTN}|cut -c 2` = "x1" ]; then
    echo -----------1---- > /dev/portd
  else
    echo -----------0---- > /dev/portd
  fi
done
