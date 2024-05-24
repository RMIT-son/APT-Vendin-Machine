# Variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++14 -O
TARGET = ftt
SOURCES = $(wildcard ./code/*.cpp)

# Default target
all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean target
clean:
	rm -f $(TARGET)