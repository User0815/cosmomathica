
:Begin:
:Function: smith_P_NL_wrap
:Pattern: SmithPNL[a_Real, k_Real]
:Arguments: {a, k}
:ArgumentTypes: {Real64, Real64}
:ReturnType: Manual
:End:


:Begin:
:Function: smith_P_L_wrap
:Pattern: SmithPL[a_Real, k_Real]
:Arguments: {a, k}
:ArgumentTypes: {Real64, Real64}
:ReturnType: Manual
:End:


:Begin:
:Function: smith_set_parameters_wrap
:Pattern: SmithSetParameters[OMEGAM_Real, OMEGAV_Real, GAMMA_Real, SIGMA8_Real,
		   NSPEC_Real, BETAP_Real, Z0_Real, NONLINEAR_Integer]
:Arguments: {OMEGAM, OMEGAV, GAMMA, SIGMA8,
		   NSPEC, BETAP, Z0, NONLINEAR}
:ArgumentTypes: {Real64, Real64, Real64, Real64, Real64, Real64, Real64, Integer}
:ReturnType: Manual
:End:
