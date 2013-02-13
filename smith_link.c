#include <stdio.h>
#include"mathlink.h"
#include "halofit/smith2.h"

void smith_set_parameters_wrap(double OMEGAM, double OMEGAV, double GAMMA, double SIGMA8,
		   double NSPEC, double BETAP, double Z0, int NONLINEAR) {

    /* get parameters from mathlink */
  setparameters_(&OMEGAM, &OMEGAV, &GAMMA, &SIGMA8,
		   &NSPEC, &BETAP, &Z0, &NONLINEAR);

  MLPutInteger(stdlink, 0); /* We need to return *something* */

}

void smith_P_NL_wrap(double a, double k){
  double pnl;
  pnl = P_NL(a, k);
  MLPutReal64(stdlink, pnl);
}

void smith_P_L_wrap(double a, double k){
  double pl;
  pl = P_L(a, k);
  MLPutReal64(stdlink, pl);
}

int main(int argc, char* argv[]) {
   return MLMain(argc, argv);
}
