#ifndef _ROBAZ_FILES
#define _ROBAZ_FILES

#include <stdio.h>

typedef enum status
{
  STATUS_OK = 0,
  STATUS_BUFFER_TOO_SMALL,
  STATUS_EOF,
  STATUS_ERROR,
} status_t;

#define file_unread(file, n)   (fseeko(file, -(n), SEEK_CUR) >= 0)
#define file_unread_char(file) file_unread(file, 1)

status_t file_readline(FILE *file, char *buffer, size_t buffer_size);

#endif
