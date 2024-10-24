CFLAGS = -o ceandefender 

all: ceandefender

ceandefender: src/main.c
	gcc $(CFLAGS) src/main.c

windows_format: ceandefender
	./ceandefender > output.txt
	unix2dos output.txt

clean:
	rm -f ceandefender output.txt
