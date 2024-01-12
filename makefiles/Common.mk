ifeq ($(OS),Windows_NT)
	ifeq ($(shell uname -s),) # not in a bash-like shell
		CLEANUP = del /F /Q
		MKDIR = mkdir
	else # in a bash-like shell, like msys
		CLEANUP = rm -rf
		MKDIR = mkdir -p
	endif

	TARGET_EXTENSION_EXE        = .exe
	TARGET_EXTENSION_LIB_STATIC = .lib
else
	CLEANUP = rm -rf
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

DIR_PATH_SRC     = src
DIR_PATH_SRC_IMP = $(DIR_PATH_SRC)/implementation
DIR_PATH_SRC_IF  = $(DIR_PATH_SRC)/interface

DIR_PATH_BUILD = build
DIR_NAME_OBJS  = $(DIR_PATH_SRC)/objs
DIR_NAME_DEPS  = $(DIR_PATH_SRC)/deps

OUT_TARGET_NAME = robazc$(TARGET_EXTENSION_LIB_STATIC)
OUT_TARGET_PATH = $(DIR_PATH_BUILD)/$(OUT_TARGET_NAME)
