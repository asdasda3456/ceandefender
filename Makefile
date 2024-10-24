CFLAGS = -o ceandefender 

all: ceandefender

ceandefender: src/main.c
	gcc $(CFLAGS) src/main.c
	gcc -o ceanbth ceanbth.c	
