CCC = g++
CCFLAGS = -Werror -pedantic -Wall -Wextra -Wvla -Wno-unused-result -Wconversion -std=c++17
SRC = *.cpp

.PHONY: all clean

all: pms

pms:
	$(CCC) $(CCFLAGS) $(SRC) -o pms

clean:
	$(RM) *.o *.a *~ pms
