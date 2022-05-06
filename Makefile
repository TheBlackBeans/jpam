all: jpam.so

jpam.so: jpam.o string.o challenge_gen.o
	gcc -shared -fPIC -lpam -o jpam.so string.o challenge_gen.o jpam.o

.c.o:
	gcc -fPIC -o $@ -c $<
