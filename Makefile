.PHONY: all clean tests tests_clean

MY_MAKEFLAGS =\
	-Imakefiles/\
	--no-builtin-rules

all clean:
	$(MAKE) $(MY_MAKEFLAGS) -f makefiles/Makefile $@

run_tests:
	$(MAKE) $(MY_MAKEFLAGS) -f makefiles/Makefile-tests run
