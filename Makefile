
CC = gcc -Wall -O3

MLINKDIR = /opt/Wolfram/Mathematica/8.0/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3 # Set this to ML64i3 if using a 64-bit system

MPREP = ${CADDSDIR}/mprep

TFOFILES = tf/tf_fit_tm.o tf/tf_fit_link.o tf/tf_fit.o 
SMITHOFILES = halofit/smith_link.o halofit/smith_tm.o halofit/smith2.o

all: smith_link tf_fit_link

tf_fit_link:  $(TFOFILES)
	${CC} -I${INCDIR} $(TFOFILES)  -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} -o $@

smith_link: $(SMITHOFILES)
	${CC} -I${INCDIR} $(SMITHOFILES)  -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} -o $@
	
%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

tf/tf_fit_tm.c: tf/tf_fit.tm
	${MPREP} $? -o $@

halofit/smith_tm.c: halofit/smith.tm
	${MPREP} $? -o $@

.PHONY: clean
clean:
	rm -f tf/*o tf/*tm.c tf_fit_link halofit/*o halofit/*tm.c smith_link

