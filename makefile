main.exe: activity.o heap.o menu.o main.o
	gcc activity.o heap.o menu.o main.o -o main.exe

activity.o: activity.c activity.h
	gcc -c activity.c
	
heap.o: heap.c heap.h activity.h
	gcc -c heap.c

menu.o: menu.c menu.h
	gcc -c menu.c

main.o: main.c heap.h activity.h menu.h
	gcc -c main.c

clean:
	del /Q *.o main.exe 2>nul