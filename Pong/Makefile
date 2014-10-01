
# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -O -Wall -std=c++11
CXXFLAGS = -O -Wall -std=c++11

# OpenGL/Mesa libraries for Linux:
GL_LIBS = -lglut -lGLU -lGL -lm


#-----------------------------------------------------------------------

pong: Enums.h DrawableObject.o Net.o Wall.o Ball.o Paddle.o CollisionManager.o Pong.cpp
	$(LINK) $(CXXFLAGS) -o $@ $^ $(GL_LIBS)

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) -o $@ $@.c $(GL_LIBS)

.cpp:
	$(CXX) -o $@ $@.cpp $(GL_LIBS)

# utility targets
clean:
	rm -f *.o *~ core

