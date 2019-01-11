#define _GNU_SOURCE
#include <stdio.h>

/*
 * Implementation-specific data.
 * Can be anything - passed to stdio functions as a void pointer.
 */
typedef struct COOKIE
{
    int unused;
} COOKIE;

void null_io(void)
{
    COOKIE impl_data = {0};

    // IO mode: r, w, a, r+, w+, and a+
    const char *mode = "r";
    /*
     *  typedef struct {
     *      cookie_read_function_t  *read;
     *      cookie_write_function_t *write;
     *      cookie_seek_function_t  *seek;
     *      cookie_close_function_t *close;
     *  } cookie_io_functions_t;
     */
    cookie_io_functions_t io_funcs = {
        .read = NULL,
        .write = NULL,
        .seek = NULL,
        .close = NULL,
    };

    // FILE *fopencookie(void *cookie, const char *mode, cookie_io_functions_t io_funcs);
    FILE *file = fopencookie((void *)&impl_data, mode, io_funcs);
    if (!file)
    {
        fprintf(stderr, "Failed to open\n");
        return;
    }

    char buffer[1024] = {0};
    ssize_t count = 0;

    // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    count = fread(buffer, sizeof(buffer[0]), sizeof(buffer), file);
    if (count == 0)
        fprintf(stderr, "Failed to read\n");

    // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    count = fwrite(buffer, sizeof(buffer[0]), sizeof(buffer), file);
    if (count == 0)
        fprintf(stderr, "Failed to write\n");

    int result = 0;

    // int fseek(FILE *stream, long offset, int whence);
    result = fseek(file, 0L, SEEK_SET);
    if (result == -1)
        fprintf(stderr, "Failed to seek\n");

    // int fclose(FILE *stream);
    result = fclose(file);
    if (result != 0)
        fprintf(stderr, "Failed to close\n");
}

int main(void)
{
    null_io();
    return 0;
}
