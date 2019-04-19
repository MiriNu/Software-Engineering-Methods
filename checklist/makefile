ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = i686-w64-mingw32-g++
endif

OBJS = main.o checkbox.o checklist.o 
main.o: main.cpp
	$(CXX) -c main.cpp -o main.o
checkbox.o: checkbox.cpp checkbox.h
	$(CXX) -c checkbox.cpp -I. -o checkbox.o	
checklist.o: checklist.cpp checklist.h
	$(CXX) -c checklist.cpp -I. -o checklist.o		

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static
clean:
	del *.o main.exe