      program mainF

      integer i, j, k
      double precision x(6)
      double precision y(3990)

      !  initialize x to be cosmological parameters 
      !  within the range and redshift
      x(1) = 0.1296   ! omega_m
      x(2) = 0.0224   ! omega_b
      x(3) = 0.9700   ! n_s
      x(4) = 0.8000   ! sigma_8
      x(5) = -1.000   ! w
      x(6) = 0.5000   ! redshift

      write(*,10), (x(j), j = 1, 6)
10    format (6f7.4 )


      ! call the emulator, x: cosmological parameters,
      ! y: vector containing k in first half and P(k) in second half
      ! 1: Delta(k), 2: P(k)

      call emu(x,y,2)

      open(30,file='pk.dat',form='formatted')
     
      do i=1,1995
         write(30,*)y(i),y(i+1995)
      enddo

      stop
      end

