# Project settings
LIB_NAME = libstone
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
AR = ar
ARFLAGS = rcs

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)
EXAMPLES = $(wildcard examples/*.c)

DOXYGEN = doxygen
DOXYFILE = Doxyfile

# Default target
all: $(LIB_NAME).a examples

# Build static library
$(LIB_NAME).a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Build example programs
examples: $(EXAMPLES:.c=)
%: %.c $(LIB_NAME).a
	$(CC) $(CFLAGS) $< -L. -lstone -o $@

# Run tests
test: $(TEST_OBJ) $(LIB_NAME).a
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lstone -o test_runner
	./test_runner

# Generate documentation
docs:
	$(DOXYGEN) $(DOXYFILE)

# Clean build files
clean:
	rm -f src/*.o tests/*.o examples/* test_runner $(LIB_NAME).a
	rm -rf docs/html

.PHONY: all clean test examples docs

