.SUFFIXES: .png .gif .eps .jpg .svg

TARGETS= \
	osc2018-kyoto-logo.eps facebook_banner.eps daimonji.eps distcc-rpi.eps \
	osc2015-kyoto-logo.eps osc2015-kyoto-booth.eps kbug-summervacation-raspi.eps \
	kof2014-logo.eps kof2012-atc.eps kof2012-mutoh.eps osc2013kyoto.eps osc2013icat.eps oval-seal-4.eps \
	osc2013-kyoto-logo.eps MyKyotoIchiba.eps kbug.gr.jp.eps KOF2012Booth.eps mailto.kbug-users.eps qml.610t.org.freebsd.OSC2013Kyoto.eps \
	KOF2012.eps 514px-Atc_osaka03s3200.eps osc2012booth.eps event_nnct.eps seal2.eps \
	turret.eps osc2012-kyoto.eps 1310698938093.eps \
	logo-kyoto-2011.eps \
	74251436.eps \
	logo-kobe-2010.eps kof2009-1.eps \
	banner2009.eps \
	kyoto_tower.eps banner.eps CIMG3131.eps \
	banner2008.eps CIMG2521.eps CIMG2018.eps CIMG0535.eps \
	OSC2008-logo.eps kbug-logo.eps \

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
