.SUFFIXES: .png .gif .eps .jpg .svg

TARGETS= 

all: ${TARGETS}

clean:
	rm ${TARGETS}

.gif.eps: $(.IMPSRC)
	convert $(.IMPSRC) $(.TARGET)

.png.eps: $(.IMPSRC)
	convert $(.IMPSRC) $(.TARGET)
.jpg.eps: $(.IMPSRC)
	convert $(.IMPSRC) $(.TARGET)
.svg.eps: $(.IMPSRC)
	inkscape --export-eps=$(.TARGET) $(.IMPSRC)
