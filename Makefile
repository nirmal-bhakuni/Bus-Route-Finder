CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BACKEND_DIR = backend_c
TESTS_DIR = tests
DATA_DIR = data

# Source and object files
BACKEND_SRCS = $(wildcard $(BACKEND_DIR)/*.c)
BACKEND_OBJS = $(BACKEND_SRCS:.c=.o)
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_BINS = $(TEST_SRCS:.c=.exe)

# Dependency files
DEPS = $(BACKEND_OBJS:.o=.d)

# Main program executable
TARGET = bus_finder.exe

# Default target
all: dirs $(TARGET) tests

# Create necessary directories
dirs:
	if not exist "$(DATA_DIR)" mkdir "$(DATA_DIR)"

# Build main program
$(TARGET): $(BACKEND_OBJS)
	$(CC) $(BACKEND_OBJS) -o $(TARGET)

# Compile backend source files into objects with dependency generation
$(BACKEND_DIR)/%.o: $(BACKEND_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Build all test executables
tests: $(TEST_BINS)

# Compile each test executable
$(TESTS_DIR)/%.exe: $(TESTS_DIR)/%.c $(filter-out $(BACKEND_DIR)/main.o,$(BACKEND_OBJS))
	$(CC) $(CFLAGS) $^ -o $@ -I$(BACKEND_DIR)

# Run main program
run: $(TARGET)
	.\$(TARGET)

# Run all tests sequentially, stop if any fails
test: tests
	@for %%f in ($(TESTS_DIR)\*.exe) do ( \
		echo Running %%f ... && \
		%%f || exit /b 1 \
	)

# Clean all build artifacts and dependency files
clean:
	del /F /Q $(BACKEND_DIR)\*.o $(BACKEND_DIR)\*.d $(TARGET) $(TESTS_DIR)\*.exe

.PHONY: all clean run test tests dirs
