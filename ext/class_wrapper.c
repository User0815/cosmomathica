/* This wrapper exists because otherwise we have colliding variable
 * definitions */

#include "class.h"

int pass_error(char **e1, char **e2, char *s1, char *s2) {\
        strcpy(*e1,s1);\
        strcpy(*e2,s2);\
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
        return pass_error(&e1,&e2,"Error running input_init_from_arguments", errmsg);
    }

    if (background_init(&pr,&ba) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error running background_init",ba.error_message);
    }

    if (thermodynamics_init(&pr,&ba,&th) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in thermodynamics_init",th.error_message);
    }

    if (perturb_init(&pr,&ba,&th,&pt) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in perturb_init",pt.error_message);
    }

    if (primordial_init(&pr,&pt,&pm) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in primordial_init",pm.error_message);
    }

    if (nonlinear_init(&pr,&ba,&th,&pt,&pm,&nl) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in nonlinear_init",nl.error_message);
    }

    if (transfer_init(&pr,&ba,&th,&pt,&nl,&tr) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in transfer_init",tr.error_message);
    }

    if (spectra_init(&pr,&ba,&pt,&pm,&nl,&tr,&sp) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in spectra_init",sp.error_message);
    }

    if (lensing_init(&pr,&pt,&sp,&nl,&le) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in lensing_init",le.error_message);
    }

    return 0;
}

typedef struct {
    double *buffer;
    int *limits;
    int id, size, count;
} return_value;

void add_to_buffer(return_value *result, double *data, int len, int *i) { 
    if (result->count+len < result->size && data != NULL) {
        memcpy(result->buffer+result->count, data, len*sizeof(double));
        result->count += len;
        (result->limits)[*i] = -result->id;
        (result->limits)[*i+1] = len;
        (*i)+=2;
    }
    (result->id)++;
}
    
double* class_get(int **limits){
    /* Everything initialized, pack results in an array */

    int i, j;
    return_value result;
    result.id = 1;
    result.size = 20000;
    result.count = 0;
    result.buffer = malloc(result.size*sizeof(result.buffer));
    result.limits = malloc(1024*sizeof(result.limits));
    for (j=0; j<1024; j++) (result.limits)[j] = 0;
    i = 0;

    /* order is important */

    add_to_buffer(&result, sp.ln_k, sp.ln_k_size, &i);
    add_to_buffer(&result, sp.ln_tau, sp.ln_tau_size, &i);
    add_to_buffer(&result, &sp.sigma8, 1, &i);

    add_to_buffer(&result, 
                /* only for today, i.e. the last tau value */
            sp.matter_transfer + 
                    (sp.ln_tau_size - 1) * sp.ln_k_size * sp.tr_size * sp.ic_size[0],
            sp.ln_k_size * sp.tr_size * sp.ic_size[0],
            &i);
   

    add_to_buffer(&result, sp.ln_pk, sp.ln_k_size * sp.ln_tau_size, &i);
    add_to_buffer(&result, sp.ln_pk_nl, sp.ln_k_size * sp.ln_tau_size, &i);


    double backg[2];
    backg[0] = ba.h;
    backg[1] = ba.age;
    add_to_buffer(&result, backg, sizeof(backg)/sizeof(backg[0]) , &i);

    /* TODO multipoles */
    *limits = result.limits;
    return result.buffer;
}

int class_free(char *e1, char *e2){

    /* Done, free everything */

    if (lensing_free(&le) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in lensing_free",le.error_message);
    }

    if (spectra_free(&sp) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in spectra_free",sp.error_message);
    }

    if (transfer_free(&tr) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in transfer_free",tr.error_message);
    }

    if (nonlinear_free(&nl) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in nonlinear_free",nl.error_message);
    }

    if (primordial_free(&pm) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in primordial_free",pm.error_message);
    }

    if (perturb_free(&pt) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in perturb_free",pt.error_message);
    }

    if (thermodynamics_free(&th) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in thermodynamics_free",th.error_message);
    }

    if (background_free(&ba) == _FAILURE_) {
      return pass_error(&e1,&e2,"Error in background_free",ba.error_message);
    }

    return 0;
}

