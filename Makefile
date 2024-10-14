CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = application
SOURCES = Application.cpp

# Default target to build and run the application
all: $(TARGET)
	@echo "Running $(TARGET) with Example Input 1.txt..."
	./$(TARGET) < Example\ Input\ 1.txt

# Compile and link the target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) *.o

.PHONY: all clean
