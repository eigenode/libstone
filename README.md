# libstone
Efficient C library for fast and scalable data structures.

## Requirements
To build and use libstone, you need:

- **C compiler** (GCC, Clang, or compatible)
- **Make** (for building the library and examples)
- **Doxygen** (optional, for generating documentation)
- Linux, macOS, or Windows (with compatible build tools)

On Ubuntu/Debian, you can install the necessary tools with:

```bash
sudo apt-get update
sudo apt-get install build-essential make doxygen graphviz
```

---

## Building the Library

Clone the repository:

```bash
git clone https://github.com/<your-username>/libstone.git
cd libstone
```

### Build the static library
```bash
make libstone.a
```
This will compile the source files and create `libstone.a` in the root directory.

### Build the library and example programs
```bash
make
```
This will build both `libstone.a` and all example programs in the `examples/` folder.

### Run tests
```bash
make test
```
This will compile and run all tests located in the `tests/` folder.

### Clean build files
```bash
make clean
```
Removes object files, the library, examples, and test binaries.

---

## Using libstone in Your Project

Include headers from `include/stone/`:

```c
#include <stone/skiplist.h>
#include <stone/minsketch.h>
```

Link your program with the static library:

```bash
gcc main.c -L. -lstone -o myprogram
```

---

## Generating Documentation (Optional)

If you have Doxygen installed, you can generate HTML documentation:

```bash
make docs
```

Then open `docs/html/index.html` in your browser.

---

## Quick Example

```c
#include <stdio.h>
#include <stone/skiplist.h>

int main() {
    printf("Cooming Soon!");
    return 0;
}
```

Compile with:

```bash
gcc example.c -L. -lstone -o example
./example
```

