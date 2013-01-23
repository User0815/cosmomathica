
CC = gcc -Wall -O4

MLINKDIR = /opt/Wolfram/Mathematica/8.0/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3 # Set this to ML64i3 if using a 64-bit system

MPREP = ${CADDSDIR}/mprep

OFILES = tf/tf_fit_tm.o tf/tf_fit_link.o tf/tf_fit.o

tf_fit_link:  $(OFILES)
	${CC} -I${INCDIR} $(OFILES)  -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} -o $@

%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

tf/tf_fit_tm.c: tf/tf_fit.tm
	${MPREP} $? -o $@

.PHONY: clean
clean:
	rm -f tf/*o tf/*tm.c tf_fit_link
