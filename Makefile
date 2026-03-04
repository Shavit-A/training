GCC = gcc

GCCFLAGS = -Wall -g

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

SRCS = server.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Default rule to build the executable
all: $(TARGET)

# ensure build directory exists before building anything
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to link object files into target executable
# make the build directory an order-only prerequisite so it exists
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(GCC) $(GCCFLAGS) -o $(TARGET) $(OBJS)

#Rule to compile .c files into .o files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(GCC) $(GCCFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Clean rule to remove generated files
clean:
	 rm -rf $(BUILD_DIR)