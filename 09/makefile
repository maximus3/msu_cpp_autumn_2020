TARGET = prog.e

FLAGS = -O2 -Wall -Werror -std=gnu++17 -c -o 

OBJ = test.o test_runner.o binsort.o

all: $(TARGET)

test: $(TARGET)
	./$(TARGET) 

clean:
	rm -f $(OBJ)

$(TARGET): $(OBJ)
	g++ $(OBJ) -pthread -o $(TARGET)
	
test.o: test.cpp test_runner.h
	g++ $< $(FLAGS) $@

%.o: %.cpp %.h
	g++ $< $(FLAGS) $@
	
%.o: %.cpp 
	g++ $< $(FLAGS) $@ 
