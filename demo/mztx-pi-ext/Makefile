all:
	cc -o loadavg -l rt loadavg.c bcm2835_new.c mztx06a.c

old-all:
	gcc -o mztx06a -l rt mztx06a.c bcm2835.c

init:
	gcc -o lcdinit -l rt lcdinit.c bcm2835.c

new:
	gcc -o lcdpi -l rt lcdpi.c bcm2835.c
