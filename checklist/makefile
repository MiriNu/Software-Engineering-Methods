ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = i686-w64-mingw32-g++
endif

OBJS = test.o

all: $(OBJS)
	$(CXX) $(OBJS) -o test.exe -static
clean:
	del *.o