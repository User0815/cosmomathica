
CC = gcc -Wall -O3

MLINKDIR = /opt/Wolfram/Mathematica/9.0.1/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3 # Set this to ML64i3 if using a 64-bit system

MPREP = ${CADDSDIR}/mprep

OFILES = math_link_tm.o math_link.o tf_fit.o 

all: math_link

math_link:  $(OFILES) Makefile
	${CC} -I${INCDIR} $(OFILES)  -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} -o $@

tf_fit.o: tf/tf_fit.c Makefile
	$(CC)  -c -I$(INCDIR) $< -o $@

%.o: %.c Makefile
	$(CC)  -c -I$(INCDIR) $< -o $@

math_link_tm.c: math_link.tm Makefile
	${MPREP} $? -o $@


.PHONY: clean
clean:
	rm -f *o *tm.c math_link

