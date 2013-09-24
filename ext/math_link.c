#include <stdio.h>
#include "mathlink.h"

#include "halofit/smith2.h"

/* TF Transfer function from Eisenstein&hu */

extern void TFset_parameters(float omega0hh, float f_baryon, float Tcmb);
extern float TFfit_onek(float k, float *tf_baryon, float *tf_cdm); 

// extern float TFsound_horizon_fit(float omega0, float f_baryon, float hubble);
// extern float TFk_peak(float omega0, float f_baryon, float hubble);

extern float TFnowiggles(float omega0, float f_baryon, float hubble, 
                                float Tcmb, float k_hmpc);
extern float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc);

void TFfit_onek_wrap(float k){
    float tf_baryon, tf_cdm, tf_full;
    tf_full = TFfit_onek(k, &tf_baryon, &tf_cdm);
        /* return tf_full, tf_baryon, tf_cdm */
    MLPutReal32(stdlink, tf_full);
    MLPutReal32(stdlink, tf_baryon);
    MLPutReal32(stdlink, tf_cdm);
}

void TFset_parameters_wrap(float omega0hh, float f_baryon, float Tcmb){
    TFset_parameters(omega0hh, f_baryon, Tcmb);
    MLPutInteger(stdlink, 0); /* We need to return *something* */
}


/* CosmicEmulator version 1.1 */



/* Halofit+ */
/* `real` was defined as double in smith2.h */


void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    setparameters_(&OMEGAM, &OMEGAV, &GAMMA, &SIGMA8, &NSPEC, &BETAP, &Z0, &NONLINEAR);
    MLPutInteger(stdlink, 0); /* We need to return *something* */
}


void HFget_PkNL(real a, real k){
    MLPutReal64(stdlink, P_NL(a, k));
}

void HFget_kappa(real ell){
    MLPutReal64(stdlink, Pkappa(ell));
}

/* CAMB */

// may need a wrapper here


int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
