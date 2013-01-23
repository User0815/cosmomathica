CC = gcc
#cflags = -ggdb3 -p
#lflags = -lm -ggdb3 -p
cflags = -O3
lflags = -lm -O3
DD =  smith2-`date +"%Y%m%d"`.tar

smith2demo: smith2demo.o smith2.o Makefile
	$(CC) $(lflags) -o smith2demo smith2demo.o smith2.o

fsmith2: fsmith2.f smith2.o Makefile
	f77 $(lflags) fsmith2.f -o fsmith2 smith2.o 

smith2demo.o: smith2demo.c smith2.c smith2.h Makefile
	$(CC) $(cflags) -c -o smith2demo.o smith2demo.c

smith2.o: smith2.c smith2.h Makefile
	$(CC) $(cflags) -c -o smith2.o smith2.c

.PHONY: clean backup

clean:
	rm -f *.o *~ *.flc smith2demo fsmith2
backup:
	tar cvf $(DD) *
