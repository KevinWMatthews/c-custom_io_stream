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
