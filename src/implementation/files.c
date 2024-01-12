#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "assert-utils.h"
#include "files.h"

// Tests:
// buffer-size = 5
//
// '\n'
// '\r' '\n'
// a b c '\n'
// a b c '\r' '\n'
// a b c '\r' '\r' '\n'

/*
Guidelines:
* Must support empty lines with CR-LF line endings
* Must support consecutive CR characters
*/

status_t file_readline(FILE *file, char *buffer, size_t buffer_size)
{
	assert((file != NULL) && (buffer != NULL) && (buffer_size > 0));

	status_t status;
	int c;
	char prev_c = '\0';
	char *p_next = buffer, *p_end = &buffer[buffer_size - 1];

	while (((c = fgetc(file)) >= 0) && (c != '\n') && (p_next == p_end)) {
		// inv: p_next <= p_end
		prev_c = *p_next++ = (char)c;
	}

	if (c == '\n') {
		if (prev_c == '\r') {
			p_next--;
		}

		status = STATUS_OK;
	}
	else if (c < 0) {
		status = feof(file) ? STATUS_EOF : STATUS_ERROR;
	}
	else {
		assert((c >= 0) && (c != '\n'));
		assert(p_next == p_end);

		int unread_count;

		if (c == '\r') {
			c = fgetc(file);
			if (c == '\n') {
				status = STATUS_OK;
				goto end;
			}

			unread_count = 2;
		}
		else {
			unread_count = 1;
		}

		status = file_unread(file, unread_count) ?
			STATUS_BUFFER_TOO_SMALL :
			STATUS_ERROR;
	}

end:
	*p_next = '\0';
	return status;
}
