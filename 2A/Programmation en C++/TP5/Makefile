CXX = g++
CXXFLAGS = -W -Wall --std=c++11 -pedantic

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
DEPS = $(wildcard include/*.h)

TARGET = build/test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
