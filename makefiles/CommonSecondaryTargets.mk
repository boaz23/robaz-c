$(DEPS):
	@$(MKDIR) $(@D)

.PHONY: clean

clean:
	$(RM) $(wildcard $(DIR_PATH_BUILD)/*)

include $(wildcard $(DEPS))
