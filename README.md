
External programs
=================

Due to copyright issues, the external packages cannot be delivered as part
of this package. You need to download the source code of the following
programs yourself. To make sure you got the right version, the MD5 sums of
the files in question are given here.

  * Transfer function: 
    tf_fit.c                [38ef737fe3bab405bac17db78815559f]
    http://background.uchicago.edu/~whu/transfer/transferpage.html

  * Halofit+:
    halofit+.tar            [4ce61ec6504a2f7cf750ab007142dea8]
    http://www.roe.ac.uk/~jap/haloes/

  * CAMB (July 2013):
    CAMB.tar.gz             [a538bb607cca96c4b2f8b1fece898411]  
    http://camb.info/

  * CosmicEmulator "Coyote" (v1.1):
    CosmicEmu_v1.1.tar.gz   [a3c7da2b41152b7d30ba458e56f7e4ab]  
    http://www.lanl.gov/projects/cosmology/CosmicEmu/emu.html

The (extracted) files need to placed in directories with names 'tf',
'halofit', 'camb', and 'CosmicEmulator', respectively, inside the 'ext'
directory.


How to compile the MathLink
===========================

Type `make`...
