ccccccccccccccccccccccccccccccccccccccccccccc
c
c     MK 1/2006
c     test for smith et al fitting formula v2.
c     calls routines from smith2.c
ccccccccccccccccccccccccccccccccccccccccccccc

      program fsmith2

      implicit none

      common/constants/pi
      double precision pi
      data pi/3.14159265d0/

      real*8 Omega_m, Omega_v, Gamma, sigma_8, n_spec, beta_p, z0
      integer nonlinear

      real *8 logell, ell, logellmin, logellmax, dlogell, 
     +     a, p_delta, p_kappa


      Omega_m   = 0.3
      Omega_v   = 0.7
      Gamma     = 0.21
      sigma_8   = 0.9
      n_spec    = 1.0
      beta_p    = 1.5
      z0        = 1.0
      nonlinear = 2

      call setparameters(Omega_m, Omega_v, Gamma, sigma_8, n_spec, 
     +     beta_p, z0, nonlinear)


c     density power spectrum
      write(*,*)"# k[Mpc/h] Delta_NL(k)"

      logellmin = 2.0
      logellmax = 7.0
      dlogell   = 0.1
      a         = 0.5

      do logell=logellmin,logellmax,dlogell

         ell = 10**logell
         call pnl(a, ell, p_delta)
         write(*,*)ell/2998.0, ell**3/2/pi**2*p_delta

      enddo


c     convergence power spectrum
      write(*,*)"# l l(l+1)/2pi*P_kappa(l)"

      logellmin = 0.0
      logellmax = 5.0
      dlogell   = 0.1

      do logell=logellmin,logellmax,dlogell

         ell = 10**logell
         call pkappa(ell, p_kappa)

         write(*,*)ell, ell*(ell+1)/2.0/pi*p_kappa

      enddo


      return
      end
