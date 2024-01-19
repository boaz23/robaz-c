#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "assert-utils.h"
#include "files.h"

/*
Guidelines:
* Must support empty lines with CR-LF line endings
* Must support consecutive CR characters
*/

status_t file_readline(
	FILE *file, size_t *nWritten,
	char *buffer, size_t bufferSize
) {
	assert((file != NULL) && (buffer != NULL) && (bufferSize > 0));

	status_t status;
	int c;
	char prev_c = '\0';
	char *p_next = buffer, *p_end = &buffer[bufferSize - 1];

	while (((c = fgetc(file)) >= 0) && (c != '\n') && (p_next < p_end)) {
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

		status = STATUS_OK;
		if (c == '\r') {
			c = fgetc(file);
			if (c == '\n') {
				goto end;
			}
			else if (c < 0) {
				unread_count = 1;
				if (!feof(file)) {
					status = STATUS_ERROR;
				}
			}
			else {
				unread_count = 2;
			}
		}
		else {
			unread_count = 1;
		}

		if (file_unread(file, unread_count)) {
			if (status != STATUS_ERROR) {
				status = STATUS_BUFFER_TOO_SMALL;
			}
		}
		else {
			status = STATUS_ERROR;
		}
	}

end:
	*p_next = '\0';
	*nWritten = (p_next - buffer);
	return status;
}
