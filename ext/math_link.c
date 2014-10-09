#include <stdio.h>
#include <stdlib.h>
#include "mathlink.h"


#define return_null()  {\
    MLPutSymbol(stdlink, "Null"); \
    MLEndPacket(stdlink); \
    MLFlush(stdlink); \
    return;\
}

/* Halofit+ */
/* `real` was defined as double in smith2.h */

#ifdef HALOFIT

#include "halofit/smith2.h"

void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    setparameters_(&OMEGAM, &OMEGAV, &GAMMA, &SIGMA8, &NSPEC, &BETAP, &Z0, &NONLINEAR);
     return_null();
}

#else

#define real double
void HFset_parameters(real OMEGAM, real OMEGAV, real GAMMA, real SIGMA8,
		   real NSPEC, real BETAP, real Z0, int NONLINEAR){
    MLPutSymbol(stdlink, "Null");
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}
extern real P_NL(real a, real k);
extern real Pkappa(real ell);

#endif /*HALOFIT*/


#ifdef TRANSFER

/* TF Transfer function from Eisenstein&hu */

/* high baryon version */
extern void TFset_parameters(float omega0hh, float f_baryon, float Tcmb);
extern float TFfit_onek(float k, float *tf_baryon, float *tf_cdm); 
extern float TFnowiggles(float omega0, float f_baryon, float hubble, 
                                float Tcmb, float k_hmpc);
extern float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc);
extern float TFsound_horizon_fit(float omega0, float f_baryon, float hubble);
extern float TFk_peak(float omega0, float f_baryon, float hubble);

/* other version */
extern int TFmdm_set_cosm(float omega_matter, float omega_baryon, float omega_hdm,
	int degen_hdm, float omega_lambda, float hubble, float redshift);
extern float TFmdm_onek_hmpc(float kk);


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
    return_null();
}
void TFset_parameters_wrap(float omega0hh, float f_baryon, float Tcmb){
    return_null();
}
extern float TFnowiggles(float omega0, float f_baryon, float hubble, float Tcmb, float k_hmpc);
extern float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc);
extern float TFsound_horizon_fit(float omega0, float f_baryon, float hubble);
extern float TFk_peak(float omega0, float f_baryon, float hubble);
extern int TFmdm_set_cosm(float omega_matter, float omega_baryon, float omega_hdm,
	int degen_hdm, float omega_lambda, float hubble, float redshift);
extern float TFmdm_onek_hmpc(float kk);

#endif /*TRANSFER*/


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
void CEget_PkNL(double omegaM, double omegaB, double ns, double sigma8, double w, double z ){
    return_null();
}
#endif /*COSMICEMU*/


/* FrankenEmu */

#ifdef FRANKENEMU

extern void emu(double *xstar, double *ystar, int *outtype);
extern void emu_noh(double *xstar, double *ystar, int *outtype);
extern void getH0fromCMB(double *xstar, double *stuff);

void franken_CEget_PkNL(double omegaM, double omegaB, double h, double ns, double sigma8, double w, double z ){
    const int output_length = 2*582;
    double input[7], output[output_length], more_output[4];
    int type=2; // Output: P(k)


    if (h>0) {
        input[0] = omegaB;
        input[1] = omegaM;
        input[2] = ns;
        input[3] = h*100;
        input[4] = w;
        input[5] = sigma8;
        input[6] = z;
        emu(input, output, &type);
    } else {
        input[0] = omegaB;
        input[1] = omegaM;
        input[2] = ns;
        input[3] = w;
        input[4] = sigma8;
        input[5] = z;
        emu_noh(input, output, &type);
        getH0fromCMB(input, more_output);
    }


    MLPutFunction(stdlink, "List", 2);
    MLPutReal64List(stdlink, (double*)output, output_length);
    MLPutReal64List(stdlink, (double*)more_output, 4);
    MLEndPacket(stdlink);
    MLFlush(stdlink);
}

/* Dummy functions need to be defined, but will never be called anyway
 * because FrankenEmu is alone in this module */
double P_NL(double a, double k){return 0;}
double Pkappa(double ell){return 0;}
float TFnowiggles(float omega0, float f_baryon, float hubble, float Tcmb, float k_hmpc){return 0.;}
float TFzerobaryon(float omega0, float hubble, float Tcmb, float k_hmpc){return 0.;}
float TFsound_horizon_fit(float omega0, float f_baryon, float hubble){return 0.;}
float TFk_peak(float omega0, float f_baryon, float hubble){return 0.;}

int TFmdm_set_cosm(float omega_matter, float omega_baryon, float omega_hdm,
	int degen_hdm, float omega_lambda, float hubble, float redshift){return 0;}
float TFmdm_onek_hmpc(float kk){return 0.;}

#else

void franken_CEget_PkNL(double omegaM, double omegaB, double ns, double sigma8, double w, double z ){
    return_null();
}

#endif /*FrankenEmu*/



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

// void runcamb(){}
void CAMBrun(double *floats, long floats_len, int *ints, long ints_len){
    return_null();
}

#endif /*CAMB*/


/* Copter */

#ifdef COPTER
extern void copter_rpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z_ini, real z_fin, int Neta, real kcut,
           int Nk, const real* k, const real* Ti, real* result);

void MLcopterRpt(real OmegaM, real OmegaB, real h, real ns, real sigma8,
           real zini, real zfin, int Neta, real kcut,
           double *k, long k_len, double *Ti, long Ti_len){

    double *result = malloc(sizeof *k * 3*k_len);
    copter_rpt(h, ns, OmegaM, OmegaB,  sigma8,
           zini, zfin, Neta, kcut, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 3*k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}

extern void copter_spt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z, real epsrel /*=1e-4*/, 
           int Nk, const real* karray, const real* Ti, real* result);

void MLcopterSpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z, real epsrel /*=1e-4*/, 
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * 4*k_len);
    copter_spt(h, ns, OmegaM, OmegaB,  sigma8,
           z, epsrel /*=1e-4*/, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 4*k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}


extern void copter_fwt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z_ini, int Nz, const real* z_fin,
           int Nk, const real* karray, const real* Ti, real* result);

void MLcopterFWT(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real zini, real* zfin, long zfin_len,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * 3*k_len*zfin_len);
    copter_fwt(h, ns, OmegaM, OmegaB,  sigma8,
           zini, zfin_len, zfin, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 3*k_len*zfin_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}


extern void copter_lpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real epsrel,
        int Nk, const real* karray, const real* Ti, real* result);

void MLcopterLpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z, real epsrel,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * 4*k_len);
    copter_lpt(h, ns, OmegaM, OmegaB,  sigma8,
           z, epsrel, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 4*k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}


extern void copter_largen(real h, real ns, real OmegaM, real OmegaB, real sigma8,
        real z_ini, real z_fin, int Neta, real epsrel,
        int Nk, const real* karray, const real* Ti, real* result);

void MLcopterLargeN(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z_ini, real z_fin, int Neta, real epsrel,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * 7*k_len);
    copter_largen(h, ns, OmegaM, OmegaB,  sigma8,
           z_ini, z_fin, Neta, epsrel, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 7*k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}


extern void copter_hspt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real qmin, real qmax, int order,
        int Nk, const real* karray, const real* Ti, real* result);

void MLcopterHspt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real qmin, real qmax, int order,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * 4*k_len);
    copter_hspt(h, ns, OmegaM, OmegaB,  sigma8,
           z, qmin, qmax, order, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, 4*k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}


extern void copter_nw(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, int formula,
        int Nk, const real* karray, const real* Ti, real* result);

void MLcopterNW(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, int formula,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * k_len);
    copter_nw(h, ns, OmegaM, OmegaB,  sigma8,
           z, formula, k_len, k, Ti, result);

    MLPutReal64List(stdlink, result, k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}

extern void copter_lin(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z,
        int Nk, const real* karray, const real* Ti, real* result);

void MLcopterLinear(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z,
           real* k, long k_len, real* Ti, long Ti_len){

    double *result = malloc(sizeof *k * k_len);
    copter_lin(h, ns, OmegaM, OmegaB,  sigma8, z, k_len, k, Ti, result);

    MLPutReal64List(stdlink, (double *)result, k_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}

extern void copter_growth(real h, real ns, real OmegaM, real OmegaB,
        int Nz, const real *zarray, real* result);

void MLcopterGrowth(real h, real ns, real OmegaM, real OmegaB,
       real *z, long z_len){

    double *result = malloc(sizeof *z * z_len);
    copter_growth(h, ns, OmegaM, OmegaB, z_len, z, result);

    MLPutReal64List(stdlink, (double *)result, z_len);
    MLEndPacket(stdlink);
    MLFlush(stdlink);

    free(result);
}
#else

void MLcopterRpt(real OmegaM, real OmegaB, real h, real ns, real sigma8,
           real zini, real zfin, int Neta, real kcut,
           double *k, long k_len, double *Ti, long Ti_len){
    return_null();
}

void MLcopterSpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z, real epsrel /*=1e-4*/, 
           real* k, long k_len, real* Ti, long Ti_len){
    return_null();
}


void MLcopterFWT(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real zini, real *zfin, long zfin_len,
           real* k, long k_len, real* Ti, long Ti_len){
    return_null();
}

void MLcopterLpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
           real z, real epsrel,
           real* k, long k_len, real* Ti, long Ti_len){

    return_null();
}


void MLcopterLargeN(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z_ini, real z_fin, int Neta, real epsrel,
           real* k, long k_len, real* Ti, long Ti_len){

    return_null();
}


void MLcopterHspt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real qmin, real qmax, int order,
           real* k, long k_len, real* Ti, long Ti_len){

    return_null();
}

void MLcopterNW(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, int formula,
           real* k, long k_len, real* Ti, long Ti_len){

    return_null();
}

void MLcopterLinear(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, 
           real* k, long k_len, real* Ti, long Ti_len){

    return_null();
}

void MLcopterGrowth(real h, real ns, real OmegaM, real OmegaB,
        int Nz, const real *zarray, real* result){
    return_null();
}
#endif /*Copter*/


#ifdef CLASS

extern int class_init(int, char**, char*, char*);
extern double* class_get(int **);
extern int class_free(char*, char*);
    
void MLClass(char *inifile){
    double *result;
    int *limits;
    int i, size = 0;
    char e1[2048], e2[2048];
    char (*argv[2])[1024];
    int fail;
    

    fail = 0;
    argv[0] = "class";
    argv[1] = inifile;
    printf("%s\n", inifile);

    
    if (class_init(2, (char **)argv, e1, e2)==0){
        result = class_get(&limits);
        for (i=1; i<1024; i+=2) size += limits[i];
        MLPutFunction(stdlink,"List", 2);
        MLPutIntegerList(stdlink, limits, 1024);
        MLPutReal64List(stdlink, result, size);
        MLEndPacket(stdlink);
        MLFlush(stdlink);
        free(result);
        free(limits);
    }
    else fail = 1;

    if (fail==1 || class_free(e1, e2)!=0) fail = 1;

    if (fail==1) {
        printf("%s\n%s\n", e1, e2);
        MLPutFunction(stdlink,"List", 2);
        MLPutString(stdlink, e1);
        MLPutString(stdlink, e2);
        MLEndPacket(stdlink);
        MLFlush(stdlink);
    }

}

#else

void MLClass(int argc, char *argv){
    return_null();
}

#endif /*CLASS*/

int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
