DEPFLAGS = -MMD -MP -MT $@ -MF $(word 2,$^)

define define_object_targets
# parameters
# $(1): Variables namespace. This parameter should be hardcoded into this code
#   here instead of using a variable for it because its value is overwritten if
#   this definition is evaluated again and this affects the commands executed
#   in the receipies.
#
$(1)_dir_path_src = $(strip $(2))
$(1)_srcs_exclude_dirs = $(strip $(3))
$(1)_inc_dirs = $(strip $(4))
# parameters end

$(1)_find_exclude = $$(foreach dir,\
	$$($(1)_srcs_exclude_dirs),\
	$$(dir:%=-not \( -path % -prune \))\
)
$(1)_SRCS = $$(shell find\
	$$($(1)_dir_path_src)\
	$$($(1)_find_exclude)\
	-name *.c\
)
$(1)_map_srcs = $$(foreach src,$$($(1)_SRCS),$(DIR_PATH_BUILD)/$$(1)/$$(src:%.c=%.$$(2)))
$(1)_OBJS = $$(call $(1)_map_srcs,$(DIR_NAME_OBJS),o)
$(1)_DEPS = $$(call $(1)_map_srcs,$(DIR_NAME_DEPS),d)
DEPS += $$($(1)_DEPS)

$(1)_CCFLAGS =\
	$$(CCFLAGS)\
	$$(DEPFLAGS)\
	$$(patsubst %,-I%,$$($(1)_inc_dirs))\

# C source
$$($(1)_OBJS): $(DIR_PATH_BUILD)/$(DIR_NAME_OBJS)/%.o:\
		%.c\
		$(DIR_PATH_BUILD)/$(DIR_NAME_DEPS)/%.d
	@$$(MKDIR) $$(@D)
	$$(CC) $$($(1)_CCFLAGS) -c $$< -o $$@
endef
