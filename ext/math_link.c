#include <stdio.h>
#include "mathlink.h"

#include "halofit/smith2.h"



/* TF Transfer function from Eisenstein&hu */

extern void TFset_parameters(float omega0hh, float f_baryon, float Tcmb);
extern float TFfit_onek(float k, float *tf_baryon, float *tf_cdm); 
extern float TFnowiggles(float omega0, float f_baryon, float hubble, 
                                float Tcmb, float k_hmpc);
extern float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc);
extern float TFsound_horizon_fit(float omega0, float f_baryon, float hubble);
extern float TFk_peak(float omega0, float f_baryon, float hubble);

void TFfit_onek_wrap(float k){
    float tf_baryon, tf_cdm, tf_full;
    tf_full = TFfit_onek(k, &tf_baryon, &tf_cdm);
        /* return tf_full, tf_baryon, tf_cdm */
    MLPutFunction(stdlink, "List", 3);
    MLPutReal32(stdlink, tf_full);
    MLPutReal32(stdlink, tf_baryon);
    MLPutReal32(stdlink, tf_cdm);
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}

void TFset_parameters_wrap(float omega0hh, float f_baryon, float Tcmb){
    TFset_parameters(omega0hh, f_baryon, Tcmb);
     /* We need to return *something* */
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}



/* CosmicEmulator version 1.1 */

extern void emu(double *xstar, double *ystar, int *outtype);
extern void getH0fromCMB(double *xstar, double *stuff);

void CEget_PkNL(double omegaM, double omegaB, double ns, double sigma8, double w, double z ){
    const int output_length = 2*1995;
    double input[6], output[output_length], more_output[4];
    int type=2; // Output: P(k)

    input[0] = omegaM;
    input[1] = omegaB;
    input[2] = ns;
    input[3] = sigma8;
    input[4] = w;
    input[5] = z;

    getH0fromCMB(input, more_output);
    emu(input, output, &type);


    MLPutFunction(stdlink, "List", 2);
    MLPutReal64List(stdlink, (double*)output, output_length);
    MLPutReal64List(stdlink, (double*)more_output, 4);
    // MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}



/* Halofit+ */
/* `real` was defined as double in smith2.h */


void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    setparameters_(&OMEGAM, &OMEGAV, &GAMMA, &SIGMA8, &NSPEC, &BETAP, &Z0, &NONLINEAR);
     /* We need to return *something* */
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}


/* CAMB */

extern void runcamb();


void CAMBrun(double *floats, long floats_len, int *ints, long ints_len){
    double *out;
    int i;

    runcamb(floats, floats_len, ints, ints_len, out);
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}


int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
