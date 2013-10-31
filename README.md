What is cosmomathica?
=====================

Wolfram Mathematica is a powerful and convenient software package used by
many cosmologists everywhere. However, since it is not always the most
efficient for low-level computing, most popular algorithms for numerical
computations in cosmology have been written in C or Fortran, since these
languages are typically much better suited for the task at hand. This
package bundles the functionality of some of these algorithms in
a Mathematica package, which makes them easier to use and avoids the need to
learn C or Fortran.

It makes use of the MathLink technology, which means that the original
source code remains untouched. The algorithms are not reimplemented either,
because that would negate the advantage of having them implemented in
a lower level language in terms of efficiency. On top of that, it would
inevitably introduce new bugs given the complexity of these algorithms.

For further details on how MathLink works, see
http://arxiv.org/abs/1107.4379.

For a detailed documentation of cosmomathica, see XXXX


Requirements
============

  * Wolfram Mathematica version ??

  * For CosmicEmulator: GSL (GNU Scientific Library)

  * For CAMB: Possibly cfitsio, healpix

  * The GNU Compiler Compilation (gcc) version ??


External programs
=================

Due to copyright issues, the external packages cannot be delivered as part
of this package. You need to download the source code of the following
programs yourself. To make sure you got the right version, the MD5 sums of
the files in question are given here.

  * Transfer function: 
    tf_fit.c                [38ef737fe3bab405bac17db78815559f]
    http://background.uchicago.edu/~whu/transfer/transferpage.html
    Daniel Eisenstein and Wayne Hu 

  * Halofit+:
    halofit+.tar            [4ce61ec6504a2f7cf750ab007142dea8]
    http://www.roe.ac.uk/~jap/haloes/
    Robert Smith et al, Martin Kilbinger

  * CAMB (July 2013):
    CAMB.tar.gz             [a538bb607cca96c4b2f8b1fece898411]  
    http://camb.info/
    Antony Lewis and Anthony Challinor

  * CosmicEmulator "Coyote" (v1.1):
    CosmicEmu_v1.1.tar.gz   [a3c7da2b41152b7d30ba458e56f7e4ab]  
    http://www.lanl.gov/projects/cosmology/CosmicEmu/emu.html
    Heitman et al

The (extracted) files need to placed in directories with names `tf`,
`halofit`, `camb`, and `CosmicEmulator`, respectively, inside the `ext`
directory.

If you wish to use a different version of CAMB, for instance, cosmomathica
may still work, but it has not been tested for it. If you use a modified
version of CAMB, the same applies. In general, if you modify things like the
type `CAMBparams`, you almost certainly will have to modify cosmomathica as
well.


How to compile the MathLink
===========================

The paths to the required Mathematica libraries are often different on every
system, so first you should adjust the Mathematica-related lines in the
Makefile, which is located in the `ext` directory. Next, change into the
`ext` directory and type `make`. 

CAMB uses the Intel Fortran compiler by default. Due to compatibility issues
with linking the different object files, CAMB needs to be compiled with GNU
gfortran. When building the MathLink, CAMB's Makefile is automatically
changed accordingly.

Note that all warnings and errors that you see may be cause by the external
programs. Make sure the warning is not from compiling the MathLink and
contact the respective authors if you have concerns. Otherwise, feel free to
file a bug report on GitHub.


How to use Cosmomathica
=======================

In general, each one of the functions `CAMB`, `Transfer`, `Halofit`, and
`CosmicEmu` returns a list of replacement rules containing the raw data as
computed by the respective program. See the notebook "demo.nb" for
a demonstration. 


Copyright and licensing
=======================

Cosmomathica is released under the GPL2. Contributions are welcome.
