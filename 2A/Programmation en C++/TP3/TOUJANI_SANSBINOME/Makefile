CXX = g++
CXXFLAGS = -W -Wall --std=c++11 -pedantic -fno-elide-constructors

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
DEPS = $(wildcard include/*.h)

TARGET = build/matrice

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
