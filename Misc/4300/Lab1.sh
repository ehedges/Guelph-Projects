#!/bin/sh

##
## Figure out how many times the word "PASS" exists in the files given
##
## v1.1: A. Hamilton-Wright, Sep 2018
##

N_FILES_PROCESSED=0
tallyPassed=0
for filename in "$@"
do

	if [ -f ${filename} ]

	then

		echo "Working on ${filename}"

		if

			## search, printing a count, and extract the second field
			grep -c PASS ${filename} | cut -d: -f2

		then

			:

		else

			## print a warning to standard error
			echo "warning: search failed" >&2

		fi

		N_FILES_PROCESSED=$((N_FILES_PROCESSED + 1))

	fi
done

echo "In total, ${tallyPassed} tests were passed"
echo "In total, ${N_FILES_PROCESSED} were processed"
