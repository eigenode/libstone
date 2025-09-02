# Project settings
LIB_NAME = libstone
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I$(LIB_NAME)/include
AR = ar
ARFLAGS = rcs

# Source files
SRC = $(wildcard $(LIB_NAME)/src/*.c)
OBJ = $(SRC:.c=.o)

# Test files
TEST_SRC = $(wildcard $(LIB_NAME)/tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Example programs
EXAMPLES_SRC = $(wildcard $(LIB_NAME)/examples/*.c)
EXAMPLES_BIN = $(EXAMPLES_SRC:.c=)

# Doxygen
DOXYGEN = doxygen
DOXYFILE = Doxyfile

# Default target
all: $(LIB_NAME).a examples

# Build static library
$(LIB_NAME).a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Build example programs
examples: $(EXAMPLES_BIN)

%: %.c $(LIB_NAME).a
	$(CC) $(CFLAGS) $< -L. -lstone -o $@.out

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: $(TEST_OBJ) $(LIB_NAME).a
	echo "Test files are: ${TEST_OBJ}"
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lstone -o test_runner
	./test_runner

# Generate documentation
docs:
	$(DOXYGEN) $(DOXYFILE)

# Clean build files
clean:
	rm -f ${LIB_NAME}/src/*.o ${LIB_NAME}/tests/*.o ${LIB_NAME}/examples/*.out test_runner $(LIB_NAME).a
	rm -rf docs/html

.PHONY: all clean test examples docs

