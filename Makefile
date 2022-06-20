#all
#install
#uninstall
#clean
#dvi
#dist
#tests
#gcov_report

all: clean build

build:
	gcc smartcalc.c expression-handler.c lists-handler.c

clean:
	rm -rf a.out