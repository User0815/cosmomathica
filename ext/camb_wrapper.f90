module cambwrapper

    use iso_c_binding

    use CAMB
    use LambdaGeneral
    use Lensing
    use AMLUtils
    use Transfer
    use constants
    use Bispectrum
    use CAMBmain

    implicit none

contains
    
    function int2bool(i)
        implicit none
        integer, intent(in) :: i
        logical :: int2bool
        
        if (i == 0) then
            int2bool = .false.
        else
            int2bool = .true.
        endif

    end function int2bool


    subroutine runcamb(floats, floats_len, ints, ints_len, output, out_len) bind(c)
        implicit none

        integer(c_int), intent(in)    :: floats_len, ints_len, out_len
        real(c_double), intent(in)    :: floats(floats_len)
        integer(c_int), intent(in)    :: ints(ints_len)
        real(c_double), intent(out)   :: output(out_len)

        integer error, fi, ii, eigenstates, fitemp, lmax
        double precision age, zre, sigma8
        real(4), allocatable :: clout(:,:)

        Type(CAMBparams) P
        Type(CAMBdata) CAMBout

        ! We have two arrays containing all the parameters: one full of doubles,
        ! one full of ints. We need to fill the structure P with it. See
        ! camb/inidriver.f90 for how it works.

        fi = 1
        ii = 1

        ! call CAMB_SetDefParams(P)
        ! Compare the following to the function CAMB_SetDefParams.
        ! Obviously the order of the following matters a lot - don't change it
        ! unless you really know what you're doing.

        P%omegac  = floats(fi); fi=fi+1
        P%omegab  = floats(fi); fi=fi+1
        P%omegav  = floats(fi); fi=fi+1
        P%H0      = floats(fi); fi=fi+1
        P%omegan  = floats(fi); fi=fi+1

        P%TCMB    = floats(fi); fi=fi+1
        P%YHe     = floats(fi); fi=fi+1

        P%Num_Nu_massless     = floats(fi); fi=fi+1
        P%Num_Nu_massive      = ints(ii); ii=ii+1
        P%Nu_mass_splittings  = .true. ! int2bool(ints(ii)); ii=ii+1
        P%Nu_mass_eigenstates = ints(ii); ii=ii+1
        eigenstates = P%Nu_mass_eigenstates

        P%Nu_mass_degeneracies(1:eigenstates) = floats(fi:fi+eigenstates)
        fi = fi+eigenstates
        P%Nu_mass_fractions(1:eigenstates) = floats(fi:fi+eigenstates)
        fi = fi+eigenstates

        P%same_neutrino_Neff  = .false. ! ?? no idea what this does

        P%Scalar_initial_condition = ints(ii); ii=ii+1
        P%NonLinear                = ints(ii); ii=ii+1

        ! call SetDefPowerParams(P%InitPower)
        ! Compare with SetDefPowerParams
        ! These are arrays with length nn
         P%InitPower%nn     = ints(ii); ii=ii+1 !number of initial power spectra
         fitemp = ints(ii-1)
         P%InitPower%an(1:fitemp)     = floats(fi:fi+fitemp); fi=fi+fitemp !scalar spectral index
         P%InitPower%n_run(1:fitemp)  = floats(fi:fi+fitemp); fi=fi+fitemp !running of scalar spectral index
         P%InitPower%ant(1:fitemp)    = floats(fi:fi+fitemp); fi=fi+fitemp !tensor spectra index
         P%InitPower%rat = 1d0
         P%InitPower%rat(1:fitemp)    = floats(fi:fi+fitemp); fi=fi+fitemp
         P%InitPower%ScalarPowerAmp(1:fitemp) = floats(fi:fi+fitemp); fi=fi+fitemp
         P%InitPower%k_0_scalar = floats(fi); fi=fi+1
         P%InitPower%k_0_tensor = floats(fi); fi=fi+1

        ! call Recombination_SetDefParams(P%Recomb)
             P%Recomb%RECFAST_fudge = 1.14d0
             P%Recomb%RECFAST_fudge_He =.86d0
             P%Recomb%RECFAST_Heswitch = 6
             P%Recomb%RECFAST_Hswitch  = .true.
        ! call Reionization_SetDefParams(P%Reion)
         P%Reion%Reionization      = int2bool(ints(ii)); ii = ii+1
         P%Reion%use_optical_depth = int2bool(ints(ii)); ii = ii+1
         P%Reion%optical_depth     = floats(fi); fi = fi+1
         P%Reion%redshift          = floats(fi); fi = fi+1
         P%Reion%fraction          = floats(fi); fi = fi+1
         P%Reion%delta_redshift    = floats(fi); fi = fi+1

         !TODO bispectrum?

        P%Transfer%high_precision = int2bool(ints(ii)); ii=ii+1

        P%Want_CMB     = int2bool(ints(ii)); ii=ii+1
        P%WantTransfer = int2bool(ints(ii)); ii=ii+1
        P%WantCls      = int2bool(ints(ii)); ii=ii+1
        P%WantScalars = int2bool(ints(ii)); ii=ii+1
        P%WantVectors = int2bool(ints(ii)); ii=ii+1
        P%WantTensors = int2bool(ints(ii)); ii=ii+1
        P%want_zstar  = int2bool(ints(ii)); ii=ii+1
        P%want_zdrag  = int2bool(ints(ii)); ii=ii+1

        P%OutputNormalization = ints(ii); ii=ii+1

        P%Max_l            = ints(ii); ii=ii+1
        P%Max_eta_k        = floats(fi); fi=fi+1
        P%Max_l_tensor     = ints(ii); ii=ii+1
        P%Max_eta_k_tensor = floats(fi); fi=fi+1
        P%Transfer%kmax          = floats(fi); fi = fi+1
        P%Transfer%k_per_logint  = ints(ii); ii=ii+1
        P%Transfer%num_redshifts = ints(ii); ii=ii+1
        ! This is an array with length num_redshifts
        P%Transfer%redshifts     = floats(fi:fi+ints(ii-1)); fi=fi+ints(ii-1) 

        P%AccuratePolarization = int2bool(ints(ii)); ii=ii+1
        P%AccurateReionization = int2bool(ints(ii)); ii=ii+1
        P%AccurateBB           = int2bool(ints(ii)); ii=ii+1

        P%DoLensing = int2bool(ints(ii)); ii=ii+1
        P%OnlyTransfers   = int2bool(ints(ii)); ii=ii+1
        P%DerivedParameters = int2bool(ints(ii)); ii=ii+1
        P%MassiveNuMethod = ints(ii); ii=ii+1

        !TODO DoTensorNeutrinos? ThreadNum?

        if (ii-1 /= ints_len .or. fi-1 /= floats_len) then
            write(*,*) "Wrong number of parameters: ", fi-1,ii-1
            write(*,*) "Expected: ", floats_len, ints_len
            stop
        endif

        error = 0
        if (.not. CAMB_ValidateParams(P)) stop 'Stopped due to parameter error'
        call  CAMBParams_Set(P, error, .false.)
        if (error>0) write(*,*) "Error: ",error,trim(global_error_message)

        ! Return the results
        call CAMB_GetTransfers(P, CAMBout, error)
        if (error>0) write(*,*) "Error: ",error,trim(global_error_message)

        lmax = P%Max_l
        allocate(clout(2:lmax,1:4))
        call CAMB_GetCls(clout, lmax, 1, .false.)

        age = CAMB_GetAge(P)
        zre = CAMB_GetZreFromTau(P,P%Reion%optical_depth) 
        sigma8 = CAMBout%MTrans%sigma_8(1,1)!(:P%Transfer%num_redshifts, :P%InitPower%nn) 

        write(*,*) size(CAMBout%MTrans%TransferData,1)
        write(*,*) size(CAMBout%MTrans%TransferData,2)
        write(*,*) size(CAMBout%MTrans%TransferData,3)

        ! Pass contents from CAMBout and clout back to MMA
        ! CAMBout%ClTransScal, ClTransVec, ClTransTens
        output(1) = 1d0*error
        output(2) = age
        output(3) = zre
        output(4) = sigma8

        
    end subroutine runcamb


end module cambwrapper
