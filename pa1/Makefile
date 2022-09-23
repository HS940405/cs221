EXETWODLINKEDLIST = pa1
OBJS  = PNG.o RGBAPixel.o lodepng.o pa1.o twodlinkedlist.o block.o

CXX = clang++
CXXFLAGS = -stdlib=libc++ -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -stdlib=libc++ -std=c++1y -lc++abi -lpthread -lm

all : pa1

$(EXETWODLINKEDLIST) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXETWODLINKEDLIST)

pa1.o : pa1.cpp twodlinkedlist.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) pa1.cpp

twodlinkedlist.o : twodlinkedlist.cpp twodlinkedlist.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion twodlinkedlist.cpp

block.o : block.cpp block.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXETWODLINKEDLIST)
