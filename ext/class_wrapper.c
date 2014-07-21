/* This wrapper exists because otherwise we have colliding variable
 * definitions */

#include "class.h"

#define MLError(s1,s2) {\
        strcpy(e1,s1);\
        strcpy(e2,s2);\
        return 1;\
}
    

    struct precision pr;        /* for precision parameters */
    struct background ba;       /* for cosmological background */
    struct thermo th;           /* for thermodynamics */
    struct perturbs pt;         /* for source functions */
    struct transfers tr;        /* for transfer functions */
    struct primordial pm;       /* for primordial spectra */
    struct spectra sp;          /* for output spectra */
    struct nonlinear nl;        /* for non-linear spectra */
    struct lensing le;          /* for lensed spectra */
    struct output op;           /* for output files */
    ErrorMsg errmsg;            /* for error messages */

int class_init(int argc, char **argv, char *e1, char *e2){

    /* pass the temporary ini file to Class */


    if (input_init_from_arguments(argc,argv,&pr,&ba,&th,&pt,&tr,&pm,&sp,&nl,&le,&op,errmsg) == _FAILURE_) {
        MLError("Error running input_init_from_arguments", errmsg);
    }

    if (background_init(&pr,&ba) == _FAILURE_) {
      MLError("Error running background_init",ba.error_message);
    }

    if (thermodynamics_init(&pr,&ba,&th) == _FAILURE_) {
      MLError("Error in thermodynamics_init",th.error_message);
    }

    if (perturb_init(&pr,&ba,&th,&pt) == _FAILURE_) {
      MLError("Error in perturb_init",pt.error_message);
    }

    if (primordial_init(&pr,&pt,&pm) == _FAILURE_) {
      MLError("Error in primordial_init",pm.error_message);
    }

    if (nonlinear_init(&pr,&ba,&th,&pt,&pm,&nl) == _FAILURE_) {
      MLError("Error in nonlinear_init",nl.error_message);
    }

    if (transfer_init(&pr,&ba,&th,&pt,&nl,&tr) == _FAILURE_) {
      MLError("Error in transfer_init",tr.error_message);
    }

    if (spectra_init(&pr,&ba,&pt,&pm,&nl,&tr,&sp) == _FAILURE_) {
      MLError("Error in spectra_init",sp.error_message);
    }

    if (lensing_init(&pr,&pt,&sp,&nl,&le) == _FAILURE_) {
      MLError("Error in lensing_init",le.error_message);
    }

    return 0;
}

#define add_to_buffer(data, len) \
if (count+len < size) {\
    memcpy(result+count, data, len*sizeof(double));\
    count += len;\
    (*limits)[i] = -i/2-1;\
    (*limits)[i+1] = len;\
    i+=2;\
}
    
double* class_get(int **limits){
    /* Everything initialized, pack results in an array */

    int size = 10000, count = 0, i, j;
    double* result = malloc(size*sizeof(result));
    *limits = malloc(1024*sizeof(limits));
    for (i=0; i<1024; i++) (*limits)[i] = 0;
    i = 0;

    /* order is important */

    /* return transfer functions */
    add_to_buffer(sp.ln_k, sp.ln_k_size);
    add_to_buffer(sp.ln_tau, sp.ln_tau_size);
    add_to_buffer(&sp.sigma8, 1);
    for (j = 0; j < sp.md_size; j++) {
        add_to_buffer(sp.matter_transfer, 
            sp.ln_k_size * sp.ln_tau_size * sp.tr_size * sp.ic_size[j]);
    }
    for (j = 0; j < sp.md_size; j++) {
        add_to_buffer(sp.ln_pk, 
            sp.ln_k_size * sp.ln_tau_size * sp.ic_size[j] * sp.ic_ic_size[j]);
    }
    return result;
}

int class_free(char *e1, char *e2){

    /* Done, free everything */

    if (lensing_free(&le) == _FAILURE_) {
      MLError("Error in lensing_free",le.error_message);
    }

    if (spectra_free(&sp) == _FAILURE_) {
      MLError("Error in spectra_free",sp.error_message);
    }

    if (transfer_free(&tr) == _FAILURE_) {
      MLError("Error in transfer_free",tr.error_message);
    }

    if (nonlinear_free(&nl) == _FAILURE_) {
      MLError("Error in nonlinear_free",nl.error_message);
    }

    if (primordial_free(&pm) == _FAILURE_) {
      MLError("Error in primordial_free",pm.error_message);
    }

    if (perturb_free(&pt) == _FAILURE_) {
      MLError("Error in perturb_free",pt.error_message);
    }

    if (thermodynamics_free(&th) == _FAILURE_) {
      MLError("Error in thermodynamics_free",th.error_message);
    }

    if (background_free(&ba) == _FAILURE_) {
      MLError("Error in background_free",ba.error_message);
    }

    return 0;
}

