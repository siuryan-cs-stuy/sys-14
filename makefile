all: control.c
	gcc -o control control.c

run: all
	./control

clean:
	rm control
	rm *.o
	rm *~

