CFLAGS=-O3 -march=native -ffast-math -funroll-loops -flto -pedantic -std=c99 -Wall -Wextra -Werror -Wconversion -std=c99
#CFLAGS=-O3 -Wall -Wextra -Werror -pedantic -Wconversion -std=c99

all: sim

sim: sim.o simlib.o simlib_base.o simlib_metodi.o
	gcc $(CFLAGS) sim.o simlib.o simlib_base.o simlib_metodi.o -o $@ -lglfw -lGL -lm
	
sim.o: ../prg/sim.c ../head/simlib.h ../head/simlib_struct.h
	gcc $(CFLAGS) -c ../prg/sim.c

simlib.o: ../lib/simlib.c ../head/simlib.h ../head/simlib_base.h ../head/simlib_struct.h
	gcc $(CFLAGS) -c ../lib/simlib.c

simlib_base.o: ../lib/simlib_base.c ../head/simlib_base.h ../head/simlib_struct.h
	gcc $(CFLAGS) -c ../lib/simlib_base.c

simlib_metodi.o: ../lib/simlib_metodi.c ../head/simlib_metodi.h ../head/simlib.h ../head/simlib_struct.h
	gcc $(CFLAGS) -c ../lib/simlib_metodi.c

c:
	find . -type f ! -name "Makefile" -delete
