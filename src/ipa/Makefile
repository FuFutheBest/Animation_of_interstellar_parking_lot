CCC = g++
CCFLAGS = -Werror -pedantic -Wall -Wextra -Wvla -Wno-unused-result -Wconversion -std=c++17
SRC = *.cpp

ifeq ($(OS),Windows_NT)
	# Windows
	LIB = -lglu32 -lfreeglut -lopengl32
else
	# Others
	OS := $(shell uname)
	ifeq ($(OS),Linux)
		# Linux
		LIB = -lglut -lGL -lGLU
	endif
	ifeq ($(OS),Darwin)
		# Mac
		LIB = -framework OpenGL -framework GLUT
	endif
endif

.PHONY: all clean

all: ipa

ipa:
	$(CCC) $(CCFLAGS) -o ipa $(SRC) $(LIB)

clean:
	$(RM) *.o *.a *~ ipa
