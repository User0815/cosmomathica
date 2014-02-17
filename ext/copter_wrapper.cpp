#include <Copter/Cosmology.h>
#include <Copter/LinearPS.h>
#include <Copter/RPT.h>
#include <Copter/SPT.h>
#include <Copter/FlowingWithTime.h>

extern "C" void copter_rpt(int PT, real h, real ns, real OmegaM, real OmegaB, 
        int Nk, real kmin, real kmax);
extern "C" void copter_spt(int PT, real h, real ns, real OmegaM, real OmegaB, 
        int Nk, real kmin, real kmax);
extern "C" void copter_fwt(int PT, real h, real ns, real OmegaM, real OmegaB, 
        int Nk, real kmin, real kmax);

void copter_rpt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax) {
    real z_i =  100;
    real z = 0.;
    int Neta =  50;
    real kcut =  10;

    Cosmology C(h, ns, OmegaM, OmegaB);
    LinearPS P_i(C, z_i);
    RPT rpt(C, P_i, z_i, z, Neta, 1000, kcut);

    for(int i = 0; i < Nk; i++) {
        real k = kmin * exp(i*log(kmax/kmin)/(Nk-1));
        // fprintf(fp, "%e %e %e %e\n", k, rpt.P1(k, 1,1) + rpt.P2(k, 1,1),
        //                                rpt.P1(k, 1,2) + rpt.P2(k, 1,2),
        //                                rpt.P1(k, 2,2) + rpt.P2(k, 2,2));
    }
}


void copter_spt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax) {
    real z = 0.;
    real epsrel = 1e-4;

    Cosmology C(h, ns, OmegaM, OmegaB);
    LinearPS P_L(C, z);
    SPT spt(C, P_L, epsrel);

    real p11, p12, p22;
    for(int i = 0; i < Nk; i++) {
        real k = kmin * exp(i*log(kmax/kmin)/(Nk-1));
        p11 = spt.P(k, 1,1);    // density-density power spectrum
        p12 = spt.P(k, 1,2);    // density-velocity cross spectrum
        p22 = spt.P(k, 2,2);    // velocity-velocity power spectrum
        // fprintf(fp, "%e %e %e %e\n", k, p11, p12, p22);
    }
}


void copter_fwt(int PT, real h, real ns, real OmegaM, real OmegaB,
        int Nk, real kmin, real kmax) {
    real z_i =  100;
    const int Nz = 2;                   // number of redshift outputs
    const real z[Nz] = { 0, 1 };

    Cosmology C(h, ns, OmegaM, OmegaB);
    LinearPS P_i(C, z_i);
    array k(Nk);
    for(int i = 0; i < Nk; i++)
        k[i] = kmin*exp(i*log(kmax/kmin)/(Nk-1));
    FlowingWithTime fwt(C, z_i, P_i, k);

    /* Calculate power spectrum */
    vector<InterpolatedP_ab> P = fwt.CalculateP_ab(Nz, z);

    /* Columns: k   P_11(k; z[0])   P_12(k; z[0])   P_22(k; z[0])   P_11(k; z[1]) ...\n"); */
    // for(int j = 0; j < Nz; j++)
        // fprintf(fp, " %g", z[j]);
    for(int i = 0; i < Nk; i++) {
        // fprintf(fp, "%e", k[i]);
        // for(int j = 0; j < Nz; j++)
            // fprintf(fp, "  %e %e %e", P[j](1,1, k[i]), P[j](1,2, k[i]), P[j](2,2, k[i]));
        // fprintf(fp, "\n");
    }
}
