# Define your C compiler
CC = gcc -O2 -Wall -lgfortran -fopenmp

# C++ compiler for copter
CPP = g++ -O2 -fopenmp

# Define your Fortran compiler (if you want to use CAMB) Must match CAMB
# compiler
F90C = gfortran -O2 -fopenmp -Wall -Wextra -Wconversion-extra -cpp

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


# Check if the external programs are present

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
  OFILES += camb_wrapper.o 
  CAMBOFILES = $(CAMB)/*.o
  CC += -DCAMB
endif

ifeq ($(wildcard copter-0.8.7/Makefile.am),)
  COPTER = 
else
  COPTER = copter-0.8.7
  OFILES += copter_wrapper.o
  CC += -DCOPTER 
  CPP += -I$(COPTER)/include 
  EXTRALIBS += $(COPTER)/lib/libcopter.a  
endif

all: math_link

math_link: $(HALOFIT) $(COSMICEMU) $(CAMB) $(COPTER) $(OFILES) Makefile
	${CC} -I${INCDIR} -L${LIBDIR} -l${MLLIB} $(OFILES) $(CAMBOFILES) -o $@ ${EXTRALIBS}  

math_link_tm.c: math_link.tm
	${MPREP} $? -o $@


%.o: %.c
	$(CC)  -c -I$(INCDIR) $< -o $@

camb_wrapper.o: camb_wrapper.f90 Makefile
	$(F90C) -c $< -o $@ -I$(CAMB) 

copter_wrapper.o: copter_wrapper.cpp Makefile
	$(CPP) -c $< -o $@

$(HALOFIT):
	+$(MAKE) -C $@

$(COSMICEMU):
	+$(MAKE) -C $@

$(CAMB):
	./patchmakefile.sh
	+$(MAKE) -C $@

$(COPTER): $(COPTER)/lib/libcopter.a

$(COPTER)/lib/libcopter.a: $(COPTER)/Makefile
	$(MAKE) -C $(COPTER) 
	$(MAKE) -C $(COPTER) install 

$(COPTER)/Makefile:
	cd $(COPTER) && ./configure --prefix=`pwd`


download:
	./download.sh

cleanall:
	rm -rf  $(HALOFIT) $(COSMICEMU) $(TRANSFER) $(COPTER) $(CAMB)

clean:
	rm -f *o *tm.c math_link testwrapper
	if [ ! -z $(TRANSFER) ]; then rm -f $(TRANSFER)/*o; fi
	if [ ! -z $(COSMICEMU) ]; then rm -f $(COSMICEMU)/*exe $(COSMICEMU)/*o ; fi
	if [ ! -z $(HALOFIT) ]; then $(MAKE) -C $(HALOFIT) clean ; fi
	if [ ! -z $(CAMB) ]; then $(MAKE) -C $(CAMB) clean ; fi
	if [ ! -z $(COPTER) ]; then $(MAKE) -C $(COPTER) uninstall clean distclean ; fi

.PHONY: clean $(HALOFIT) $(COSMICEMU) $(CAMB) $(COPTER) download cleanall
