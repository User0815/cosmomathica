#include <stdio.h>
#include "smith2.h"

int main()
{
   real k, ell;


   set_cosmological_parameters_to_default();
   dump_param(stdout);


   /* density power spectrum */

   printf("# k[Mpc/h] Delta_NL(a=0.5,k)\n");
   for (k=1.0e2; k<=1.0e7; k*=1.5) {
      printf("%e %e\n", k/2998.0, k*k*k/2/pi/pi*P_NL(0.5, k));
   }


   /* convergence power spectrum */

   printf("# l l(l+1)/2pi*P_kappa(l)\n");
   for (ell=2.0; ell<=1.0e5; ell*=1.05) {
      printf("%e %e\n", ell, ell*(ell+1)/twopi*Pkappa(ell));
   }


   return 0;
}
