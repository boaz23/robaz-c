ifeq ($(OS),Windows_NT)
	ifeq ($(shell uname -s),) # not in a bash-like shell
		RM = del /F /Q
		MKDIR = mkdir
	else # in a bash-like shell, like msys
		RM    += -r
		MKDIR = mkdir -p
	endif

	TARGET_EXTENSION_EXE        = .exe
	TARGET_EXTENSION_LIB_STATIC = .lib
else
	RM    += -r
	MKDIR = mkdir -p

	TARGET_EXE_EXTENSION        = 
	TARGET_EXTENSION_LIB_STATIC = .a
endif

ifeq ($(NDEBUG),)
	CCFLAGS += -g
else
	CCFLAGS += -DNDEBUG
endif

CCFLAGS +=\
	-Wall\
	-Wextra\
	-Wpedantic\
	-Wpointer-arith\
	-Wcast-align\
	-Wwrite-strings\
	-Wswitch-default\
	-Wunreachable-code\
	-Wmissing-field-initializers\
	-Wno-unknown-pragmas\
	-Wstrict-prototypes\
	-Wundef\
	-Wold-style-definition\

DIR_NAME_IMP = implementation
DIR_NAME_IF  = interface

DIR_NAME_LIBS  = libs
DIR_PATH_BUILD = build
DIR_NAME_OBJS  = objs
DIR_NAME_DEPS  = deps

DEPS =

print_var = $(info VAR $(1) = $($(1)))
