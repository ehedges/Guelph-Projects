#!/bin/sh

##
## Figure out how many times the word "PASS" exists in the files given
##
##Evan Hedges

##echo Command to write arguments to the standard output.
##grep searches the input filees for lines that matches a pattern. 
##cut is a utility used to cut out lines of the file, this can be done by byte, position, character and delimiter. 
##-d is a flag, can be used with cut to seperate by delimiter.
##-c used to count the number of times a word occurs. Returns a number.
##-f obtains patterns from a file. 
##-f2 same as f, but obtain the 2nd pattern from a file. 

N_FILES_PROCESSED=0

tempPassed=0
tempFailed=0
tallyPassed=0
tallyFailed=0
total=0

for filename in "$@"
do

	if [ -f ${filename} ]

	then

		echo "Working on ${filename}"

		if

			## search, printing a count, and extract the second field
			tempPassed=`grep -c "\<PASS\>" "${filename}" | cut -d: -f2` 
			tempFailed=`grep -c "\<FAIL\>" "${filename}" | cut -d: -f2`

			if [ ${tempFailed} -gt 0 ] 

			then	
		
				errorLines=`grep -n "\<FAIL\>" "${filename}"` 
				echo "\n${errorLines}\n"

			fi

			tallyPassed=$((tempPassed+tallyPassed)) 
			tallyFailed=$((tempFailed+tallyFailed))
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
echo "In total, ${tallyFailed} tests were Failed"
decimalPass=`python -c "print($tallyPassed*1.25)"`
decimalFail=`python -c "print($tallyFailed*(-1.5))"`
total=`python -c "print($decimalPass+$decimalFail)"`
result=`python -c " 
if ( $total < 0):
	print 'FAIL with ',
	print($total)
else:
	print 'PASS with ',
	print($total)
"
`

echo "${result}"
echo "Decimal pass is, ${decimalPass}"
echo "Decimal fail is, ${decimalFail}"
echo "In total, ${N_FILES_PROCESSED} were processed"
