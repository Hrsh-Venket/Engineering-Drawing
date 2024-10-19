CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = application
SOURCES = Application.cpp

# Include Eigen3. Use to fix path if necessary.
EIGEN3_INCLUDE_DIR = /usr/include/eigen3
CXXFLAGS += -I$(EIGEN3_INCLUDE_DIR)

all: $(TARGET)
	@echo "Running $(TARGET) with Example Input 1.txt..."
	./$(TARGET) < Input.txt

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) *.o

.PHONY: all clean
