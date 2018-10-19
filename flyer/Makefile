.SUFFIXES: .dvi .tex .pdf .ps

all: flyer.pdf flyer.ps

flyer.dvi: flyer.tex date.tex

clean:
	rm -rf *.blg *.bbl *.aux *.dvi *.log *.pdf *~

preview: flyer.dvi
	xdvi flyer.dvi

date.tex: flyer.tex
	git log --pretty=format:"%ad" -1 > date.tex

.tex.dvi: $(.IMPSRC)
	(cd figures;${MAKE})
	platex $(.IMPSRC) 
.dvi.pdf: $(.IMPSRC)
	dvipdfm $(.IMPSRC)
#.dvi.ps: $(.IMPSRC)
#	dvips $(.IMPSRC)
#.ps.pdf: 
#	ps2pdf14 -dPDFSETTINGS=/default -sPAPERSIZE=a4 $(.IMPSRC) $(.TARGET)
