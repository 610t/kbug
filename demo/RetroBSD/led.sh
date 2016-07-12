#!/bin/sh
LED_PORT=/dev/porte
# Init port
echo ........iiiioooo > /dev/confe
c=0
out=0000
header=............
while true
do
    if [ `expr ${c} % 4` -eq 0 ]; then
      out=`echo ${out}|sed 's/^.//'|sed 's/$/1/'`
    else
      out=`echo ${out}|sed 's/^.//'|sed 's/$/0/'`
    fi
    echo ${header}${out} > ${LED_PORT}
    echo ${out}
    in=`cat ${LED_PORT}`
    sw=`echo ${in}|sed 's/^........//'|sed 's/....$//'`
    echo ${in}:${sw}
    c=`expr ${c} + 1`
    echo ${c}" "`date`
done
