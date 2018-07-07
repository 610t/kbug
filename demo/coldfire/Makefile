.SUFFIXES:	.c .o .bin
CFLAGS+=	-g -I/usr/local/include
TARGET=		coldfire_shape.bin coldfire_glxgears.bin
# TARGET=		coldfire_shape coldfire_glxgears my_shape my_test my_test2
COLDFIRE_LIBS=	coldfire.o
LDFLAGS+=	-L/usr/local/lib -lGL -lXext -lX11 -lm
COLDFIRE_LDFLAGS+=	${COLDFIRE_LIBS} ${LDFLAGS}

all:		${TARGET} ${COLDFIRE_LIBS} 

clean:
	rm ${TARGET} *~ *.o 

# LIB for coldfire
coldfire.o:	coldfire.c coldfire.h

# TARGET binary
coldfire_shape.bin: coldfire_shape.o ${COLDFIRE_LIBS}
#	${CC} -g -o coldfire_shape coldfire_shape.o ${COLDFIRE_LDFLAGS}
coldfire_glxgears.bin: coldfire_glxgears.o ${COLDFIRE_LIBS}
#	${CC} -g -o coldfire_glxgears coldfire_glxgears.o ${COLDFIRE_LDFLAGS}
#my_shape: my_shape.o
#	${CC} -g -o my_shape my_shape.o ${LDFLAGS}
#my_test:	my_test.o
#	${CC} -g -o my_test my_test.o ${LDFLAGS}
#my_test2:	my_test2.o
#	${CC} -g -o my_test2 my_test2.o ${LDFLAGS}

.o.bin:
	${CC} -g -o $@ $< ${COLDFIRE_LDFLAGS}

#.c.o:
#	${CC} -g -o $@ $< 
#	echo $@ $< 
