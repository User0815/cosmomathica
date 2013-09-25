# Adjust the following four lines if necessary
MLINKDIR = /opt/Wolfram/Mathematica/9.0.1/SystemFiles/Links/MathLink/DeveloperKit
SYS = Linux-x86-64# Set this value with the result of evaluating $SystemID
EXTRALIBS = -lm -lpthread -lrt -lstdc++ # Set these with appropriate libs for your system.
MLLIB = ML64i3# Set this to ML64i3 if using a 64-bit system


# No changes necessary below this line
# ====================================

CADDSDIR = ${MLINKDIR}/${SYS}/CompilerAdditions
INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}
MPREP = ${CADDSDIR}/mprep

CC = gcc -Wall -O3

TRANSFER = tf
HALOFIT = halofit
COSMICEMU = CosmicEmulator
EXTRALIBS += -lgsl -lgslcblas # if cosmicemu is requested we need these
CAMB = camb


OFILES = math_link.o math_link_tm.o 
OFILES += $(HALOFIT)/smith2.o 
OFILES += $(COSMICEMU)/hubble.o $(COSMICEMU)/emu.o 
OFILES += $(TRANSFER)/tf_fit.o 
#  OFILES += $(CAMB)
#  TODO


all: math_link

math_link: $(HALOFIT) $(COSMICEMU) $(OFILES) Makefile
	${CC} -I${INCDIR} -L${LIBDIR} -l${MLLIB} ${EXTRALIBS} $(OFILES) -o $@

math_link_tm.c: math_link.tm
	${MPREP} $? -o $@


%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

$(HALOFIT):
	+$(MAKE) -C $@

$(COSMICEMU):
	+$(MAKE) -C $@

$(CAMB):
	+$(MAKE) -C $@


.PHONY: clean $(HALOFIT) $(COSMICEMU)

clean:
	rm -f *o *tm.c math_link 
	rm -f $(TRANSFER)/*o
	rm -f $(COSMICEMU)/*exe $(COSMICEMU)/*o
	+$(MAKE) -C $(HALOFIT) clean
	+$(MAKE) -C $(CAMB) clean
