_This project has been created as part of the 42 curriculum by mbuchet._

## Description
**get_next_line** is a utility function that retrieves the next line on each new call.
Its goal is to better understand:
- learn the 'read' function in C
- a project with a huge potential for memory leak
- learn to truly understand the power of pointers

Reference:
- https://man7.org/linux/man-pages/man2/read.2.html

## Instructions

### Build
From the root of the repository, run:
- `make`

This generates:
- `get_next_line.a`

### How to compile

- `make` → compile the project and generate `get_next_line.a`
- `make all` → same as `make`
- `make clean` → remove object files (`.o`)
- `make fclean` → remove object files and the library (`get_next_line.a`)
- `make re` → fully rebuild the project (fclean + all)


Tested on **Ubuntu** (42 Brussels environment and WSL from Windows 11).

### Usage

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

## Algorithm and data structure (explanation + justification)

### Algorithm (Parsing / Dispatch)

The function initializes a structure called `t_buffer`, which contains:

* `content`: the buffer holding data for the next function call
* `size`: the current size of the stored content
* `current_read`: the current write position within the buffer

An infinite loop is used to extract the first line using `extract_line`.
Inside this function, memory is pre-allocated up to the next `\n`. If possible, data is written into `buf.content` using `buffer_realloc_head`, which dynamically expands the buffer when needed.

At this point, the function determines the length of the line and allocates the required memory for it.

The loop then continues and calls `current_read_line`, which reads `BUFFER_SIZE` bytes at a time into `buf.content`.

If the end of the file is reached or an error occurs, the entire buffer is freed using `free_buf`.

**Why this approach?**
- If I ever want to support multiple file descriptors, it will be easy to extend.
- The code is clean, readable, and lightweight. I avoid relying too much on libft functions and instead implement new ones tailored for optimized behavior specific to this function.

### Data structures
The function initializes a structure called `t_buffer`, which contains:

* `content`: the buffer holding data for the next function call
* `size`: the current size of the stored content
* `current_read`: the current write position within the buffer

The main function only keeps the extracted line and returns it as the current line.

## How it works (overview)

### Main Functions

* `char *get_next_line(int fd)`: main function
* `static char *extract_line(t_buffer *buf)`: extracts the target line
* `static ssize_t current_read_line(t_buffer *buf, int fd)`: reads the current line

### Utility Functions

* `void ft_strlcpy(char *dst, const char *src, size_t dsize)`: safely copies a string from `src` to `dst`
* `void free_buf(t_buffer *buf)`: frees all memory contained in `buf`
* `void buffer_realloc_head(t_buffer *buf, size_t new_size)`: reallocates and expands the buffer memory when needed

## Resources (references + AI usage)

### References
- 42 subject PDF (get_next_line, version 12.1, 42 Brussels)
- `read` manual: https://man7.org/linux/man-pages/man2/read.2.html

### AI usage
AI was used to help identify certain memory leaks and to improve my ability to detect them later.
This README was translated from French to English.
