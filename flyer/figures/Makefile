.SUFFIXES: .png .gif .eps

TARGETS=OSC2008-logo.eps kbug-logo.eps

all: ${TARGETS}

clean:
	rm ${TARGETS}

.gif.eps: $(.IMPSRC)
	convert $(.IMPSRC) $(.TARGET)

.png.eps: $(.IMPSRC)
	convert $(.IMPSRC) $(.TARGET)
