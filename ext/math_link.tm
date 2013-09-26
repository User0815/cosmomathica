
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
:Function:      CAMBrun
:Pattern:       CAMBrun[floats_List, ints_List]
:Arguments:     {floats, ints}
:ArgumentTypes: {RealList, IntegerList}
:ReturnType:    Manual
:End:

