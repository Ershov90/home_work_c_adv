all: prog

prog: main.o 
	gcc -o prog main.c  -lncurses -DNCURSES_STATIC

main.o: main.c
	gcc -c -o main.o main.c -lncurses -DNCURSES_STATIC 

clean:
	del *.o prog.exe