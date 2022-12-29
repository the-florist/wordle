#!/bin/bash
#FILES = functions.cpp
NAME = -o wordle
COMPILER = g++-12
TESTFILE = -o ./tools/tests

clean:
	@rm wordle
	@rm ./tools/debug_output.txt

test:
	$(COMPILER) $(TESTFILE) ./tools/tests.cpp
	@./tools/tests
	@echo "Tests run, exiting program."
	@rm ./tools/tests

main:
	@$(COMPILER) $(NAME) wordle.cpp