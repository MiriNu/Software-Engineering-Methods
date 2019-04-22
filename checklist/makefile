ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = checkbox.o main.o checklist.o

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static
clean: rm -f *.o