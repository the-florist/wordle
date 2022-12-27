#!/bin/bash
#FILES = functions.cpp
NAME = -o wordle
COMPILER = g++-12
TESTFILE = -o tests

clean:
	rm wordle
	rm ./tools/debug_output.txt

test:
	cd ./tools/
	$(COMPILER) $(TESTFILE) tests.cpp
	./tests
	echo "Tests run, exiting program."
	rm tests

make:
	$(COMPILER) $(NAME) wordle.cpp