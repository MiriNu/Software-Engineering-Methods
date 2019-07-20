CXX = i686-w64-mingw32-g++
CPPFLAGS = -std=c++1z -static -g
OBJS += Common/Control.o Common/EventEngine.o Common/Graphics.o FinalProject/Source.o Controls/Label.o Controls/textbox.o Common/Border/NullBorder.o Common/Border/SingleBorder.o Common/Border/Border.o

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o final.exe
clean:
	rm -f $(OBJS)
	rm -f *.exe


