#include <unistd.h>
#include <stdarg.h>
#include "tests-common.h"
#include "files.h"
#include "file-mem.h"
#include "math-ext.h"

static fileMem_t fileStub;
#define FILE_STUB_SIZE 256U

declare_real_func(fgetc);
declare_real_func(fseeko);
declare_real_func(feof);

int wrap_func(fgetc)(FILE *file) {
	return fileMem_getc((fileMem_t *)file);
}

int wrap_func(fseeko)(FILE *file, off_t offset, int whence) {
	return fileMem_seeko((fileMem_t *)file, offset, whence);
}

int wrap_func(feof)(FILE *file) {
	return fileMem_eof((fileMem_t *)file);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static void print_char_array(const char *buffer, const char *buffer_end) {
#pragma GCC diagnostic pop
#define printf printfe
	if (buffer == buffer_end) {
		printf("<collapsed buffer>");
	}
	else if (buffer[0] == '\0')
	{
		printf("<empty>");
	}
	else
	{
		for (const char *pc = buffer; (pc < buffer_end) && *pc; pc++)
		{
			unsigned char c = *(unsigned char *)pc;
			if (c == '\n')
			{
				printf("\\n");
			}
			else if (c == '\r')
			{
				printf("\\r");
			}
			else if (c == '\t')
			{
				printf("\\t");
			}
			else if ((0x20 <= c) && (c < 0x80))
			{
				printf("'%c'", c);
			}
			else
			{
				printf("0x%02X", c);
			}

			printf(" ");
		}
	}

	printf("\n");
#undef printf
}

TEST_GROUP(file_readline);
TEST_SETUP(file_readline) {
	fileMem_reset(&fileStub);
}

TEST_TEAR_DOWN(file_readline) {
}

void test_file_readline_singleLine(
	size_t bufferSize,
	status_t expected_status,
	const char *fmt, const char *lineEnd, ...
) {
	assert(bufferSize > 0);

	va_list ap;
	va_start(ap, lineEnd);

	size_t lineLength = fileMem_writef_appendv(&fileStub, fmt, ap);
	size_t lineEndingLength = fileMem_writef_append(&fileStub, lineEnd);

	size_t nWritten;
	char buffer[bufferSize];
	status_t status = file_readline(
		(FILE *)&fileStub, &nWritten,
		buffer, bufferSize
	);

	size_t expected_nWritten;
	size_t expected_idxRead;
	if (lineLength < bufferSize) {
		expected_nWritten = lineLength;
		expected_idxRead = lineLength + lineEndingLength;
	}
	else {
		expected_idxRead = expected_nWritten = bufferSize - 1;
	}

	TEST_ASSERT_EQUAL(expected_status, status);
	TEST_ASSERT_EQUAL_size_t(expected_nWritten, nWritten);
	TEST_ASSERT_EQUAL_size_t(expected_idxRead, fileStub.idxRead);
	if (expected_nWritten > 0) {
		TEST_ASSERT_EQUAL_CHAR_ARRAY(fileStub.buffer, buffer, expected_nWritten);
	}

	va_end(ap);
}

#define define_file_readline_test_singleLine(funcName, bufferSize, expected_status, fmt, lineEnd, ...)\
	TEST(file_readline, funcName) {\
		test_file_readline_singleLine(bufferSize, expected_status, fmt, lineEnd, ##__VA_ARGS__);\
	}

define_file_readline_test_singleLine(emptyLine_noLineEnd, 1, STATUS_EOF, "", "")
define_file_readline_test_singleLine(emptyLine_lf, 1, STATUS_OK, "", "\n")
define_file_readline_test_singleLine(emptyLine_crlf, 1, STATUS_OK, "", "\r\n")
define_file_readline_test_singleLine(something_noLineEnd, 5, STATUS_EOF, "abc", "")
define_file_readline_test_singleLine(something_lf, 5, STATUS_OK, "abc", "\n")
define_file_readline_test_singleLine(something_crlf, 5, STATUS_OK, "abc", "\r\n")
define_file_readline_test_singleLine(something_bufferSizeExact_noLineEnd, 4, STATUS_EOF, "abc", "")
define_file_readline_test_singleLine(something_bufferSizeExact_lf, 4, STATUS_OK, "abc", "\n")
define_file_readline_test_singleLine(something_bufferSizeExact_crlf, 4, STATUS_OK, "abc", "\r\n")
define_file_readline_test_singleLine(something_bufferTooSmall_noLineEnd, 3, STATUS_BUFFER_TOO_SMALL, "abc", "")
define_file_readline_test_singleLine(something_bufferTooSmall_lf, 3, STATUS_BUFFER_TOO_SMALL, "abc", "\n")
define_file_readline_test_singleLine(something_bufferTooSmall_crlf, 3, STATUS_BUFFER_TOO_SMALL, "abc", "\r\n")
define_file_readline_test_singleLine(lineBodyEndCr_noLineEnd, 5, STATUS_EOF, "ab\r", "")
define_file_readline_test_singleLine(lineBodyEndCr_crlf, 5, STATUS_OK, "ab\r", "\r\n")
define_file_readline_test_singleLine(lineBodyEndCr_bufferSizeExact_noLineEnd, 4, STATUS_EOF, "ab\r", "")
define_file_readline_test_singleLine(lineBodyEndCr_bufferSizeExact_crlf, 4, STATUS_OK, "ab\r", "\r\n")
define_file_readline_test_singleLine(lineBodyEndCr_bufferTooSmall_noLineEnd, 3, STATUS_BUFFER_TOO_SMALL, "ab\r", "")
define_file_readline_test_singleLine(lineBodyEndCr_bufferTooSmall_noLineEnd_someChar, 3, STATUS_BUFFER_TOO_SMALL, "ab\r3", "")

TEST_GROUP_RUNNER(file_readline) {
	fileMem_init(&fileStub, FILE_STUB_SIZE);

	RUN_TEST_CASE(file_readline, emptyLine_noLineEnd);
	RUN_TEST_CASE(file_readline, emptyLine_lf);
	RUN_TEST_CASE(file_readline, emptyLine_crlf);
	RUN_TEST_CASE(file_readline, something_noLineEnd);
	RUN_TEST_CASE(file_readline, something_lf);
	RUN_TEST_CASE(file_readline, something_crlf);
	RUN_TEST_CASE(file_readline, something_bufferSizeExact_noLineEnd);
	RUN_TEST_CASE(file_readline, something_bufferSizeExact_lf);
	RUN_TEST_CASE(file_readline, something_bufferSizeExact_crlf);
	RUN_TEST_CASE(file_readline, something_bufferTooSmall_noLineEnd);
	RUN_TEST_CASE(file_readline, something_bufferTooSmall_lf);
	RUN_TEST_CASE(file_readline, something_bufferTooSmall_crlf);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_noLineEnd);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_crlf);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_bufferSizeExact_noLineEnd);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_bufferSizeExact_crlf);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_bufferTooSmall_noLineEnd);
	RUN_TEST_CASE(file_readline, lineBodyEndCr_bufferTooSmall_noLineEnd_someChar);

	fileMem_free(&fileStub);
}

static void RunAllTests(void) {
	RUN_TEST_GROUP(file_readline);
}

int main(int argc, const char * argv[]) {
	return UnityMain(argc, argv, RunAllTests);
}
