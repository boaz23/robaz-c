include Common.mk

# SRC_EXTS = c cpp s
SRCS = $(shell find $(DIR_PATH_SRC_IMP) -name *.cpp -or -name *.c -or -name *.s)
# TODO: Do this for each extension
map_srcs = $(foreach src,$(SRCS),$(DIR_PATH_BUILD)/$(1)/$(src:$(DIR_PATH_SRC_IMP)/%.c=%.$(2)))
OBJS = $(call map_srcs,$(DIR_NAME_OBJS),o)
# DEPS_SRC_EXTS = c cpp
DEPS = $(call map_srcs,$(DIR_NAME_DEPS),d)
DIRS = $(dir $(OBJS) $(DEPS))

INC_FLAGS = -I$(DIR_PATH_SRC_IF)
# INC_DIRS  = $(shell find $(DIR_PATH_SRC) -type d)
# INC_FLAGS = $(addprefix -I,$(INC_DIRS))

DEPFLAGS += -MMD -MP -MT $@ -MF $(DIR_PATH_BUILD)/$(DIR_NAME_DEPS)/$*.d
CCFLAGS += $(INC_FLAGS) $(DEPFLAGS)

$(OUT_TARGET_PATH): $(OBJS)
#	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(AR) -rc $@ $^

# c source
$(DIR_PATH_BUILD)/$(DIR_NAME_OBJS)/%.o::\
		$(DIR_PATH_SRC_IMP)/%.c\
		$(DIR_PATH_BUILD)/$(DIR_NAME_DEPS)/%.d |\
		$(dir $(DIR_PATH_BUILD)/$(DIR_NAME_OBJS)/%.o)\
		$(dir $(DIR_PATH_BUILD)/$(DIR_NAME_DEPS)/%.d)
	$(CC) $(CCFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(DIR_PATH_BUILD)/$(DIR_NAME_OBJS)/%.o:: $(DIR_PATH_SRC_IMP)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# assembly
$(DIR_PATH_BUILD)/$(DIR_NAME_OBJS)/%.o:: $(DIR_PATH_SRC_IMP)/%.s
	$(AS) $(ASFLAGS) -c $< -o $@

$(DEPS):

$(DIRS):
	$(MKDIR) $@

.PHONY: all clean tests

all: $(OUT_TARGET_PATH)

clean:
	$(RM) -r $(wildcard $(DIR_PATH_BUILD)/*)

include $(wildcard $(DEPS))

# tests:
# 	$(CC) -o build/test_files $(CCFLAGS) -Isrc/interface/ -Wl,--wrap=fgetc -Wl,--wrap=fseeko -Wl,--wrap=feof test/test_files.c src/implementation/files.c
