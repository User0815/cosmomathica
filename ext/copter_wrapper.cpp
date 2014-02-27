#include <Copter/Cosmology.h>
#include <Copter/LinearPS.h>
#include <Copter/RPT.h>
#include <Copter/SPT.h>
#include <Copter/FlowingWithTime.h>
#include <Copter/LagrangianResummation.h>
#include <Copter/LargeN.h>
#include <Copter/HigherSPT.h>
#include <Copter/NoWigglePS.h>
#include <Copter/GrowthFunction.h>

extern "C" void copter_rpt(real h, real ns, real OmegaM, real OmegaB, real sigma8,
        real z_ini, real z_fin, int Neta, real kcut,
        int Nk, const real* karray, const real* Ti, real* result) {

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_i(C, z_ini);
    RPT rpt(C, P_i, z_ini, z_fin, Neta, 1000, kcut);

    for(int i = 0; i < Nk; i++) {
        real k = karray[i];
        result[3*i] = rpt.P1(k, 1,1) + rpt.P2(k, 1,1);
        result[3*i+1] = rpt.P1(k, 1,2) + rpt.P2(k, 1,2);
        result[3*i+2] = rpt.P1(k, 2,2) + rpt.P2(k, 2,2);
    }
}


extern "C" void copter_spt(real h, real ns, real OmegaM, real OmegaB, real sigma8,
        real z, real epsrel /*=1e-4*/, 
        int Nk, const real* karray, const real* Ti, real* result) {

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_L(C, z);
    SPT spt(C, P_L, epsrel);

    for(int i = 0; i < Nk; i++) {
        real k = v_k[i];
        result[4*i] = spt.P(k, 1,1);    // density-density power spectrum
        result[4*i+1] = spt.P(k, 1,2);    // density-velocity cross spectrum
        result[4*i+2] = spt.P(k, 2,2);    // velocity-velocity power spectrum
        result[4*i+3] = spt.G(k);  
    }
}

int fwt_test() {
    const char* cstr = "example";       // cosmology
    const real z_i = 100;               // starting redshift
    const int Nk = 100;                 // number of points in interpolated power spectrum
    const real kmin = 1e-3;
    const real kmax = 10;
    const int Nz = 2;                   // number of redshift outputs
    const real z[Nz] = { 0, 1 };
    Cosmology C(cstr);
    LinearPS P_i(C, z_i);
    array k(Nk);
    for(int i = 0; i < Nk; i++)
        k[i] = kmin*exp(i*log(kmax/kmin)/(Nk-1));
    FlowingWithTime fwt(C, z_i, P_i, k);
    vector<InterpolatedP_ab> P = fwt.CalculateP_ab(Nz, z);
    return 0;
}

extern "C" void copter_fwt(real _h, real _ns, real _OmegaM, real _OmegaB, real _sigma8,
        real z_ini, int Nz, const real* z_fin,
        int Nk, const real* karray, const real* Ti, real* result) {

    // fwt_test();

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(_h, _ns, _OmegaM, _OmegaB, _sigma8, v_k, v_Ti);
    LinearPS P_i(C, z_ini);
    FlowingWithTime fwt(C, z_ini, P_i, v_k);

    /* Calculate power spectrum */
    vector<InterpolatedP_ab> P = fwt.CalculateP_ab(Nz, z_fin);

    for(int j = 0; j < Nz; j++){
        for(int i = 0; i < Nk; i++) {
            result[Nz*j*3*Nk + 3*i] = P[j](1,1, karray[i]);
            result[Nz*j*3*Nk + 3*i + 1] = P[j](1,2, karray[i]);
            result[Nz*j*3*Nk + 3*i + 2] = P[j](2,2, karray[i]);
        }
    }
}


extern "C" void copter_lpt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real epsrel,
        int Nk, const real* karray, const real* Ti, real* result){

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LagrangianResummation lpt(C, z, epsrel);
    for(int i = 0; i < Nk; i++) {
        real k = karray[i];
        result[4*i] = lpt.P(k);
        result[4*i+1] = lpt.P22(k);
        result[4*i+2] = lpt.P13(k);
        result[4*i+3] = lpt.G(k);
    }

}


extern "C" void copter_largen(real h, real ns, real OmegaM, real OmegaB, real sigma8,
        real z_ini, real z_fin, int Neta, real epsrel,
        int Nk, const real* karray, const real* Ti, real* result) {

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_L(C, z_fin);
    LargeN largen(C, P_L, z_fin, z_ini, Neta, epsrel);

    for(int i = 0; i < Nk; i++) {
        real k = karray[i];
        result[7*i] = largen.Pi_11(k);    // density-density power spectrum
        result[7*i+1] = largen.Pi_12(k);    // density-velocity cross spectrum
        result[7*i+2] = largen.Pi_22(k);    // velocity-velocity power spectrum
        result[7*i+3] = largen.Sigma_11(k);
        result[7*i+4] = largen.Sigma_12(k);
        result[7*i+5] = largen.Sigma_21(k);
        result[7*i+6] = largen.Sigma_22(k);
    }
}


extern "C" void copter_hspt(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, real qmin, real qmax, int order,
        int Nk, const real* karray, const real* Ti, real* result){

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_L(C, z);
    HigherSPT hspt(P_L, qmin, qmax, order);

    for(int i = 0; i < Nk; i++) {
        real k = karray[i];
        result[4*i] = hspt.P(k);
        result[4*i+1] = hspt.P1(k);
        result[4*i+2] = hspt.P2(k);
        result[4*i+3] = hspt.P3(k);
    }
}

extern "C" void copter_nw(real h, real ns, real OmegaM, real OmegaB,  real sigma8,
        real z, int formula,
        int Nk, const real* karray, const real* Ti, real* result){

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_L(C, z);
    NoWigglePS nw(C, z, formula);

    for(int i = 0; i < Nk; i++) {
        result[i] = nw.Evaluate(karray[i]);
    }
}


extern "C" void copter_lin(real h, real ns, real OmegaM, real OmegaB,  real sigma8, 
        real z,
        int Nk, const real* karray, const real* Ti, real* result){

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
    LinearPS P_L(C, z);

    for(int i = 0; i < Nk; i++) {
        result[i] = P_L.Evaluate(karray[i]);
    }
}

extern "C" void copter_growth(real h, real ns, real OmegaM, real OmegaB,
        int Nz, const real *z, real* result){

    Cosmology C(h, ns, OmegaM, OmegaB);
    GrowthFunction D(C);

    for (int i=0; i < Nz;  i++){
        result[i] = D(z[i]);
    }
}
