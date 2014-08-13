FILENAME = main

all:
	pdflatex $(FILENAME).tex
	bibtex $(FILENAME)
	pdflatex $(FILENAME).tex
	pdflatex $(FILENAME).tex

clean:
	rm -f *~ *.aux *.bbl *.blg *.log *.out *.toc
