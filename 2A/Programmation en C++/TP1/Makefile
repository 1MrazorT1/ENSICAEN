CXX = g++
CXXFLAGS = -W -Wall --std=c++11 -pedantic

SRC = src/*.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = include/*.h

TARGET = build/livres.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean