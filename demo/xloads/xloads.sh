#!/bin/sh
XLOAD_HOSTS="192.168.60.1 192.168.60.12 192.168.60.14 192.168.60.16 192.168.7.2"
XSIZE=600
YSIZE=300
XMAX=3

## ssh
if [ x"${SSH_AGENT_PID}" = x"" ];then
  eval `ssh-agent -s`
  ssh-add
fi

# force DISPLAY at :0
export DISPLAY=:0

# Off bell and screensaver
xset b off
xset s off

## xload
xc=0
yc=0
for h in ${XLOAD_HOSTS}
do
  x=`expr ${xc} \* ${XSIZE}`
  y=`expr ${yc} \* ${YSIZE}`
  echo "Host: ${h} (${xc},${yc}):(${x},${y})"
  ssh -X ${h}	"source ~/.path;xload -geometry ${XSIZE}x${YSIZE}+${x}+${y}" &
  sleep 5
  if [ `expr ${xc} % ${XMAX}` -eq `expr ${XMAX} - 1` ];then
    xc=0
    yc=`expr ${yc} + 1`
  fi
  xc=`expr ${xc} + 1`
done
