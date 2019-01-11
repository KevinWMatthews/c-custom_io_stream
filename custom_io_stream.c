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

// cookie_read_function_t *read:
// ssize_t read(void *cookie, char *buf, size_t size);
// The read function should return:
// the number of bytes copied into buf,
// 0 on end of file,
// or -1 on error
ssize_t custom_read(void *cookie, char *buf, size_t size)
{
    fprintf(stdout, "Entering: %s\n", __func__);
    fprintf(stdout, "Exiting: %s\n", __func__);
    return size;
}

// cookie_write_function_t *write:
// ssize_t write(void *cookie, const char *buf, size_t size);
// The write function should return:
// the number of bytes copied from buf,
// or 0 on error.
ssize_t custom_write(void *cookie, const char *buf, size_t size)
{
    fprintf(stdout, "Entering: %s\n", __func__);
    fprintf(stdout, "Exiting: %s\n", __func__);
    return size;
}

// cookie_seek_function_t *seek:
// int seek(void *cookie, off64_t *offset, int whence);
// whence will be one of:
// SEEK_SET
// SEEK_CUR
// SEEK_END
// The seek function should return:
// 0 on success,
// and -1 on error
int custom_seek(void *cookie, off64_t *offset, int whence)
{
    fprintf(stdout, "Entering: %s\n", __func__);
    fprintf(stdout, "Exiting: %s\n", __func__);
    return 0;
}

// cookie_close_function_t *closefclose(file)
// int close(void *cookie);
// The close function should return:
// 0 on success,
// and EOF on error.
int custom_close(void *cookie)
{
    fprintf(stdout, "Entering: %s\n", __func__);
    fprintf(stdout, "Exiting: %s\n", __func__);
    return 0;
}

int main(void)
{
    COOKIE impl_data = {0};

    // IO mode: r, w, a, r+, w+, and a+
    const char *mode = "w+";
    /*
     *  typedef struct {
     *      cookie_read_function_t  *read;
     *      cookie_write_function_t *write;
     *      cookie_seek_function_t  *seek;
     *      cookie_close_function_t *close;
     *  } cookie_io_functions_t;
     */
     cookie_io_functions_t io_funcs = {
         .read = custom_read,
         .write = custom_write,
         .seek = custom_seek,
         .close = custom_close,
     };

    // FILE *fopencookie(void *cookie, const char *mode, cookie_io_functions_t io_funcs);
    FILE *file = fopencookie((void *)&impl_data, mode, io_funcs);
    if (!file)
    {
        fprintf(stderr, "Failed to open\n");
        return -1;
    }

    char buffer[1024] = {0};
    ssize_t count = 0;
    int result = 0;

    fprintf(stdout, "\nReading:\n");
    // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    count = fread(buffer, sizeof(buffer[0]), sizeof(buffer), file);
    if (count != sizeof(buffer))
        fprintf(stderr, "Failed to read\n");

    fprintf(stdout, "\nSeeking:\n");
    // int fseek(FILE *stream, long offset, int whence);
    result = fseek(file, 0L, SEEK_SET);
    if (result == -1)
        fprintf(stderr, "Failed to seek\n");

    fprintf(stdout, "\nWriting:\n");
    // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    count = fwrite(buffer, sizeof(buffer[0]), sizeof(buffer), file);
    if (count != sizeof(buffer))
        fprintf(stderr, "Failed to write\n");
    else
        fprintf(stdout, "Wrote n bytes: %zd\n", count);

    fprintf(stdout, "\nFlushing:\n");
    // int fflush(FILE *stream);
    result = fflush(file);
    if (result != 0)
        fprintf(stderr, "Failed to flush\n");

    fprintf(stdout, "\nClosing:\n");
    // int fclose(FILE *stream);
    result = fclose(file);
    if (result != 0)
        fprintf(stderr, "Failed to close\n");

    return 0;
}
