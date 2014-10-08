
:Begin:
:Function:      TFmdm_set_cosm
:Pattern:       TFSetCosmology[OmegaM_Real, OmegaB_Real, OmegaH_Real, Degen_Integer, OmegaL_Real, Hubble_Real, Redshift_Real]
:Arguments:     {OmegaM, OmegaB, OmegaH, Degen, OmegaL, Hubble, Redshift}
:ArgumentTypes: {Real32, Real32, Real32, Integer, Real32, Real32, Real32}
:ReturnType:    Integer
:End:


:Begin:
:Function:      TFmdm_onek_mpc
:Pattern:       TFOneK[kk_Real]
:Arguments:     {kk}
:ArgumentTypes: {Real32}
:ReturnType:    Real32
:End:



:Begin:
:Function:      TFset_parameters_wrap
:Pattern:       TFSetParameters[OmegaMh2_Real, fBaryon_Real, TCMB_Real]
:Arguments:     {OmegaMh2, fBaryon, TCMB}
:ArgumentTypes: {Real32, Real32, Real32}
:ReturnType:    Manual
:End:

:Begin:
:Function:      TFfit_onek_wrap
:Pattern:       TFFitOneK[k_Real]
:Arguments:     {k}
:ArgumentTypes: {Real32}
:ReturnType:    Manual
:End:

:Begin:
:Function:      TFnowiggles
:Pattern:       TFNoWiggles[OmegaCDM_Real, fBaryon_Real, h_Real, Tcmb_Real, kh_Real]
:Arguments:     {OmegaCDM, fBaryon, h, Tcmb, kh}
:ArgumentTypes: {Real32, Real32, Real32, Real32, Real32}
:ReturnType:    Real32
:End:

:Begin:
:Function:      TFzerobaryon
:Pattern:       TFZeroBaryon[OmegaCDM_Real, h_Real, Tcmb_Real, kh_Real]
:Arguments:     {OmegaCDM, h, Tcmb, kh}
:ArgumentTypes: {Real32, Real32, Real32, Real32}
:ReturnType:    Real32
:End:

:Begin:
:Function:      TFsound_horizon_fit
:Pattern:       TFSoundHorizon[omega0_Real,  fbaryon_Real,  hubble_Real]
:Arguments:     {omega0, fbaryon, hubble}
:ArgumentTypes: {Real32, Real32, Real32}
:ReturnType:    Real32
:End:

:Begin:
:Function:      TFk_peak
:Pattern:       TFkPeak[ omega0_Real,  fbaryon_Real,  hubble_Real]
:Arguments:     {omega0, fbaryon, hubble}
:ArgumentTypes: {Real32, Real32, Real32}
:ReturnType:    Real32
:End:

:Begin:
:Function:      HFset_parameters
:Pattern:       HFSetParameters[OmegaM_Real, OmegaV_Real, Gamma_Real, Sigma8_Real, NSpec_Real, BetaP_Real, Z0_Real, Nonlinear_Integer]
:Arguments:     {OmegaM, OmegaV, Gamma, Sigma8, NSpec, BetaP, Z0, Nonlinear}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer}
:ReturnType:    Manual
:End:

:Begin:
:Function:      P_NL
:Pattern:       HFGetPkNL[a_Real, k_Real]
:Arguments:     {a, k}
:ArgumentTypes: {Real64, Real64}
:ReturnType:    Real64
:End:

:Begin:
:Function:      Pkappa
:Pattern:       HFGetKappa[ell_Real]
:Arguments:     {ell}
:ArgumentTypes: {Real64}
:ReturnType:    Real64
:End:

:Begin:
:Function:      CEget_PkNL
:Pattern:       CEGetPkNL[omegaM_Real, omegaB_Real, ns_Real, sigma8_Real, w_Real, z_Real]
:Arguments:     {omegaM, omegaB, ns, sigma8, w, z}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64}     
:ReturnType:    Manual
:End:

:Begin:
:Function:      franken_CEget_PkNL
:Pattern:       FrankenCEGetPkNL[omegaM_Real, omegaB_Real, h_Real, ns_Real, sigma8_Real, w_Real, z_Real]
:Arguments:     {omegaM, omegaB, h, ns, sigma8, w, z}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64}     
:ReturnType:    Manual
:End:


:Begin:
:Function:      CAMBrun
:Pattern:       CAMBrun[floats_List, ints_List]
:Arguments:     {floats, ints}
:ArgumentTypes: {RealList, IntegerList}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterRpt
:Pattern:       CopterRpt[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, zini_Real, zfin_Real, Neta_Integer, kcut_Real, k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, zini, zfin, Neta, kcut, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer, Real64, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterSpt
:Pattern:       CopterSpt[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, z_Real, epsrel_Real, k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, z, epsrel, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterFWT
:Pattern:       CopterFWT[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, zini_Real, zfin_List, k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, zini, zfin, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64List, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterLpt
:Pattern:       CopterLpt[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, z_Real, epsreal_Real, k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, z, epsreal, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterLargeN
:Pattern:       CopterLargeN[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, zini_Real, zfin_Real, Neta_Integer, epsreal_Real,  k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, zini, zfin, Neta, epsreal, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer, Real64, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterHspt
:Pattern:       CopterHspt[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, z_Real, qmin_Real, qmax_Real, order_Integer,  k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, z, qmin, qmax, order, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterNW
:Pattern:       CopterNW[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, z_Real, formula_Integer,  k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, z, formula, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Integer, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterLinear
:Pattern:       CopterLinear[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, sigma8_Real, z_Real, k_List, Ti_List]
:Arguments:     {h, ns, OmegaM, OmegaB, sigma8, z, k, Ti}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64List, Real64List}
:ReturnType:    Manual
:End:

:Begin:
:Function:      MLcopterGrowth
:Pattern:       CopterGr[h_Real, ns_Real, OmegaM_Real, OmegaB_Real, z_List]
:Arguments:     {h, ns, OmegaM, OmegaB, z}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64List}
:ReturnType:    Manual
:End:


:Begin:
:Function:      MLClass
:Pattern:       MlClass[inifile_String]
:Arguments:     {inifile}
:ArgumentTypes: {String}
:ReturnType:    Manual
:End:


