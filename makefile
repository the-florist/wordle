#!/bin/bash
NAME = -o wordle
COMPILER = g++-12
TESTFILE = -o ./tools/tests

clean:
	@if [[ -e wordle ]]; then rm wordle; fi
	@if [[ -e ./tools/debug_output.txt ]]; then rm ./tools/debug_output.txt; fi

test:
	@$(COMPILER) $(TESTFILE) ./tools/tests.cpp
	@./tools/tests
	@echo "Tests run, exiting program."
	@rm ./tools/tests

main:
	@$(COMPILER) $(NAME) wordle.cpp

run:
	@if [[ !(-e wordle) ]]; then make main; fi
	@./wordle