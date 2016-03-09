.SUFFIXES: .dvi .tex .pdf

all: OSC2008flyer.pdf

clean:
	rm -rf *.blg *.bbl *.aux *.dvi *.log *.pdf *~

preview: flyer.dvi
	xdvi flyer.dvi

.tex.dvi: $(.IMPSRC)
	platex $(.IMPSRC) 
.dvi.pdf: $(.IMPSRC)
	dvipdfmx $(.IMPSRC)
