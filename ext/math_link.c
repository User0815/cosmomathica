#include <stdio.h>
#include <stdlib.h>
#include "mathlink.h"

/* Halofit+ */
/* `real` was defined as double in smith2.h */

#ifdef HALOFIT

#include "halofit/smith2.h"

void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    setparameters_(&OMEGAM, &OMEGAV, &GAMMA, &SIGMA8, &NSPEC, &BETAP, &Z0, &NONLINEAR);
     /* We need to return *something* */
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}

#else

#define real double
void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}
real P_NL(real a, real k){return 0.;}
real Pkappa(real ell){return 0.;}

#endif


#ifdef TRANSFER

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

#else
void TFfit_onek_wrap(float k){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}
void TFset_parameters_wrap(float omega0hh, float f_baryon, float Tcmb){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}
float TFnowiggles(float omega0, float f_baryon, float hubble, float Tcmb, float k_hmpc){return 0.;}
float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc){return 0.;}
float TFsound_horizon_fit(float omega0, float f_baryon, float hubble){return 0.;}
float TFk_peak(float omega0, float f_baryon, float hubble){return 0.;}
#endif


/* CosmicEmulator version 1.1 */

#ifdef COSMICEMU
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
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}

#else
void emu(double *xstar, double *ystar, int *outtype){}
void getH0fromCMB(double *xstar, double *stuff){}
void CEget_PkNL(double omegaM, double omegaB, double ns, double sigma8, double w, double z ){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}
#endif


/* CAMB */

#ifdef CAMB
extern void runcamb();

void CAMBrun(double *floats, long floats_len, int *ints, long ints_len){
    /* TODO Do longs need to be converted to ints here? */

    const int floats_out_len = 2000000;
    double *floats_out = malloc(sizeof(*floats_out) * floats_out_len);
    const int ints_out_len = 100;
    double ints_out[ints_out_len];

    runcamb(floats, &floats_len, ints, &ints_len, (double*)floats_out, &floats_out_len, (int*)ints_out, &ints_out_len);

    MLPutFunction(stdlink, "List", 2);
    MLPutReal64List(stdlink, (double*)floats_out, floats_out_len);
    MLPutIntegerList(stdlink, (int*)ints_out, ints_out_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(floats_out);
}

#else

void runcamb(){}
void CAMBrun(double *floats, long floats_len, int *ints, long ints_len){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}

#endif


/* Copter */

#ifdef COPTER
extern void copter_rpt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax);
extern void copter_spt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax);
extern void copter_fwt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax);


#else

void copter_rpt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax){}
void copter_spt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax){}
void copter_fwt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax){}

#endif



int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
