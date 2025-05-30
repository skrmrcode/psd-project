all: main.exe run_test_suite.exe

main.exe: activity.o heap.o menu.o main.o utils.o
	gcc activity.o heap.o menu.o main.o utils.o -o main.exe

run_test_suite.exe: activity.o heap.o menu.o test.o utils.o
	gcc activity.o heap.o menu.o test.o utils.o -o run_test_suite.exe

activity.o: activity.c activity.h
	gcc -c activity.c
	
heap.o: heap.c heap.h activity.h
	gcc -c heap.c

menu.o: menu.c menu.h utils.h
	gcc -c menu.c

utils.o: utils.c utils.h
	gcc -c utils.c

main.o: main.c heap.h activity.h menu.h
	gcc -c main.c

test.o: test.c test.h
	gcc -c test.c

clean:
	del /Q *.o run_test_suite.exe main.exe report.txt report_test.txt result.txt 2>nul
