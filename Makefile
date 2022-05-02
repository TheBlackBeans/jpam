all: jpam.so

jpam.so: jpam.o
	gcc -shared -lpam -o jpam.so jpam.o

jpam.o: src/jpam.c
	gcc -fPIC -o jpam.o -c src/jpam.c

