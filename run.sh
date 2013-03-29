#!/bin/bash

# Copy user's code here
echo "Copying header and source files for domtree and html"
cp ../domtree.h ./
cp ../domtree.c ./
cp ../html.h ./
cp ../html.c ./



# Go trough all tests:
NOT_PASSED=0
for t in tests/* ; do
	if [ -d "$t" ]; then
		echo "-- Starting test $(basename $t) --"
	
		cat $t/main.c > main.c
		gcc -std=c99 -Wall -Wextra -Werror domtree.h domtree.c html.h html.c main.c -o hw03
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

ZERO=0
if [[ $NOT_PASSED -eq $ZERO ]]; then
	rm output.html
fi
rm main.c
