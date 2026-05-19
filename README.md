_This project has been created as part of the 42 curriculum by mbuchet._

## Description

**get_next_line** is a utility function that retrieves the next line on each new call.

Its goal is to better understand:

- the `read` function in C
- memory management and leak prevention
- the power of pointers

Reference:

- https://man7.org/linux/man-pages/man2/read.2.html

---

## Compilation

Compile the project with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

This generates the executable with the chosen `BUFFER_SIZE`.

Tested on **Ubuntu** (42 Brussels environment and WSL on Windows 11).

---

## Usage

Example of how to use `get_next_line`:

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Algorithm and Data Structure

### Algorithm

The function initializes a structure called `t_buffer`, which contains:

* `content`: buffer holding stored data
* `size`: current size of the stored content
* `current_read`: current position inside the buffer

An internal loop extracts the next line using `extract_line`.

Memory is dynamically expanded using `buffer_realloc_head` whenever additional space is needed. The function then allocates enough memory for the extracted line and returns it.

Reading is performed through `current_read_line`, which reads `BUFFER_SIZE` bytes at a time.

If EOF or an error occurs, allocated memory is cleaned using `free_buf`.

The remaining data after a newline is moved at the beginning of the buffer using `fill_buffer`.

When the file reaches EOF without a trailing newline, the remaining content is returned through `get_next_line_end`.

### Why this approach?

* Easy to extend for multiple file descriptors
* Lightweight and readable implementation
* Custom utility functions optimized specifically for this project

---

## Main Functions

### Core Functions

* `char *get_next_line(int fd)`
  Main function that reads and returns the next line from a file descriptor.

* `static char *extract_line(t_buffer *buf)`
  Searches for a newline in the buffer, allocates memory for the line, and extracts it.

* `static ssize_t current_read_line(t_buffer *buf, int fd)`
  Reads `BUFFER_SIZE` bytes from the file descriptor and appends them to the buffer.

* `static char *get_next_line_end(t_buffer *buf, char *line)`
  Handles the end of the file and returns the remaining content if no newline is left.

* `static void fill_buffer(t_buffer *buf, size_t new_size)`
  Shifts the remaining unread content to the beginning of the buffer after a line extraction.

### Utility Functions

* `void ft_strlcpy(char *dst, const char *src, size_t dsize)`
  Safely copies a string from `src` to `dst`.

* `void free_buf(t_buffer *buf)`
  Frees the allocated memory inside the buffer structure.

* `void buffer_realloc_head(t_buffer *buf, size_t new_size)`
  Reallocates and expands the buffer memory when additional space is required.

---

## Buffer Structure

```c
typedef struct s_buffer
{
    char    *content;
    size_t  size;
    size_t  current_read;
}   t_buffer;
```

### Structure Fields

* `content` → stores buffered data between function calls
* `size` → current amount of stored data
* `current_read` → current reading index inside the buffer

---

## Resources

### References

* 42 subject PDF (`get_next_line`, version 12.1)
* `read` manual: [https://man7.org/linux/man-pages/man2/read.2.html](https://man7.org/linux/man-pages/man2/read.2.html)

### AI Usage

AI was used to help identify memory leaks and improve debugging skills.
This README was translated from French to English.
