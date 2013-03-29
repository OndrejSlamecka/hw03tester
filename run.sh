#!/bin/bash

# Copy user's code here
echo "Copying header and source files for domtree and html"
cp ../domtree.h ./
cp ../domtree.c ./
cp ../html.h ./
cp ../html.c ./


# Go through all tests:
NOT_PASSED=0
for t in tests/* ; do
	if [ -d "$t" ]; then
		echo "-- Starting test $(basename $t) --"
	
		cat $t/main.c > main.c
		gcc -std=c99 -Wall -Wextra -Werror domtree.h domtree.c html.h html.c main.c -o hw03
		output=$(basename $t)_output.html
		./hw03 < $t/input.html > $output
		DIFF=$(diff $t/exp_output.html $output)
		if [ "$DIFF" == "" ]; then
			echo "Test passed"
			rm $output
		else
			echo "Test $(basename $t) failed. Try running"
			echo "	$(tput setaf 1)$ diff $t/exp_output.html $output$(tput setaf 7)"
			NOT_PASSED=$((NOT_PASSED + 1))
		fi
	fi
done

echo "--- Whole test suit ended. $NOT_PASSED failed. ---"
rm main.c
