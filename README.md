# Custom FILE Streams

Create custom `FILE` objects for use with C stdio functions.

## Background

`FILE` IO requries five functions:

  * open
  * close
  * read
  * write
  * seek

GNU provides an extension that allows us to create custom `FILE` types:
` fopencookie`. If we provide this function with pointers to the other four
`FILE` IO functions (read, write, seek, close), we have complete IO.

## Documentation

Official docs at man7.org (Linux, not POSIX):

  * [fopencookie](http://man7.org/linux/man-pages/man3/fopencookie.3.html)
  * [fclose](http://man7.org/linux/man-pages/man3/fclose.3.html)
  * [fread](http://man7.org/linux/man-pages/man3/fread.3.html)
  * [fwrite](http://man7.org/linux/man-pages/man3/fwrite.3.html)
  * [fseek](http://man7.org/linux/man-pages/man3/fseek.3.html)

C file IO docs on cppreference:

  * [fopen](https://en.cppreference.com/w/c/io/fopen)
  * [fclose](https://en.cppreference.com/w/c/io/fclose)
  * [fread](https://en.cppreference.com/w/c/io/fread)
  * [fwrite](https://en.cppreference.com/w/c/io/fwrite)
  * [fseek](https://en.cppreference.com/w/c/io/fseek)
