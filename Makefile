.PHONY: all clean tests tests_clean

MY_MAKEFLAGS =\
	-Imakefiles/\
	--no-builtin-rules

all clean:
	$(MAKE) $(MY_MAKEFLAGS) -f makefiles/Makefile $@

# tests:
# 	$(MAKE) -Imakefiles/ -f makefiles/Makefile-tests test

# tests_clean:
# 	$(MAKE) -Imakefiles/ -f makefiles/Makefile-tests clean
