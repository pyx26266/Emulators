CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++2a

SRCS := main.cxx chip8_soc.cxx

BUILD_DIR ?= ./build

OBJS := $(SRCS:$(BUILD_DIR)/%.cxx=$(BUILD_DIR)/%.o)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

EXECUTABLE := $(BUILD_DIR)/chip8

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

# Compile each source file into an object file
$(BUILD_DIR)/%.o: %.cxx | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files to create the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -w -lSDL2 -o $@

# Clean up intermediate files
clean:
	rm -rf $(BUILD_DIR)