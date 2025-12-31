# C Preprocessor Implementation

A simple C-based preprocessor for handling `#define` and `#undef` directives.

## Features
- Process `#define` directives for macro definitions
- Process `#undef` directives to remove definitions
- Replace macro identifiers with their definitions
- Hash table implementation for efficient storage

## Build and Run
```bash
# Compile
gcc -o preprocessor preprocessor.c

# Usage
./preprocessor < input.txt
```

## Example
Input:
```c
#define MAX 100
Value is MAX
#undef MAX
Value is MAX
```

Output:
```
Value is 100
Value is MAX
```

## Implementation Details
- Hash table with 101 buckets
- Separate chaining for collision resolution
- Dynamic memory allocation for strings
- Handles identifiers with characters: [a-zA-Z0-9_]

## Limitations
1. No parameterized macros
2. No conditional compilation (#ifdef, #ifndef)
3. No file inclusion (#include)
4. Macro replacement only on same line

## Project Structure
```
.
├── preprocessor.c    # Main implementation
├── input.c           # Input handling
├── output.c          # Output functions
└── preprocessor      # Executable
```

## Development Status
Educational project. Basic functionality implemented.
