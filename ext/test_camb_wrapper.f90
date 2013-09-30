program testwrapper

    use cambwrapper
    implicit none

    integer, parameter :: floats_len = 10, ints_len = 10, output_len = 10
    double precision :: floats(floats_len), outp(output_len)
    integer  :: ints(ints_len)

    call runcamb(floats, floats_len, ints, ints_len, outp, output_len)

    write(*,*) "end"

end program testwrapper
