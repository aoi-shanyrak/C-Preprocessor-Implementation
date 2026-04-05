# C Preprocessor Implementation

A simple C-based preprocessor for handling `#define` and `#undef` directives.

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

## Limitations
1. No parameterized macros
2. No conditional compilation (#ifdef, #ifndef)
3. No file inclusion (#include)
4. Macro replacement only on same line
