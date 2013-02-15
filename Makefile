
CC = gcc -Wall -O3

MLINKDIR = /opt/Wolfram/Mathematica/8.0/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3 # Set this to ML64i3 if using a 64-bit system

MPREP = ${CADDSDIR}/mprep

TFOFILES = tf_fit_tm.o tf_fit_link.o tf_fit.o 

all: tf_fit_link

tf_fit_link:  $(TFOFILES)
	${CC} -I${INCDIR} $(TFOFILES)  -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} -o $@

tf_fit.o: tf/tf_fit.c
	$(CC)  -c -I$(INCDIR) $< -o $@

%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

tf_fit_tm.c: tf_fit.tm
	${MPREP} $? -o $@


.PHONY: clean
clean:
	rm -f *o *tm.c tf_fit_link *o *tm.c

