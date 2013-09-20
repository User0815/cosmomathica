/*
 *  design.h
 *  
 *
 *  Created by Earl Lawrence on 12/14/09.
 *
 *  This program was prepared by Los Alamos National Security, LLC at Los Alamos National Laboratory (LANL) 
 *  under contract No. DE-AC52-06NA25396 with the U.S. Department of Energy (DOE). All rights in the program 
 *  are reserved by the DOE and Los Alamos National Security, LLC.  Permission is granted to the public to 
 *  copy and use this software without charge, provided that this Notice and any statement of authorship are 
 *  reproduced on all copies.  Neither the U.S. Government nor LANS makes any warranty, express or implied, 
 *  or assumes any liability or responsibility for the use of this software.
 *
 */


static double x[37][5] = 
  {9.6857142857142886e-01,   7.9999999999999960e-01,   4.8399999999999982e-01,   7.0457746478873251e-01,   8.0649999999999988e-01,
   7.4285714285714266e-01,   6.0000000000000109e-01,   2.2600000000000001e-01,   8.4084507042253520e-01,   9.0316666666666656e-01,
   3.5428571428571409e-01,   1.0000000000000000e+00,   7.4199999999999966e-01,   8.1830985915492971e-01,   7.0966666666666667e-01,
   5.1714285714285724e-01,   6.0000000000000109e-01,   4.1949999999999971e-01,   2.9577464788732377e-01,   3.5483333333333344e-01,
   4.5142857142857162e-01,   5.0000000000001391e-02,   6.1299999999999999e-01,   7.2746478873239429e-01,   9.6833333333333382e-02,
   9.0285714285714325e-01,   7.0000000000000040e-01,   3.2249999999999990e-01,   1.9190140845070419e-01,   1.2900000000000020e-01,
   1.9428571428571428e-01,   4.0000000000000069e-01,   3.5500000000000020e-01,   4.6267605633802800e-01,   1.0000000000000000e+00,
   7.0857142857142896e-01,   4.0000000000000069e-01,   6.7750000000000010e-01,   6.7957746478873249e-01,   1.6133333333333330e-01,
   5.4857142857142838e-01,   9.5000000000000040e-01,   6.4499999999999980e-01,   1.8732394366197189e-01,   9.3549999999999989e-01,
   5.8000000000000029e-01,   1.5000000000000069e-01,   3.2500000000000293e-02,   4.9154929577464801e-01,   5.1616666666666677e-01,
   6.7714285714285705e-01,   9.5000000000000040e-01,   1.6149999999999992e-01,   3.9295774647887333e-01,   2.9033333333333350e-01,
   6.5714285714286003e-02,   5.0000000000000000e-01,   7.7399999999999947e-01,   3.9084507042253511e-02,   5.4833333333333334e-01,
   8.0571428571428572e-01,   3.0000000000000138e-01,   5.4849999999999988e-01,   1.2253521126760580e-01,   7.4199999999999999e-01,
   7.7428571428571458e-01,   9.0000000000000069e-01,   9.0299999999999958e-01,   3.2218309859154937e-01,   4.8383333333333328e-01,
   6.1428571428571399e-01,   7.5000000000000000e-01,   8.3850000000000002e-01,   5.1936619718309840e-01,   3.2333333333333471e-02,
   1.2857142857142867e-01,   1.5000000000000069e-01,   4.5150000000000007e-01,   4.4964788732394373e-01,   2.5800000000000006e-01,
   6.4571428571428591e-01,   0.0000000000000000e+00,   3.8700000000000001e-01,   2.4436619718309863e-01,   6.7749999999999999e-01,
   3.2285714285714295e-01,   5.0000000000001391e-02,   1.9350000000000028e-01,   9.8591549295774725e-02,   4.5166666666666683e-01,
   2.2571428571428620e-01,   8.4999999999999931e-01,   6.4500000000000085e-02,   0.0000000000000000e+00,   1.9350000000000012e-01,
   2.5714285714285734e-01,   2.5000000000000000e-01,   8.7099999999999977e-01,   6.3802816901408455e-01,   8.3866666666666667e-01,
   3.8571428571428601e-01,   3.0000000000000138e-01,   9.3549999999999933e-01,   1.4190140845070423e-01,   2.2583333333333322e-01,
   8.7142857142857133e-01,   5.0000000000000000e-01,   1.0000000000000000e+00,   5.3450704225352119e-01,   3.2249999999999995e-01,
   3.1428571428571535e-02,   2.5000000000000000e-01,   2.5799999999999979e-01,   1.7746478873239435e-01,   6.4499999999999919e-02,
   2.9142857142857181e-01,   5.4999999999999960e-01,   5.1600000000000013e-01,   1.7042253521126757e-01,   0.0000000000000000e+00,
   8.4000000000000019e-01,   1.0000000000000105e-01,   8.0650000000000033e-01,   4.3591549295774651e-01,   9.6766666666666656e-01,
   4.1999999999999971e-01,   8.4999999999999931e-01,   2.9050000000000009e-01,   6.4612676056338025e-01,   5.8066666666666666e-01,
   4.8285714285714276e-01,   4.5000000000000034e-01,   0.0000000000000000e+00,   3.3485915492957730e-01,   7.7416666666666656e-01,
   9.3428571428571439e-01,   3.5000000000000103e-01,   9.6999999999999836e-02,   6.7183098591549273e-01,   6.1283333333333334e-01,
   1.5999999999999981e-01,   6.5000000000000069e-01,   9.6750000000000025e-01,   3.2640845070422536e-01,   6.4516666666666656e-01,
   9.7142857142857142e-02,   7.5000000000000000e-01,   1.2900000000000017e-01,   2.0387323943661992e-01,   8.7100000000000000e-01,
   1.0000000000000000e+00,   2.0000000000000034e-01,   7.0949999999999991e-01,   3.1021126760563361e-01,   3.8716666666666655e-01,
   0.0000000000000000e+00,   7.0000000000000040e-01,   5.8049999999999968e-01,   4.9154929577464801e-01,   4.1933333333333334e-01,
   5.6717142857142877e-01,   5.1611999999999969e-01,   9.5369999999999977e-01,   8.7500000000000011e-01,   2.5500000000000000e-01,
   8.4891999999999979e-01,   6.2223000000000084e-01,   3.6957500000000021e-01,   9.0625000000000000e-01,   5.0000000000000000e-01,
   8.1319142857142868e-01,   2.8733000000000031e-01,   5.5224699999999993e-01,   9.3749999999999989e-01,   7.4500000000000000e-01,
   4.5594285714285948e-02,   9.1685999999999945e-01,   4.4333649999999986e-01,   9.6874999999999978e-01,   9.8999999999999999e-01,
   8.4371428571428564e-01,   6.2737500000000068e-01,   8.6634999999999929e-01,   1.0000000000000000e+00,   1.0000000000000007e-02};

static double xmin[5] = 
  {1.2000000000000000e-01,   2.1499999999999998e-02,   8.4999999999999998e-01,   6.1599999999999999e-01,  -1.3000000000000000e+00};

static double xrange[5] = 
  {3.5000000000000003e-02,   2.0000000000000018e-03,   2.0000000000000007e-01,   2.8400000000000003e-01,   6.0000000000000009e-01};

static double aemu[6] = 
  {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
