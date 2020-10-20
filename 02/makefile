TARGET = prog.e

FLAGS = -O2 -Wall -Werror -std=gnu++17 -lm -c -o

OBJ = test_runner.o TokenParser.o test.o

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) 

clean:
	rm -f $(OBJ)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET)
	
test.o: test.cpp test_runner.h TokenParser.h
	g++ $< $(FLAGS) $@

%.o: %.cpp %.h
	g++ $< $(FLAGS) $@
	
%.o: %.cpp 
	g++ $< $(FLAGS) $@ 
