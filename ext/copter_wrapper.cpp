#include <cstdlib>

#include <Copter/Cosmology.h>
#include <Copter/LinearPS.h>
#include <Copter/RPT.h>
#include <Copter/SPT.h>
#include <Copter/FlowingWithTime.h>

extern "C" void copter(int argc, char* argv[]);

void copter(int argc, char* argv[]) {
    if(argc < 3)
        error("Usage: %s cosmology z [z_i Neta kcut Nk kmin kmax]\n", argv[0]);

    const char* cosmology = argv[1];
    int PT = 0;
    real z_i = (argc >= 4) ? atof(argv[3]) : 100;
    int Neta = (argc >= 5) ? atoi(argv[4]) : 50;
    real kcut = (argc >= 6) ? atof(argv[5]) : 10;
    int Nk = (argc >= 7) ? atoi(argv[6]) : 500;
    real kmin = (argc >= 8) ? atof(argv[7]) : 1e-3;
    real kmax = (argc >= 9) ? atof(argv[8]) : 0.5;

    Cosmology C(cosmology);

    if (PT == 0){
        /* RPT */
        real z = atof(argv[2]);
        LinearPS P_i(C, z_i);
        RPT rpt(C, P_i, z_i, z, Neta, 1000, kcut);
        for(int i = 0; i < Nk; i++) {
            real k = kmin * exp(i*log(kmax/kmin)/(Nk-1));
            // fprintf(fp, "%e %e %e %e\n", k, rpt.P1(k, 1,1) + rpt.P2(k, 1,1),
            //                                rpt.P1(k, 1,2) + rpt.P2(k, 1,2),
            //                                rpt.P1(k, 2,2) + rpt.P2(k, 2,2));
        }
    } else
    if (PT == 1){
        real z = atof(argv[2]);
        /* SPT */
        real epsrel = 1e-4;
        LinearPS P_L(C, z);
        SPT spt(C, P_L, epsrel);
        real p11, p12, p22;
        for(int i = 0; i < Nk; i++) {
            real k = kmin * exp(i*log(kmax/kmin)/(Nk-1));
            p11 = spt.P(k, 1,1);    // density-density power spectrum
            p12 = spt.P(k, 1,2);    // density-velocity cross spectrum
            p22 = spt.P(k, 2,2);    // velocity-velocity power spectrum
            // printf("%d/%d: %e %e %e %e\n", i+1, Nk, k, p11, p12, p22);
            // fprintf(fp, "%e %e %e %e\n", k, p11, p12, p22);
        }
    } else
    if (PT == 2){
        /* FWT */
        const int Nz = 2;                   // number of redshift outputs
        const real z[Nz] = { 0, 1 };
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

}
