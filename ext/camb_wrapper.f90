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


    subroutine add1Darray(array, output, offset, intarray, intoffset)
        implicit none
        integer, intent(inout) :: offset, intoffset
        double precision, intent(in) :: array(:)
        double precision, intent(out) :: output(:)
        integer, intent(out) :: intarray(:)
        integer i

        if (offset + size(array) > size(output)) stop "camb_wrapper: array too small"

        do i=1,size(array,1)
            output(offset+i) = array(i)
        end do

        intarray(intoffset+1) = 1
        intarray(intoffset+2) = size(array)
        offset = offset + size(array)
        intoffset = intoffset + 2

    end subroutine add1Darray


    subroutine add2Darray(array, output, offset, intarray, intoffset)
        implicit none
        integer, intent(inout) :: offset, intoffset
        double precision, intent(in) :: array(:,:)
        double precision, intent(out) :: output(:)
        integer, intent(out) :: intarray(:)
        integer i,j

        if (offset + size(array) > size(output)) stop "camb_wrapper: array too small"

        do i=1,size(array,1)
            do j=1,size(array,2)
                output(offset+j+(i-1)*size(array,2)) = array(i,j)
            end do
        end do

        intarray(intoffset+1) = 2
        intarray(intoffset+2) = size(array,1)
        intarray(intoffset+3) = size(array,2)
        offset = offset + size(array)
        intoffset = intoffset + 3

    end subroutine add2Darray


    subroutine add3Darray(array, output, offset, intarray, intoffset)
        implicit none
        integer, intent(inout) :: offset, intoffset
        double precision, intent(in) :: array(:,:,:)
        double precision, intent(out) :: output(:)
        integer, intent(out) :: intarray(:)
        integer i,j,k

        if (offset + size(array) > size(output)) stop "camb_wrapper: array too small"

        do i=1,size(array,1)
            do j=1,size(array,2)
                do k=1,size(array,3)
                    output(offset+k+(j-1)*size(array,3)+(i-1)*size(array,2)*size(array,3)) = array(i,j,k)
                end do
            end do
        end do

        intarray(intoffset+1) = 3
        intarray(intoffset+2) = size(array,1)
        intarray(intoffset+3) = size(array,2)
        intarray(intoffset+4) = size(array,3)
        offset = offset + size(array)
        intoffset = intoffset + 4

    end subroutine add3Darray


    subroutine runcamb(floats, floats_len, ints, ints_len, floats_out, floats_out_len, ints_out, ints_out_len) bind(c)
        implicit none

        integer(c_int), intent(in)    :: floats_len, ints_len
        integer(c_int), intent(inout) :: ints_out_len, floats_out_len
        real(c_double), intent(in)    :: floats(floats_len)
        integer(c_int), intent(in)    :: ints(ints_len)
        real(c_double), intent(out)   :: floats_out(floats_out_len)
        integer(c_int), intent(out)   :: ints_out(ints_out_len)

        integer error, fi, ii, eigenstates, fitemp, i, float_offset, int_offset

        Type(CAMBparams) P
        Type(MatterPowerData) PK_data

        ! We have two arrays containing all the parameters: one full of doubles,
        ! one full of ints. We need to fill the structure P with it. See
        ! camb/inidriver.f90 for how it works. We avoid passing structures
        ! between C and Fortran because of compatibility issues, so we pass flat
        ! arrays.


        ! call CAMB_SetDefParams(P)
        ! Compare the following to the function CAMB_SetDefParams.
        ! Obviously the order of the following matters a lot - don't change it
        ! unless you really know what you're doing.

        fi = 1
        ii = 1

#define nextfloat floats(fi); fi=fi+1
#define nextint ints(ii); ii=ii+1
#define nextbool int2bool(ints(ii)); ii=ii+1

        P%omegac  = nextfloat
        P%omegab  = nextfloat
        P%omegav  = nextfloat
        P%H0      = nextfloat
        P%omegan  = nextfloat

        P%TCMB    = nextfloat
        P%YHe     = nextfloat

        P%Num_Nu_massless     = nextfloat
        P%Num_Nu_massive      = nextint
        P%Nu_mass_splittings  = .true. ! int2bool(ints(ii)); ii=ii+1
        P%Nu_mass_eigenstates = nextint
        eigenstates = P%Nu_mass_eigenstates

        P%Nu_mass_degeneracies(1:eigenstates) = floats(fi:fi+eigenstates)
        fi = fi+eigenstates
        P%Nu_mass_fractions(1:eigenstates) = floats(fi:fi+eigenstates)
        fi = fi+eigenstates

        P%same_neutrino_Neff  = .false. ! ?? no idea what this does

        P%Scalar_initial_condition = nextint
        P%NonLinear                = nextint

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
         P%InitPower%k_0_scalar = nextfloat
         P%InitPower%k_0_tensor = nextfloat

        ! call Recombination_SetDefParams(P%Recomb)
             P%Recomb%RECFAST_fudge = 1.14d0
             P%Recomb%RECFAST_fudge_He =.86d0
             P%Recomb%RECFAST_Heswitch = 6
             P%Recomb%RECFAST_Hswitch  = .true.
        ! call Reionization_SetDefParams(P%Reion)
         P%Reion%Reionization      = nextbool
         P%Reion%use_optical_depth = nextbool
         P%Reion%optical_depth     = nextfloat
         P%Reion%redshift          = nextfloat
         P%Reion%fraction          = nextfloat
         P%Reion%delta_redshift    = nextfloat

         !TODO bispectrum?

        P%Transfer%high_precision = nextbool

        P%Want_CMB     = nextbool
        P%WantTransfer = nextbool
        P%WantCls      = nextbool
        P%WantScalars = nextbool
        P%WantVectors = nextbool
        P%WantTensors = nextbool
        P%want_zstar  = nextbool
        P%want_zdrag  = nextbool

        P%OutputNormalization = nextint

        P%Max_l            = nextint
        P%Max_eta_k        = nextfloat
        P%Max_l_tensor     = nextint
        P%Max_eta_k_tensor = nextfloat
        P%Transfer%kmax          = nextfloat
        P%Transfer%k_per_logint  = nextint
        P%Transfer%num_redshifts = nextint
        ! This is an array with length num_redshifts
        P%Transfer%redshifts     = floats(fi:fi+ints(ii-1)); fi=fi+ints(ii-1) 

        P%AccuratePolarization = nextbool
        P%AccurateReionization = nextbool
        P%AccurateBB           = nextbool

        P%DoLensing = nextbool
        P%OnlyTransfers   = nextbool
        P%DerivedParameters = nextbool
        P%MassiveNuMethod = nextint

        CP%DerivedParameters = .true.
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

        call CAMB_GetResults(P)
        if (global_error_flag/=0) then
            write (*,*) 'Error result '//trim(global_error_message)
            stop
        endif
        ! the global variables MT, Cl_scalar, Cl_vector, Cl_tensor now contain
        ! meaningful data

        ! Return the results

        ints_out(1) = error
        int_offset = 1

#define add3d(array) call add3darray(array, floats_out, float_offset, ints_out, int_offset)
#define add2d(array) call add2darray(array, floats_out, float_offset, ints_out, int_offset)
#define add1d(array) call add1darray(array, floats_out, float_offset, ints_out, int_offset)

        ! Derived parameters first
        float_offset = 0
        call add1darray( (/ ThermoDerivedParams( derived_Age ),&
            ThermoDerivedParams( derived_zstar ),&
            ThermoDerivedParams( derived_rstar ),&
            ThermoDerivedParams( derived_thetastar ),&
            ThermoDerivedParams( derived_zdrag ),&
            ThermoDerivedParams( derived_rdrag ),&
            ThermoDerivedParams( derived_kD ),&
            ThermoDerivedParams( derived_thetaD ),&
            ThermoDerivedParams( derived_zEQ ),&
            ThermoDerivedParams( derived_thetaEQ ) /),&
        floats_out, float_offset, ints_out, int_offset)


        if(P%WantScalars) add3d(Cl_scalar)
        if(P%WantVectors) add3d(Cl_vector)
        if(P%WantTensors) add3d(Cl_tensor)

        if (P%WantTransfer) then
            do i=1,P%InitPower%nn     
                call Transfer_GetMatterPowerData(MT, PK_data, i)
                add1d(PK_data%log_kh)
                add2d(PK_data%matpower)
                call MatterPowerdata_MakeNonlinear(PK_data)
                add2d(PK_data%matpower)
            end do
            add3d(dble(MT%TransferData))
            add2d(MT%sigma_8)
        endif


        ! Background: TODO: CAMB never fills these arrays. But the functions
        ! exist, so we have to do it by hand.
        if (associated(BackgroundOutputs%z_outputs)) then
            add1d(BackgroundOutputs%z_outputs)
            add1d(BackgroundOutputs%H)
            add1d(BackgroundOutputs%DA)
            add1d(BackgroundOutputs%rs_by_D_v)
        endif

        ints_out_len = int_offset
        floats_out_len = float_offset
        
        call CAMB_cleanup
    end subroutine runcamb


end module cambwrapper
