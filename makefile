CC=gcc
CFLAGS=-g -framework SDL2
DEPS = bsp_maths.h level_gen.h
OBJ = bsp.o bsp_maths.o level_gen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bsp: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)