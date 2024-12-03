# Filter Program - Instructions

## Authorized Functions

- `read`
- `strlen`
- `malloc`
- `calloc`
- `realloc`
- `free`
- `printf`
- `perror`

## Task

Write a program that will take one and only one argument "s".  
Your program will read from `stdin` and write all the content read to `stdout` except that every occurrence of `s` must be replaced by `"*"` (as many as the length of `s`).

### Example

```bash
./filter bonjour
```

will behave the same as:

```bash
sed 's/bonjour/*******/g'
```

### General Behavior

More generally, your program must be equivalent to the shell script `filter.sh` (given in the folder).

## Error Handling

- In case of an error during a `read` or a `malloc`, you must write `"Error: "` followed by the error message to `stdout` and return `1`.

- If the program is called with no arguments, multiple arguments, or an empty argument, it must return `1`.
