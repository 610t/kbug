.SUFFIXES: .png .gif .eps .jpg .svg

TARGETS=OSC2008-logo.eps kbug-logo.eps \
	banner2008.eps CIMG2521.eps CIMG2018.eps CIMG0535.eps \
	kyoto_tower.eps banner.eps CIMG3131.eps \
	banner2009.eps \
	logo-kobe-2010.eps kof2009-1.eps \
	74251436.eps \
	logo-kyoto-2011.eps

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
