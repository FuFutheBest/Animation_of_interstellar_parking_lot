# used to compile outside of the src directory
CCC = g++                                       
CCFLAGS = -Werror -pedantic -Wall -Wextra -Wvla -std=c++17 -Wno-unused-result -Wconversion  
LIBS = -lglut -lGL                                
SRC = $(wildcard src/*.cpp)                       
OBJ = $(SRC:src/%.cpp=src/%.o)                    
TARGET = parklot                                  

.PHONY: clean hlibs

all: $(TARGET)
	@echo Parking lot successfully constructed 

$(TARGET): $(OBJ)
	@$(CCC) $(CCFLAGS) -o $(TARGET) $(OBJ) $(LIBS)  

src/%.o: src/%.cpp
	@$(CCC) $(CCFLAGS) -c $< -o $@  

clean:
	@$(RM) src/*.o *.a *~ $(TARGET)  
	@echo Parking lot successfully cleaned  

# CCC = g++
# CCFLAGS = -Werror -pedantic -Wall -Wextra -Wvla -std=c++17 -Wno-unused-result -Wconversion
# LIBS = -lglut -lGL
# SRC = $(wildcard *.cpp)
# OBJ = $(SRC:.cpp=.o)
# TARGET = parklot

# .PHONY: clean hlibs

# all: $(TARGET)
# 	@echo Parking lot successfully constructed

# $(TARGET): $(OBJ)
# 	$(CCC) $(CCFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

# .cpp.o:
# 	$(CCC) $(CCFLAGS) -c $< -o $@

# clean:
# 	$(RM) *.o *.a *~ $(TARGET)
# 	@echo Parking lot successfully cleaned

