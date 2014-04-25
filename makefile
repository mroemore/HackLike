CC=gcc
CFLAGS=-g -framework SDL2 -Wall
DEPS = maths_helper.h level_gen.h
OBJ = main.o maths_helper.o level_gen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bsp: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
