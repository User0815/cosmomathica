/*
 * This file automatically produced by /opt/Wolfram/Mathematica/9.0.1/SystemFiles/Links/MathLink/DeveloperKit/Linux-x86-64/CompilerAdditions/mprep from:
 *	math_link.tm
 * mprep Revision 16 Copyright (c) Wolfram Research, Inc. 1990-2009
 */

#define MPREP_REVISION 16

#include "mathlink.h"

int MLAbort = 0;
int MLDone  = 0;
long MLSpecialCharacter = '\0';

MLINK stdlink = 0;
MLEnvironment stdenv = 0;
#if MLINTERFACE >= 3
MLYieldFunctionObject stdyielder = (MLYieldFunctionObject)0;
MLMessageHandlerObject stdhandler = (MLMessageHandlerObject)0;
#else
MLYieldFunctionObject stdyielder = 0;
MLMessageHandlerObject stdhandler = 0;
#endif /* MLINTERFACE >= 3 */

/********************************* end header *********************************/


void TFset_parameters_wrap P(( float _tp1, float _tp2, float _tp3));

#if MLPROTOTYPES
static int _tr0( MLINK mlp)
#else
static int _tr0(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp1;
	float _tp2;
	float _tp3;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal32( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal32( mlp, &_tp3) ) goto L2;
	if ( ! MLNewPacket(mlp) ) goto L3;

	TFset_parameters_wrap(_tp1, _tp2, _tp3);

	res = 1;
L3: L2: L1: 
L0:	return res;
} /* _tr0 */


void TFfit_onek_wrap P(( float _tp1));

#if MLPROTOTYPES
static int _tr1( MLINK mlp)
#else
static int _tr1(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp1;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLNewPacket(mlp) ) goto L1;

	TFfit_onek_wrap(_tp1);

	res = 1;
L1: 
L0:	return res;
} /* _tr1 */


float TFnowiggles P(( float _tp1, float _tp2, float _tp3, float _tp4, float _tp5));

#if MLPROTOTYPES
static int _tr2( MLINK mlp)
#else
static int _tr2(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp0;
	float _tp1;
	float _tp2;
	float _tp3;
	float _tp4;
	float _tp5;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal32( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal32( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal32( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal32( mlp, &_tp5) ) goto L4;
	if ( ! MLNewPacket(mlp) ) goto L5;

	_tp0 = TFnowiggles(_tp1, _tp2, _tp3, _tp4, _tp5);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal32( mlp, _tp0);
L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr2 */


float TFzerobaryon P(( float _tp1, float _tp2, float _tp3, float _tp4));

#if MLPROTOTYPES
static int _tr3( MLINK mlp)
#else
static int _tr3(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp0;
	float _tp1;
	float _tp2;
	float _tp3;
	float _tp4;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal32( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal32( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal32( mlp, &_tp4) ) goto L3;
	if ( ! MLNewPacket(mlp) ) goto L4;

	_tp0 = TFzerobaryon(_tp1, _tp2, _tp3, _tp4);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal32( mlp, _tp0);
L4: L3: L2: L1: 
L0:	return res;
} /* _tr3 */


float TFsound_horizon_fit P(( float _tp1, float _tp2, float _tp3));

#if MLPROTOTYPES
static int _tr4( MLINK mlp)
#else
static int _tr4(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp0;
	float _tp1;
	float _tp2;
	float _tp3;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal32( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal32( mlp, &_tp3) ) goto L2;
	if ( ! MLNewPacket(mlp) ) goto L3;

	_tp0 = TFsound_horizon_fit(_tp1, _tp2, _tp3);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal32( mlp, _tp0);
L3: L2: L1: 
L0:	return res;
} /* _tr4 */


float TFk_peak P(( float _tp1, float _tp2, float _tp3));

#if MLPROTOTYPES
static int _tr5( MLINK mlp)
#else
static int _tr5(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	float _tp0;
	float _tp1;
	float _tp2;
	float _tp3;
	if ( ! MLGetReal32( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal32( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal32( mlp, &_tp3) ) goto L2;
	if ( ! MLNewPacket(mlp) ) goto L3;

	_tp0 = TFk_peak(_tp1, _tp2, _tp3);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal32( mlp, _tp0);
L3: L2: L1: 
L0:	return res;
} /* _tr5 */


void HFset_parameters P(( double _tp1, double _tp2, double _tp3, double _tp4, double _tp5, double _tp6, double _tp7, int _tp8));

#if MLPROTOTYPES
static int _tr6( MLINK mlp)
#else
static int _tr6(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp1;
	double _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	double _tp7;
	int _tp8;
	if ( ! MLGetReal64( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal64( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal64( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal64( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal64( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal64( mlp, &_tp6) ) goto L5;
	if ( ! MLGetReal64( mlp, &_tp7) ) goto L6;
	if ( ! MLGetInteger( mlp, &_tp8) ) goto L7;
	if ( ! MLNewPacket(mlp) ) goto L8;

	HFset_parameters(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6, _tp7, _tp8);

	res = 1;
L8: L7: L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr6 */


double P_NL P(( double _tp1, double _tp2));

#if MLPROTOTYPES
static int _tr7( MLINK mlp)
#else
static int _tr7(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp0;
	double _tp1;
	double _tp2;
	if ( ! MLGetReal64( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal64( mlp, &_tp2) ) goto L1;
	if ( ! MLNewPacket(mlp) ) goto L2;

	_tp0 = P_NL(_tp1, _tp2);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal64( mlp, _tp0);
L2: L1: 
L0:	return res;
} /* _tr7 */


double Pkappa P(( double _tp1));

#if MLPROTOTYPES
static int _tr8( MLINK mlp)
#else
static int _tr8(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp0;
	double _tp1;
	if ( ! MLGetReal64( mlp, &_tp1) ) goto L0;
	if ( ! MLNewPacket(mlp) ) goto L1;

	_tp0 = Pkappa(_tp1);

	res = MLAbort ?
		MLPutFunction( mlp, "Abort", 0) : MLPutReal64( mlp, _tp0);
L1: 
L0:	return res;
} /* _tr8 */


void CEget_PkNL P(( double _tp1, double _tp2, double _tp3, double _tp4, double _tp5, double _tp6));

#if MLPROTOTYPES
static int _tr9( MLINK mlp)
#else
static int _tr9(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double _tp1;
	double _tp2;
	double _tp3;
	double _tp4;
	double _tp5;
	double _tp6;
	if ( ! MLGetReal64( mlp, &_tp1) ) goto L0;
	if ( ! MLGetReal64( mlp, &_tp2) ) goto L1;
	if ( ! MLGetReal64( mlp, &_tp3) ) goto L2;
	if ( ! MLGetReal64( mlp, &_tp4) ) goto L3;
	if ( ! MLGetReal64( mlp, &_tp5) ) goto L4;
	if ( ! MLGetReal64( mlp, &_tp6) ) goto L5;
	if ( ! MLNewPacket(mlp) ) goto L6;

	CEget_PkNL(_tp1, _tp2, _tp3, _tp4, _tp5, _tp6);

	res = 1;
L6: L5: L4: L3: L2: L1: 
L0:	return res;
} /* _tr9 */


void CAMBrun P(( double * _tp1, long _tpl1, int * _tp2, long _tpl2));

#if MLPROTOTYPES
static int _tr10( MLINK mlp)
#else
static int _tr10(mlp) MLINK mlp;
#endif
{
	int	res = 0;
	double * _tp1;
	long _tpl1;
	int * _tp2;
	long _tpl2;
	if ( ! MLGetRealList( mlp, &_tp1, &_tpl1) ) goto L0;
	if ( ! MLGetIntegerList( mlp, &_tp2, &_tpl2) ) goto L1;
	if ( ! MLNewPacket(mlp) ) goto L2;

	CAMBrun(_tp1, _tpl1, _tp2, _tpl2);

	res = 1;
L2:	MLDisownIntegerList( mlp, _tp2, _tpl2);
L1:	MLDisownRealList( mlp, _tp1, _tpl1);

L0:	return res;
} /* _tr10 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((MLINK));
	const char  *f_name;
	} _tramps[11] = {
		{ 3, 0, _tr0, "TFset_parameters_wrap" },
		{ 1, 0, _tr1, "TFfit_onek_wrap" },
		{ 5, 0, _tr2, "TFnowiggles" },
		{ 4, 0, _tr3, "TFzerobaryon" },
		{ 3, 0, _tr4, "TFsound_horizon_fit" },
		{ 3, 0, _tr5, "TFk_peak" },
		{ 8, 0, _tr6, "HFset_parameters" },
		{ 2, 0, _tr7, "P_NL" },
		{ 1, 0, _tr8, "Pkappa" },
		{ 6, 0, _tr9, "CEget_PkNL" },
		{ 2, 0, _tr10, "CAMBrun" }
		};

#define CARDOF_EVALSTRS 0

static int _definepattern P(( MLINK, char*, char*, int));

int  _MLDoCallPacket P(( MLINK, struct func[], int));


#if MLPROTOTYPES
int MLInstall( MLINK mlp)
#else
int MLInstall(mlp) MLINK mlp;
#endif
{
	int _res;
	_res = MLConnect(mlp);
	if (_res) _res = _definepattern(mlp, (char *)"TFSetParameters[OmegaMh2_Real, fBaryon_Real, TCMB_Real]", (char *)"{OmegaMh2, fBaryon, TCMB}", 0);
	if (_res) _res = _definepattern(mlp, (char *)"TFFitOneK[k_Real]", (char *)"{k}", 1);
	if (_res) _res = _definepattern(mlp, (char *)"TFNoWiggles[OmegaCDM_Real, fBaryon_Real, h_Real, Tcmb_Real, kh_Real]", (char *)"{OmegaCDM, fBaryon, h, Tcmb, kh}", 2);
	if (_res) _res = _definepattern(mlp, (char *)"TFZeroBaryon[OmegaCDM_Real, h_Real, Tcmb_Real, kh_Real]", (char *)"{OmegaCDM, h, Tcmb, kh}", 3);
	if (_res) _res = _definepattern(mlp, (char *)"TFSoundHorizon[omega0_Real,  fbaryon_Real,  hubble_Real]", (char *)"{omega0, fbaryon, hubble}", 4);
	if (_res) _res = _definepattern(mlp, (char *)"TFkPeak[ omega0_Real,  fbaryon_Real,  hubble_Real]", (char *)"{omega0, fbaryon, hubble}", 5);
	if (_res) _res = _definepattern(mlp, (char *)"HFSetParameters[OmegaM_Real, OmegaV_Real, Gamma_Real, Sigma8_Real, NSpec_Real, BetaP_Real, Z0_Real, Nonlinear_Integer]", (char *)"{OmegaM, OmegaV, Gamma, Sigma8, NSpec, BetaP, Z0, Nonlinear}", 6);
	if (_res) _res = _definepattern(mlp, (char *)"HFGetPkNL[a_Real, k_Real]", (char *)"{a, k}", 7);
	if (_res) _res = _definepattern(mlp, (char *)"HFGetKappa[ell_Real]", (char *)"{ell}", 8);
	if (_res) _res = _definepattern(mlp, (char *)"CEGetPkNL[omegaM_Real, omegaB_Real, ns_Real, sigma8_Real, w_Real, z_Real]", (char *)"{omegaM, omegaB, ns, sigma8, w, z}", 9);
	if (_res) _res = _definepattern(mlp, (char *)"CAMBrun[floats_List, ints_List]", (char *)"{floats, ints}", 10);
	if (_res) _res = MLPutSymbol( mlp, "End");
	if (_res) _res = MLFlush( mlp);
	return _res;
} /* MLInstall */


#if MLPROTOTYPES
int MLDoCallPacket( MLINK mlp)
#else
int MLDoCallPacket( mlp) MLINK mlp;
#endif
{
	return _MLDoCallPacket( mlp, _tramps, 11);
} /* MLDoCallPacket */

/******************************* begin trailer ********************************/

#ifndef EVALSTRS_AS_BYTESTRINGS
#	define EVALSTRS_AS_BYTESTRINGS 1
#endif


#if CARDOF_EVALSTRS
#if MLPROTOTYPES
static int  _doevalstr( MLINK mlp, int n)
#else
static int  _doevalstr( mlp, n)
	 MLINK mlp; int n;
#endif
{
	long bytesleft, charsleft, bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
	long charsnow;
#endif
	char **s, **p;
	char *t;

	s = (char **)evalstrs;
	while( n-- > 0){
		if( *s == 0) break;
		while( *s++ != 0){}
	}
	if( *s == 0) return 0;
	bytesleft = 0;
	charsleft = 0;
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft += bytesnow;
		charsleft += bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
		t = *p;
		charsleft -= MLCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
#endif
		++p;
	}


	MLPutNext( mlp, MLTKSTR);
#if EVALSTRS_AS_BYTESTRINGS
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		MLPut8BitCharacters( mlp, bytesleft, (unsigned char*)*p, bytesnow);
		++p;
	}
#else
	MLPut7BitCount( mlp, charsleft, bytesleft);
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		t = *p;
		charsnow = bytesnow - MLCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
		charsleft -= charsnow;
		MLPut7BitCharacters(  mlp, charsleft, *p, bytesnow, charsnow);
		++p;
	}
#endif
	return MLError( mlp) == MLEOK;
}
#endif /* CARDOF_EVALSTRS */


#if MLPROTOTYPES
static int  _definepattern( MLINK mlp, char *patt, char *args, int func_n)
#else
static int  _definepattern( mlp, patt, args, func_n)
	MLINK  mlp;
	char  *patt, *args;
	int    func_n;
#endif
{
	MLPutFunction( mlp, "DefineExternal", (long)3);
	  MLPutString( mlp, patt);
	  MLPutString( mlp, args);
	  MLPutInteger( mlp, func_n);
	return !MLError(mlp);
} /* _definepattern */


#if MLPROTOTYPES
int _MLDoCallPacket( MLINK mlp, struct func functable[], int nfuncs)
#else
int _MLDoCallPacket( mlp, functable, nfuncs)
	MLINK mlp;
	struct func functable[];
	int nfuncs;
#endif
{
	long len;
	int n, res = 0;
	struct func* funcp;

	if( ! MLGetInteger( mlp, &n) ||  n < 0 ||  n >= nfuncs) goto L0;
	funcp = &functable[n];

	if( funcp->f_nargs >= 0
	&& ( ! MLCheckFunction(mlp, "List", &len)
	     || ( !funcp->manual && (len != funcp->f_nargs))
	     || (  funcp->manual && (len <  funcp->f_nargs))
	   )
	) goto L0;

	stdlink = mlp;
	res = (*funcp->f_func)( mlp);

L0:	if( res == 0)
		res = MLClearError( mlp) && MLPutSymbol( mlp, "$Failed");
	return res && MLEndPacket( mlp) && MLNewPacket( mlp);
} /* _MLDoCallPacket */


#if MLPROTOTYPES
mlapi_packet MLAnswer( MLINK mlp)
#else
mlapi_packet MLAnswer( mlp)
	MLINK mlp;
#endif
{
	mlapi_packet pkt = 0;

	while( !MLDone && !MLError(mlp) && (pkt = MLNextPacket(mlp), pkt) && pkt == CALLPKT){
		MLAbort = 0;
		if( !MLDoCallPacket(mlp)) pkt = 0;
	}
	MLAbort = 0;
	return pkt;
} /* MLAnswer */



/*
	Module[ { me = $ParentLink},
		$ParentLink = contents of RESUMEPKT;
		Message[ MessageName[$ParentLink, "notfe"], me];
		me]
*/

#if MLPROTOTYPES
static int refuse_to_be_a_frontend( MLINK mlp)
#else
static int refuse_to_be_a_frontend( mlp)
	MLINK mlp;
#endif
{
	int pkt;

	MLPutFunction( mlp, "EvaluatePacket", 1);
	  MLPutFunction( mlp, "Module", 2);
	    MLPutFunction( mlp, "List", 1);
		  MLPutFunction( mlp, "Set", 2);
		    MLPutSymbol( mlp, "me");
	        MLPutSymbol( mlp, "$ParentLink");
	  MLPutFunction( mlp, "CompoundExpression", 3);
	    MLPutFunction( mlp, "Set", 2);
	      MLPutSymbol( mlp, "$ParentLink");
	      MLTransferExpression( mlp, mlp);
	    MLPutFunction( mlp, "Message", 2);
	      MLPutFunction( mlp, "MessageName", 2);
	        MLPutSymbol( mlp, "$ParentLink");
	        MLPutString( mlp, "notfe");
	      MLPutSymbol( mlp, "me");
	    MLPutSymbol( mlp, "me");
	MLEndPacket( mlp);

	while( (pkt = MLNextPacket( mlp), pkt) && pkt != SUSPENDPKT)
		MLNewPacket( mlp);
	MLNewPacket( mlp);
	return MLError( mlp) == MLEOK;
}


#if MLPROTOTYPES
#if MLINTERFACE >= 3
int MLEvaluate( MLINK mlp, char *s)
#else
int MLEvaluate( MLINK mlp, charp_ct s)
#endif /* MLINTERFACE >= 3 */
#else
int MLEvaluate( mlp, s)
	MLINK mlp;
#if MLINTERFACE >= 3
	char *s;
#else
	charp_ct s;
#endif /* MLINTERFACE >= 3 */
#endif
{
	if( MLAbort) return 0;
	return MLPutFunction( mlp, "EvaluatePacket", 1L)
		&& MLPutFunction( mlp, "ToExpression", 1L)
		&& MLPutString( mlp, s)
		&& MLEndPacket( mlp);
} /* MLEvaluate */


#if MLPROTOTYPES
#if MLINTERFACE >= 3
int MLEvaluateString( MLINK mlp, char *s)
#else
int MLEvaluateString( MLINK mlp, charp_ct s)
#endif /* MLINTERFACE >= 3 */
#else
int MLEvaluateString( mlp, s)
	MLINK mlp;
#if MLINTERFACE >= 3
	char *s;
#else
	charp_ct s;
#endif /* MLINTERFACE >= 3 */
#endif
{
	int pkt;
	if( MLAbort) return 0;
	if( MLEvaluate( mlp, s)){
		while( (pkt = MLAnswer( mlp), pkt) && pkt != RETURNPKT)
			MLNewPacket( mlp);
		MLNewPacket( mlp);
	}
	return MLError( mlp) == MLEOK;
} /* MLEvaluateString */


#if MLINTERFACE >= 3
#if MLPROTOTYPES
void MLDefaultHandler( MLINK mlp, int message, int n)
#else
void MLDefaultHandler( mlp, message, n)
	MLINK mlp;
	int message, n;
#endif
#else
#if MLPROTOTYPES
void MLDefaultHandler( MLINK mlp, unsigned long message, unsigned long n)
#else
void MLDefaultHandler( mlp, message, n)
	MLINK mlp;
	unsigned long message, n;
#endif
#endif /* MLINTERFACE >= 3 */
{
	switch (message){
	case MLTerminateMessage:
		MLDone = 1;
	case MLInterruptMessage:
	case MLAbortMessage:
		MLAbort = 1;
	default:
		return;
	}
}

#if MLPROTOTYPES
#if MLINTERFACE >= 3
static int _MLMain( char **argv, char **argv_end, char *commandline)
#else
static int _MLMain( charpp_ct argv, charpp_ct argv_end, charp_ct commandline)
#endif /* MLINTERFACE >= 3 */
#else
static int _MLMain( argv, argv_end, commandline)
#if MLINTERFACE >= 3
  char **argv, argv_end;
  char *commandline;
#else
  charpp_ct argv, argv_end;
  charp_ct commandline;
#endif /* MLINTERFACE >= 3 */
#endif
{
	MLINK mlp;
#if MLINTERFACE >= 3
	int err;
#else
	long err;
#endif /* MLINTERFACE >= 3 */

	if( !stdenv)
		stdenv = MLInitialize( (MLParametersPointer)0);
	if( stdenv == (MLEnvironment)0) goto R0;

#if MLINTERFACE >= 3
	if( !stdhandler)
		stdhandler = (MLMessageHandlerObject)MLDefaultHandler;
#else
	if( !stdhandler)
		stdhandler = MLCreateMessageHandler( stdenv, MLDefaultHandler, 0);
#endif /* MLINTERFACE >= 3 */


	mlp = commandline
		? MLOpenString( stdenv, commandline, &err)
#if MLINTERFACE >= 3
		: MLOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
#else
		: MLOpenArgv( stdenv, argv, argv_end, &err);
#endif
	if( mlp == (MLINK)0){
		MLAlert( stdenv, MLErrorString( stdenv, err));
		goto R1;
	}

	if( stdyielder) MLSetYieldFunction( mlp, stdyielder);
	if( stdhandler) MLSetMessageHandler( mlp, stdhandler);

	if( MLInstall( mlp))
		while( MLAnswer( mlp) == RESUMEPKT){
			if( ! refuse_to_be_a_frontend( mlp)) break;
		}

	MLClose( mlp);
R1:	MLDeinitialize( stdenv);
	stdenv = (MLEnvironment)0;
R0:	return !MLDone;
} /* _MLMain */


#if MLPROTOTYPES
#if MLINTERFACE >= 3
int MLMainString( char *commandline)
#else
int MLMainString( charp_ct commandline)
#endif /* MLINTERFACE >= 3 */
#else
#if MLINTERFACE >= 3
int MLMainString( commandline)  char *commandline;
#else
int MLMainString( commandline)  charp_ct commandline;
#endif /* MLINTERFACE >= 3 */
#endif
{
	return _MLMain( (charpp_ct)0, (charpp_ct)0, commandline);
}

#if MLPROTOTYPES
int MLMainArgv( char** argv, char** argv_end) /* note not FAR pointers */
#else
int MLMainArgv( argv, argv_end)  char **argv, **argv_end;
#endif
{   
	static char FAR * far_argv[128];
	int count = 0;
	
	while(argv < argv_end)
		far_argv[count++] = *argv++;
		 
	return _MLMain( far_argv, far_argv + count, (charp_ct)0);

}

#if MLPROTOTYPES
#if MLINTERFACE >= 3
int MLMain( int argc, char **argv)
#else
int MLMain( int argc, charpp_ct argv)
#endif /* MLINTERFACE >= 3 */
#else
#if MLINTERFACE >= 3
int MLMain( argc, argv) int argc; char **argv;
#else
int MLMain( argc, argv) int argc; charpp_ct argv;
#endif /* MLINTERFACE >= 3 */
#endif
{
#if MLINTERFACE >= 3
 	return _MLMain( argv, argv + argc, (char *)0);
#else
 	return _MLMain( argv, argv + argc, (charp_ct)0);
#endif /* MLINTERFACE >= 3 */
}
 
