
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
:Function:      HFset_parameters
:Pattern:       HFSetParameters[OmegaM_Real, OmegaV_Real, Gamma_Real, Sigma8_Real, NSpec_Real, BetaP_Real, Z0_Real, Nonlinear_Integer]
:Arguments:     {OmegaM, OmegaV, Gamma, Sigma8, NSpec, BetaP, Z0, Nonlinear}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer}
:ReturnType:    Manual
:End:

:Begin:
:Function:      HFget_PkNL
:Pattern:       HFGetPkNL[a_Real, k_Real]
:Arguments:     {a, k}
:ArgumentTypes: {Real64, Real64}
:ReturnType:    Manual
:End:

:Begin:
:Function:      HFget_kappa
:Pattern:       HFGetKappa[ell_Real]
:Arguments:     {ell}
:ArgumentTypes: {Real64}
:ReturnType:    Manual
:End:

