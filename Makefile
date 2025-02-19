# Compiler and flags
CXX = g++
CXXFLAGS = -m64 -Wall -Wextra -Wpedantic -O2 -Iinclude

# Source files (only include existing ones)
SRC = src/main.cpp src/bitboard.cpp src/attacks.cpp src/lookup.cpp src/utilities.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)

# Output binary
TARGET = build/chess_engine

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ)
	@echo "Linking: $(TARGET)"
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Compilation step
build/%.o: src/%.cpp
	@mkdir -p build
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build directory
clean:
	rm -rf build
	@echo "Cleaned build directory."

# Run the chess engine
run: all
	@echo "Running chess engine..."
	./build/chess_engine
