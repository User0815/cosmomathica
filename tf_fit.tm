
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

