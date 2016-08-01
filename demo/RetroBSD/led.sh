#!/bin/sh
LED_PORT=/dev/porte
SW_PORT=/dev/portd
ADC_PITCH=50

# Blink all LEDs 8 times.
blink () {
  l=0
  while [ ${l} -lt 8 ]
  do
    echo ........11111111 > /dev/porte
#    sleep 1
    echo ........00000000 > /dev/porte
#    sleep 1
    l=`expr ${l} + 1`
  done
}

# Init port
echo ........oooooooo > /dev/confe
echo ..............ii > /dev/confd
c=0
out=00000000
header=........

blink

while true
do
    # ADC
    dev=0
    # Currently skip adc input.
    while [ ${dev} -lt 0 ]
#    while [ ${dev} -lt 5 ]
    do
        adc=`cat /dev/adc${dev}|head -1`
        echo -n "ADC\t${dev}:\t"${adc}"\t"
        adc_div=`expr ${adc} / ${ADC_PITCH}`
        i=0
        while [ ${i} -lt ${adc_div} ]
        do
            echo -n "="
            i=`expr ${i} + 1`
        done
        echo
        dev=`expr $dev + 1`
    done
    echo "---"

    # GPIO LED
#    echo "2 o ${c} p" | dc
    if [ `expr ${c} % 8` -eq 0 ]; then
      out=`echo ${out}|sed -e 's/^.//' -e 's/$/1/'`
    else
      out=`echo ${out}|sed -e 's/^.//' -e 's/$/0/'`
    fi
    echo ${header}${out} > ${LED_PORT}
    echo ${out}
#    in=`cat ${LED_PORT}`
#    sw=`echo ${in}|sed 's/^........//'|sed 's/....$//'`
#    echo ${in}:${sw}
    c=`expr ${c} + 1`
#    echo ${c}" "`date`

    # GPIO SW
    portd=`cat /dev/portd`
    sw=`echo ${portd}|sed -e 's/^-*\([01]\).$/\1/'`
    echo "SW:${sw}(${portd})"
    if [ ${sw} -eq 1 ]; then
      blink
    fi
done
