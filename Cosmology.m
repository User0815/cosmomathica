(* ::Package:: *)

BeginPackage["Cosmology`"]


Cosmology::usage="This list of rules defines the background cosmology."


Fiducial::usage="Fiducial[X] returns the fiducial value of parameter X."


Redshift::usage="Redshift[a] returns the redshift as a function of the scale factor, i.e. z=1/a+1."


Hubble::usage="Hubble[z] returns the Hubble parameter at a given redshift z."


DimensionlessHubble::usage="DimensionlessHubble[z] returns the Hubble parameter at a given redshift z divided by the Hubble constant today."


w::usage="w[z] returns the equation of state at redshift z using the CPL parameterization."


GrowthFunction::usage="GrowthFunction[z] returns the growth function at redshift z, parameterized by the growth index."


GrowthFactor::usage="GrowthFactor[z] returns the growth factor at redshift z, parameterized by the growth index."


OmegaM::usage="OmegaM[z] returns the relative matter density at redshift z."


Distance::usage="Distance[z] accepts the Option DistanceType with the possible values Comoving, TransverseComoving, AngularDiameter, Luminosity or LookBack. Distance[z1, z2] gives the distance between two galaxies at redshifts z1 and z2 along the line of sight."


OmegaB::usage="Baryon density"
OmegaC::usage="Cold dark matter density"
OmegaL::usage="Dark energy density"
OmegaTot::usage="Total density"
OmegaK::usage="Curvature 'density'"
h::usage="Reduced Hubble parameter"
H0::usage="Hubble parameter"
omegaM::usage="Reduced matter density"
omegaL::usage="Reduced dark energy density"
omegaB::usage="Reduced baryon density"
omegaC::usage="Reduced cold dark matter density"
omegaK::usage="Reduced curvature 'density'"
w0::usage="Equation of state today"
w1::usage="Equation of state running parameter"
gamma::usage="Growth index"
sigma8::usage="Power spectrum amplitude"
ns::usage="Spectral index"
DistanceType::usage="Distance type"
Comoving::usage="Comoving distance"
TransverseComoving::usage="Transeverse comoving distance"
AngularDiameter::usage="Angular diameter distance"
Luminosity::usage="Luminosity distance"


Begin["`Private`"]


Cosmology={OmegaM->.25,
OmegaB->.05,
OmegaC->OmegaM-OmegaB,
OmegaL->.75,
OmegaTot->OmegaM+OmegaL,
OmegaK->1-OmegaTot,
h->.7,
H0->h *1./3000,(*Units: c/Mpc*)
omegaM->OmegaM h^2,
omegaL->OmegaL h^2,
omegaB->OmegaB h^2,
omegaC->OmegaC h^2,
omegaK->OmegaK h^2,
w0->-1,
w1->0,
gamma->.545,(*growth index*)
sigma8->.8,
ns->.9}
cosmoopts:=Cosmology~Join~{
DistanceType->Comoving};


OV[x_,opts:OptionsPattern[]]:=(OptionValue@x/.If[List@opts!={},List@opts,1->1]//.cosmoopts);
Options[OV]:=cosmoopts;


Fiducial[x_,opts:OptionsPattern[]]:=OV[x,opts];
Options[Fiducial]:=cosmoopts;


Redshift=Compile[{{a,_Real}},1/a+1];


w[z_,opts:OptionsPattern[]]:=OV[w0,opts]+OV[w1,opts]*z/(1+z);
Options[w]:=cosmoopts;
fw[z_,opts:OptionsPattern[]]:=Integrate[(1+w[z,opts])/(1+zx),{zx,0,z},GenerateConditions->False];


(* H in units of H_ 0 *)
DimensionlessHubble[z_,opts:OptionsPattern[]]:=Sqrt[OV[OmegaM,opts]*(1+z)^3+OV[OmegaK,opts]*(1+z)^2+OV[OmegaL,opts]*Exp[3*fw[z,opts]]];
Options[DimensionlessHubble]:=cosmoopts;


Hubble[z_,opts:OptionsPattern[]]:=OV[H0,opts]DimensionlessHubble[z,opts];
Options[Hubble]:=cosmoopts;


OmegaM[z_,opts:OptionsPattern[]]:=OV[OmegaM,opts]*(1+z)^3/DimensionlessHubble[z,opts]^2;Options[OmegaM]:=cosmoopts;
(*Note: om0 is not used here*)


sinn=Compile[{{x,_Real},{ok,_Real}},Evaluate@If[ok==0,x,Sinh[Sqrt[ok]x]/Sqrt[ok]]];


Clear[antideriv];
antideriv1[opts:OptionsPattern[]]:=antideriv[opts]=NDSolve[{y'[zx]==1/Hubble[zx,opts],y[0]==0},y,{zx,0,10}][[1,1,2]];
antideriv2[opts:OptionsPattern[]]:=antideriv[opts]=NDSolve[{y'[zx]==1/Hubble[zx,opts]/(1+z),y[0]==0},y,{zx,0,10}][[1,1,2]];
Distance[z_,opts:OptionsPattern[]]:=Switch[OptionValue@DistanceType,
Comoving,antideriv1[opts][z],
TransverseComoving,sinn[Distance[z,DistanceType->Comoving,opts],OV[OmegaK,opts]],
AngularDiameter,Distance[z,DistanceType->TransverseComoving,opts]/(1+z),
Luminosity,Distance[z,DistanceType->TransverseComoving,opts]*(1+z),
LookBack,antideriv2[opts][z]
];
Distance[z1_,z2_,opts:OptionsPattern[]]:=Switch[OptionValue@DistanceType,
Comoving,Distance[z2,opts]-Distance[z1,opts],
TransverseComoving,Null,
AngularDiameter,Null,
Luminosity,Null,
LookBack,Distance[z2,opts]-Distance[z1,opts]];
Options[Distance]:=cosmoopts;


(*growth factor*)
Clear[GrowthFactor,GrowthFunction];
GrowthFactor[z_,opts:OptionsPattern[]]:=OmegaM[z,opts]^OV[gamma,opts];
Options[GrowthFactor]:=cosmoopts;
antideriv3[opts:OptionsPattern[]]:=antideriv3[opts]=NDSolve[{y'[zx]==GrowthFactor[zx,opts]/(1+zx),y[0]==0},y,{zx,0,z}];
GrowthFunction[z_,opts:OptionsPattern[]]:=Exp[-antideriv3[opts][z]];


End[ ]
EndPackage[ ]
