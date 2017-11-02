# while in the working drirectory run 'make -j -f Makefile'
#or simply just 'make'

CXX = g++
STD = c++14
CXXFLAGS = -Wall -Wextra -O2 -std=$(STD)
LFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lGL

OBJ=platformer_main.o

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

platformer.out: $(OBJ)
	$(CXX) -o $@ $^ $(LFLAGS)
