#!/bin/bash

# Copy user's code here
echo "Copying header and source files for domtree and html"
cp ../domtree.h ./
cp ../domtree.c ./
cp ../html.h ./
cp ../html.c ./


# Go through all tests:
DIFF_NOT_PASSED=0
VALGRIND_NOT_PASSED=0
for t in tests/* ; do
	if [ -d "$t" ]; then
		echo "-- Starting test $(basename $t) --"
	
		binary=./hw03_$(basename $t)
        output=$(basename $t)_output.html

		cat $t/main.c > main.c
		gcc -std=c99 -Wall -Wextra -Werror domtree.h domtree.c html.h html.c main.c -o $binary

        valgrind=$( { valgrind --leak-check=full -q $binary < $t/input.html > $output; } 2>&1 )
		diff=$(diff $t/exp_output.html $output)

		if [ "$diff" == "" ]; then
			echo "Output comparison test passed"
			rm $output
		else
			echo "Test $(basename $t) failed. Try running"
			echo "	$ $(tput setaf 1)diff $t/exp_output.html $output$(tput setaf 7)"
			DIFF_NOT_PASSED=$((DIFF_NOT_PASSED + 1))
		fi

		if [ "$valgrind" == "" ]; then
			echo "Valgrind test passed"
			rm $binary
		else
			echo "Valgrind test failed. Try running"
			echo "	$ $(tput setaf 1)valgrind $binary < $t/input.html$(tput setaf 7)"
			VALGRIND_NOT_PASSED=$((VALGRIND_NOT_PASSED + 1))
		fi
	fi
done

echo "--- All tests ended. $DIFF_NOT_PASSED output comparisons failed. $VALGRIND_NOT_PASSED valgrind tests failed. ---"
rm main.c
