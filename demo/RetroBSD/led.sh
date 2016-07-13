#!/bin/sh
LED_PORT=/dev/porte
ADC_PITCH=50

# Init port
echo ........iiiioooo > /dev/confe
c=0
out=0000
header=............
while true
do
    # ADC
    dev=0
    while [ ${dev} -lt 4 ]
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
