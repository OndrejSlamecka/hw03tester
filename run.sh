#!/bin/bash

# Copy user's code here
if [[ $1 == "-c" ]]; then
	echo "Copying header and source files for domtree and html"
	cp ../domtree.h ./
	cp ../domtree.c ./
	cp ../html.h ./
	cp ../html.c ./
fi


# Go trough all tests:
NOT_PASSED=0
for t in tests/* ; do
	if [ -d "$t" ]; then
		echo "-- Starting test $(basename $t) --"
	
		gcc -std=c99 -Wall -Wextra -Werror domtree.h domtree.c html.h html.c $t/main.c -o hw03
		./hw03 < $t/input.html > output.html
		DIFF=$(diff $t/exp_output.html output.html)
		if [ "$DIFF" == "" ]; then
			echo "Test passed"
		else
			echo "Test $(basename $t) failed. Try $ diff $t/exp_output.html output.html"
			NOT_PASSED=$((NOT_PASSED + 1))
		fi
	fi
done

echo "--- Whole test suit ended. $NOT_PASSED failed. ---"
rm output.html
