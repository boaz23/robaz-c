
#include <stdio.h>
#include "tests_common.h"
#include "files.h"
#include "print.h"

declare_real_func(fgetc);
declare_real_func(fseeko);
declare_real_func(feof);

int wrap_func(fgetc)(FILE *file) {
	printf_ln("fgetc called of fd %d", fileno(file));
	return real_func(fgetc)(file);
}

int wrap_func(fseeko)(FILE *file, off_t offset, int whence) {
	return real_func(fseeko)(file, offset, whence);
}

int wrap_func(feof)(FILE *file) {
	return real_func(feof)(file);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printfe_ln("No file provided");
		return 1;
	}

	const char *file_path = argv[1];
	FILE *file = fopen(file_path, "r");
	if (file == NULL) {
		printfe_ln("Failed to open the file '%s'", file_path);
		return 2;
	}

	printf_ln("read '%c'", fgetc(file));

	// char buffer[5];
	// const char *buffer_end = &buffer[sizeof(buffer)];
	// status_t status = file_readline(file, buffer, sizeof(buffer));

	// switch (status)
	// {
	// case STATUS_OK:
	// case STATUS_EOF:
	//   printf("Read");
	//   if (status == STATUS_EOF)
	//   {
	//     printf(" (EOF)");
	//   }
	//   printf(": ");
	//   break;

	// case STATUS_BUFFER_TOO_SMALL:
	//   printfe_ln("Line too long");
	//   return 3;

	// case STATUS_ERROR:
	//   printfe_ln("Line read error: errno=%d (%s)", errno, strerror(errno));
	//   return 4;

	// default:
	//   fail();
	// }

	// if (buffer[0] == '\0')
	// {
	//   printf("<empty>");
	// }
	// else
	// {
	//   for (char *pc = buffer; (pc < buffer_end) && *pc; pc++)
	//   {
	//     unsigned char c = *(unsigned char *)pc;
	//     if (c == '\r')
	//     {
	//       printf("\\r");
	//     }
	//     else if ((0x20 <= c) && (c < 0x80))
	//     {
	//       printf("'%c'", c);
	//     }
	//     else
	//     {
	//       printf("0x%02X", c);
	//     }

	//     printf(" ");
	//   }
	// }

	// printf("\n");

	if (fclose(file) < 0)
	{
		printfe_ln("Failed to close the file '%s'", file_path);
		return 2;
	}

	return 0;
}
