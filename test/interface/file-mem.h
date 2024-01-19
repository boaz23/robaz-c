#ifndef _ROBAZ_TESTS_FILE_MEM
#define _ROBAZ_TESTS_FILE_MEM

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct {
	char *buffer;
	size_t maxBufferSize;
	size_t idxWrite;
	size_t idxRead;
	int error;
} fileMem_t;

void fileMem_init(fileMem_t *file, size_t maxBufferSize);
void fileMem_free(fileMem_t *file);

size_t fileMem_writef_append(fileMem_t *file, const char *fmt, ...);
size_t fileMem_writef_appendv(fileMem_t *file, const char *fmt, va_list ap);

static inline void fileMem_reset(fileMem_t *file) {
	assert(file != NULL);

	file->idxWrite = 0;
	file->idxRead = 0;
	file->error = 0;
}

static inline void fileMem_setError(fileMem_t *file, int error) {
	assert(file != NULL);

	file->error = error;
}

static inline void fileMem_setReadIndex(fileMem_t *file, size_t idxRead) {
	assert((file != NULL) && (idxRead < file->maxBufferSize));

	file->idxRead = idxRead;
}

int fileMem_getc(fileMem_t *file);
int fileMem_seeko(fileMem_t *file, off_t offset, int whence);

static inline int fileMem_eof(fileMem_t *file) {
	assert(file != NULL);

	return file->error == EOF;
}

#endif
