# Define your C compiler
CC = gcc -Wall -lgfortran -fopenmp

# Define your Fortran compiler (if you want to use CAMB) Must match CAMB
# compiler
F90C = gfortran -fopenmp -Wall -Wextra -Wconversion-extra -cpp

# Mathematica related variables - adjust as necessary
MLINKDIR = /opt/Wolfram/Mathematica/9.0.1/SystemFiles/Links/MathLink/DeveloperKit
# Set this value with the result of evaluating $SystemID:
SYS = Linux-x86-64
# Set these with appropriate libs for your system:
EXTRALIBS = -lm -lpthread -lrt -lstdc++ 
# Set this to ML64i3 if using a 64-bit system:
MLLIB = ML64i3


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
  CC += -DTRANSFER
endif 

ifeq ($(wildcard halofit/smith2.c),)
  HALOFIT = 
else
  HALOFIT = halofit
  OFILES += $(HALOFIT)/smith2.o 
  CC += -DHALOFIT
endif

ifeq ($(wildcard CosmicEmulator/emu.c),)
  COSMICEMU = 
else
  COSMICEMU = CosmicEmulator
  OFILES += $(COSMICEMU)/hubble.o $(COSMICEMU)/emu.o 
  EXTRALIBS += -lgsl -lgslcblas 
  CC += -DCOSMICEMU
endif

ifeq ($(wildcard camb/camb.f90),)
  CAMB = 
else
  CAMB = camb
  OFILES += camb_wrapper.o camb/*.o
  CC += -DCAMB
endif


all: math_link

math_link: $(HALOFIT) $(COSMICEMU) $(CAMB) $(OFILES) Makefile
	${CC} -I${INCDIR} -L${LIBDIR} -l${MLLIB} $(OFILES) -o $@ ${EXTRALIBS}  

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
	+$(MAKE) -C $@


download:
	./download.sh

cleanall:
	rm -rf  $(HALOFIT) $(COSMICEMU) $(TRANSFER)

clean:
	rm -f *o *tm.c math_link testwrapper
	if [ ! -z $(TRANSFER) ]; then rm -f $(TRANSFER)/*o; fi
	if [ ! -z $(COSMICEMU) ]; then rm -f $(COSMICEMU)/*exe $(COSMICEMU)/*o ; fi
	if [ ! -z $(HALOFIT) ]; then $(MAKE) -C $(HALOFIT) clean ; fi
	if [ ! -z $(CAMB) ]; then $(MAKE) -C $(CAMB) clean ; fi

.PHONY: clean $(HALOFIT) $(COSMICEMU) $(CAMB) download cleanall
