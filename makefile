CXX=g++
CXXFLAGS=-Wall -I. -std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
TARGET=game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)