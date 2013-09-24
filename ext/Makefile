
CC = gcc -Wall -O3

MLINKDIR = /opt/Wolfram/Mathematica/9.0.1/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3 # Set this to ML64i3 if using a 64-bit system

MPREP = ${CADDSDIR}/mprep

HALOFIT = halofit
COSMICEMU = CosmicEmulator

OFILES = math_link.o math_link_tm.o tf_fit.o 
EXTOFILES= $(HALOFIT)/smith2.o $(COSMICEMU)/hubble.o $(COSMICEMU)/emu.o

all: math_link

math_link: $(OFILES) $(HALOFIT) $(COSMICEMU) Makefile
	${CC} -I${INCDIR} -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} $(OFILES) $(EXTOFILES) -o $@

tf_fit.o: tf/tf_fit.c Makefile
	$(CC)  -c -I$(INCDIR) $< -o $@

$(HALOFIT): Makefile
	+$(MAKE) -C $@

$(COSMICEMU): Makefile
	+$(MAKE) -C $@

#TODO make a halofit.o and cosmicemu.o cause of extra linker options

%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

math_link_tm.c: math_link.tm
	${MPREP} $? -o $@


.PHONY: clean $(HALOFIT) $(COSMICEMU)
clean:
	rm -f *o *tm.c math_link
	+$(MAKE) -C $(HALOFIT) clean
