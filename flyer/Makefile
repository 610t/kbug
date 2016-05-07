.SUFFIXES: .dvi .tex .pdf

all: flyer.pdf

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
