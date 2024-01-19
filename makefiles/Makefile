include Common.mk
include CommonObjects.mk
include SrcObjects.mk
include CommonSecondaryTargets.mk

OUT_TARGET_NAME = robazc$(TARGET_EXTENSION_LIB_STATIC)
OUT_TARGET_PATH = $(DIR_PATH_BUILD)/$(OUT_TARGET_NAME)

$(OUT_TARGET_PATH): $(IMP_OBJS)
#	$(CC) $(IMP_OBJS) -o $@ $(LDFLAGS)
	$(AR) -rc $@ $^

.PHONY: all

all: $(OUT_TARGET_PATH)
