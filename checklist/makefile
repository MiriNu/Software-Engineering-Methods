main.o: main.cpp
	g++ -c main.cpp -o main.o -static
checkbox.o: checkbox.cpp checkbox.h
	g++ -c checkbox.cpp -I. -o checkbox.o -static
checklist.o: checklist.cpp checklist.h
	g++ -c checklist.cpp -I. -o checklist.o -static
all: main.o checkbox.o checklist.o
	g++ main.o checkbox.o checklist.o -o main.exe -static
clean:
	del *.o main.exe