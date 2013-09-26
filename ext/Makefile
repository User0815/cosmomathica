# Define your C compiler
CC = gcc -Wall -lgfortran -fopenmp

# Define your Fortran compiler (if you want to use CAMB)
F90C = gfortran -fopenmp

# Mathematica related variables - adjust as necessary
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

OFILES = math_link.o math_link_tm.o 


ifeq ($(wildcard tf/tf_fit.c),)
  TRANSFER = 
else
  TRANSFER = tf
  OFILES += $(TRANSFER)/tf_fit.o 
endif 

ifeq ($(wildcard halofit/smith2.c),)
  HALOFIT = 
else
  HALOFIT = halofit
  OFILES += $(HALOFIT)/smith2.o 
endif

ifeq ($(wildcard CosmicEmulator/emu.c),)
  COSMICEMU = 
else
  COSMICEMU = CosmicEmulator
  OFILES += $(COSMICEMU)/hubble.o $(COSMICEMU)/emu.o 
  EXTRALIBS += -lgsl -lgslcblas 
endif

ifeq ($(wildcard camb/camb.f90),)
  CAMB = 
else
  CAMB = camb
  #  EXTRALIBS += -L$(CAMB) -lcamb_recfast 
  OFILES += camb_wrapper.o
endif


all: math_link

math_link: $(HALOFIT) $(COSMICEMU) $(CAMB) $(OFILES) Makefile
	${CC} -I${INCDIR} -L${LIBDIR} -l${MLLIB} $(OFILES) -o $@ ${EXTRALIBS}  camb/*.o

math_link_tm.c: math_link.tm
	${MPREP} $? -o $@


%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

camb_wrapper.o: camb_wrapper.f90 Makefile
	$(F90C) -c $< -o $@ -I$(CAMB) 

$(HALOFIT):
	+$(MAKE) -C $@

$(COSMICEMU):
	+$(MAKE) -C $@

$(CAMB):
	# change from ifort to gfortran
	+$(MAKE) -C $@ all


.PHONY: clean $(HALOFIT) $(COSMICEMU) $(CAMB)

clean:
	rm -f *o *tm.c math_link 
	rm -f $(TRANSFER)/*o
	rm -f $(COSMICEMU)/*exe $(COSMICEMU)/*o
	+$(MAKE) -C $(HALOFIT) clean
	+$(MAKE) -C $(CAMB) clean
