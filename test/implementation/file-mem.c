#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "assert-utils.h"
#include "file-mem.h"

void fileMem_init(fileMem_t *file, size_t maxBufferSize)
{
	fileMem_reset(file);
	file->buffer = malloc(maxBufferSize);
	file->maxBufferSize = maxBufferSize;
}

void fileMem_free(fileMem_t *file) {
	free(file->buffer);
}

size_t fileMem_writef_append(fileMem_t *file, const char *fmt, ...)
{
	assert((file != NULL) && (fmt != NULL));

	va_list ap;
	va_start(ap, fmt);

	size_t nWritten = fileMem_writef_appendv(file, fmt, ap);

	va_end(ap);
	return nWritten;
}

size_t fileMem_writef_appendv(fileMem_t *file, const char *fmt, va_list ap) {
	assert((file != NULL) && (fmt != NULL));

	size_t maxWriteSize = (file->maxBufferSize - file->idxWrite);
	int nWritten = vsnprintf(
		&file->buffer[file->idxWrite],
		maxWriteSize, fmt, ap
	);
	assert(
		(0 <= nWritten) &&
		((size_t)nWritten < maxWriteSize) &&
		(file->idxWrite <= SIZE_MAX - nWritten)
	);

	file->idxWrite += nWritten;
	return (size_t)nWritten;
}

int fileMem_getc(fileMem_t *file) {
	assert(file != NULL);

	if ((file->error == 0) && (file->idxRead >= file->idxWrite)) {
		file->error = EOF;
	}
	if (file->error != 0) {
		return file->error;
	}

	return file->buffer[file->idxRead++];
}

int fileMem_seeko(fileMem_t *file, off_t offset, int whence) {
	assert(file != NULL);

	size_t base;

	switch (whence) {
		case SEEK_SET:
			base = 0;
			break;
		
		case SEEK_CUR:
			base = file->idxRead;
			break;

		case SEEK_END:
			base = file->idxWrite;
			break;

		default:
			fail_msg("Invalid seek whence value %u", whence);
			break;
	}

	if ((offset < 0) && (-((off_t)base) > offset)) {
		// The result offset would be negative
		return EINVAL;
	}

	file->idxRead = base + offset;
	return 0;
}
