TARGET = prog.e

FLAGS = -O2 -Wall -Werror -std=gnu++17 -c -o

OBJ = test.o test_runner.o

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) 

clean:
	rm -f $(OBJ)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET)
	
test.o: test.cpp test_runner.h serializer.hpp
	g++ $< $(FLAGS) $@

%.o: %.cpp %.h
	g++ $< $(FLAGS) $@
	
%.o: %.cpp 
	g++ $< $(FLAGS) $@ 
