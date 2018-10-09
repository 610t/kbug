# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
SPHINXPROJ    = KBUGBoothGuide
SOURCEDIR     = .
BUILDDIR      = _build

WEBDIR	="sacraya.610t.org:/mnt/vela/www/apache22/data/kbug/book/booth/"

all:
	${MAKE} html
	${MAKE} singlehtml
	rst2pdf -s ja.json index-ja.rst -o KBUGBoothGuide.pdf
	gs -q -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=book.pdf AsiaBSDConCover.pdf KBUGBoothGuide.pdf BackCover.pdf

sync:
	rsync -azv _build/ ${WEBDIR}
	rsync KBUGBoothGuide.pdf ${WEBDIR}/KBUGBoothGuide.pdf
	rsync book.pdf ${WEBDIR}/KBUGBoothGuide-print.pdf

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
