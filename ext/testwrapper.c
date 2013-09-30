#include<stdio.h>
#include<stdlib.h>

extern void runcamb(double *floats, 
        int *floats_len, 
        int *ints, 
        int *ints_len, 
        double *out, 
        int *out_len);


int main(){
    int floats_len = 10, ints_len = 10, out_len = 10;
    double floats[floats_len];
    int ints[ints_len];
    double out[out_len];

    runcamb((double*)floats, &floats_len, (int*)ints, &ints_len, (double*) out, &out_len);

    printf("%e\n", out[0]);

    return 0;
}
