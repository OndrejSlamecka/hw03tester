#!/bin/bash

# Copy user's code here
echo "Copying header and source files for domtree and html"
cp ../domtree.h ./
cp ../domtree.c ./
cp ../html.h ./
cp ../html.c ./

echo "Running unit tests"
result=$( bash unit.sh 2>&1 )
if [ "$result" == "" ]; then
    echo "  Unit tests passed"
	echo "Running integration tests"
	bash integration.sh
else
	echo $result
    echo "  Unit tests failed. Skipping integration tests"
fi
