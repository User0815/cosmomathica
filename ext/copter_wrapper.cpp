#include <Copter/Cosmology.h>
#include <Copter/LinearPS.h>
#include <Copter/RPT.h>
#include <Copter/SPT.h>
#include <Copter/FlowingWithTime.h>
#include <Copter/LagrangianResummation.h>
#include <Copter/LargeN.h>
#include <Copter/HigherSPT.h>

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


extern "C" void copter_fwt(real h, real ns, real OmegaM, real OmegaB, real sigma8,
        real z_ini, int Nz, const real* z_fin,
        int Nk, const real* karray, const real* Ti, real* result) {

    std::vector<real> v_k(karray, karray + Nk);
    std::vector<real> v_Ti(Ti, Ti + Nk);

    Cosmology C(h, ns, OmegaM, OmegaB, sigma8, v_k, v_Ti);
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
