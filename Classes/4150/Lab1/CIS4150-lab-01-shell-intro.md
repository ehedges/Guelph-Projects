
CIS 4150 Lab : Shell Programming for Test Automation: Pt 1
==========================================================

The most important part of testing is that it get done, and get done reproducibly.
For this reason, software development organizations are all interested in automating
testing so that all testing can be easily run, and run repeatedly.

In order to apply a potentially large number of tests to a given software system
in an automated and reproducible way, an obvious strategy is to write a program
to do it.

We have learned about "test drivers" and "test cases" in class, and now we will
look at tools to write these ourselves.

Later in the class we will look at language-specific test systems such as JUnit,
however we will begin by looking at the general principles of testing using some
type of scripting engine, which is the de-facto standard test strategy used by
the vast majority of software houses.

Using script based testing (using a common scripting language like the Bourne
shell) is so pervasive and simple that it has prevented any analogue of a unit
testing tool like JUnit from becoming popular in the C programming world.


Unix/Linux based Test Automation
--------------------------------

The simplest, most portable, and by far the most common means of automating
the running of programs, including test suites, under any UNIX-alike system,
is Bourne Shell (`sh`) scripting.

On Linux, the Bourne shell is replaced by a Bourne Shell derivative, the
Bourne-Again Shell (`bash`), which is a _superset_ of `sh`.
We will focus our attention on the command
structures common to both `sh(1)` and `bash(1)`, as this way they will run
under any POSIX compliant Bourne shell.


Shell Syntax Parsing
--------------------

In `sh` scripts, "_whitespace_" is used to delimit tokens.  This is very different
from most other programming languages with which you are familiar, such as C,
Python, perl, Java.

If you have a syntax error, pay careful attention to the spacing in the examples.  In particular, note that

	if [ ${variable} = "value" ]

is quite different from

	if[ "${variable}"="value" ]

In the second one, the shell is not trying to perform an `if` command,
but rather is looking to find some command called `if[`.  Were one to fix
the missing space between the `if` and the `[`, the `[` command (called `test(1)`)
would evaluate `"${variable}"="value"` as a single token, which would evaluate
whether the string is not the null string.  As the string at minimum contains
the substring "`=value`" this test would always be true.

As you can see, it will benefit you to think carefully about your spacing.

Variables
---------

In `sh` scripting, variables are set using simple `VARIABLE=value` statements.
Double quotes are used if there are any spaces in the value, _e.g._:

	AVAR="some value"

Backquotes (usually available on the same key as the tilde `~`) are
used to set a variable with the value printed by a program or pipe:

	WHAT_DID_IT_PRINT=`echo "Hello there"`
	echo "WHAT_DID_IT_PRINT contains ${WHAT_DID_IT_PRINT} as a value"


Comments
--------

Comments begin at a `#` character, and extend to the end of the line.
The only exception to this is in the very first character of a file,
where a `#!` pairing forms a magic number indicating an interpreter
is to be used for the executable file.


Program Control Structure
-------------------------

Program control in the form of looping and branching is available.
Here is a simple example:

	#!/bin/sh

	##
	## Figure out how many times the word "PASS" exists in the files given
	##
	## v1.1: A. Hamilton-Wright, Sep 2018
	##

	N_FILES_PROCESSED=0

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

	echo "In total, ${N_FILES_PROCESSED} were processed"

Things to note in this example:

* the `#!` line at the top of the file indicating the interpreter `/bin/sh`
* the use of the variable `N_FILES_PROCESSED` to tally how many times the
	loop is run
* the builtin variable `"$@"` used to access the list of command arguments
	to the script (_i.e._ the equivalent of the `argv` array in a C program).
	By using the double quotes around $@ we get a list of quoted strings,
	with any spacing preserved within the string.
* the `for` loop structure using a list of elements (from `"$@"`) and a
	body delimited by `do` and `done`
* the two different `if` statements:
	* each body begun by `then` and terminated by `fi`
	* the second using an `else` clause
	* the first using the program `[` to test whether a string variable
		value is of type file, where `[` will return success (0) if the
		test succeeds
	* the second evaluating whether the `grep | cut` pipe returned success
* the use of the `:` command as a placeholder in an otherwise empty `if`
	statement body
* the use of the `$(( arithmetic ))` syntax to perform arithmetic expansion


For this lab
------------

Using the above script (downloadable from CourseLink), add the
following functionality:

1)	Tally the total number of PASS statements.  Note that you can use
	backquotes to load up the printed values from a command or pipe into
	a variable. 
	
	In one sentence each, explain the functionality of  the following commands and/or flags.
		echo, grep, cut, -d, -c, -f, -f2

2)  If a file contains "FAIL(s)" then add logic to display the line number in the file that "FAIL(s)" ocurred on to the screen. 

3)	After processing all files, compute whether or not the result of all the files is "PASS" or "FAIL".
Each "PASS" is given a weight of 1.25 and each "FAIL" is given a weight of -1.5. 
A final result of "PASS" is a score >= 0. For example, if 2 "PASS" strings are 
found across all files and 2 "FAIL"strings are found across all files, then the resulting final socre would be -0.5. 
Therefore the final result would be fail. However, if 3 "PASS" strings were found across all files and 2 "FAIL" strings were found across all files, 
the reulting final score would be (1.25*3 + (-1.5)*2) = 0.75. Therefore the final result would be "PASS". 
Display the value of the final result to the screen and display whether it is "PASS" or "FAIL". 


Submit your work by the end of the lab period using the CourseLink "dropbox"
tool for this lab.

A note on the Unix environment
==============================

If you are working on this lab on a Unix-type machine
(Linux, MacOS or some Unix variant) then all of the tools pertaining to the
Bourne shell should already work for you.

If you are working on something else, please be aware that you can do the
work of this lab (or any of the Unix based work in the course) by using
secure shell (`ssh`) to access the machine `linux.socs.uoguelph.ca`.  You
will then need to move files back and forth from your "local" machine
(the one you are typing on) and the "remote" `linux.socs.uoguelph.ca` machine.

To copy a file such as `CIS4150-lab-02-files.zip` from the current directory
in your local machine _to_ `linux.socs.uoguelph.ca` you can use a command
such as

	scp CIS4150-lab-02-files.zip yourusername@linux.socs.uoguelph.ca:.

Note that the "`.`" after the "`:`" character means "current directory",
which is your login (`${HOME}`) directory.  If you wanted to put the
file in the subdirectory `work' you would use:

	scp CIS4150-lab-02-files.zip yourusername@linux.socs.uoguelph.ca:work


Note that this looks very much like the copy command `cp(1)`, with a machine
identity stuck in front of the name for the directory or file on the remote
machine -- and it is.  To copy the other way, you just use something like this:

	scp yourusername@linux.socs.uoguelph.ca:work/myfile.txt .


If you want to use wildcards on the remote machine, you have to put them in quotes
like so:

	scp "yourusername@linux.socs.uoguelph.ca:work/*.c" .


Otherwise, your local machine will try to expand the "`\*`" and things will
be confused.

Getting ssh for Windows
-----------------------

Most modern operating systems have some version of `ssh` and `scp` built in,
however Windows does not.  You can obtain the "PuTTY" ssh tool from
[https://www.putty.org/](https://www.putty.org/).  Follow the "download PuTTY here"
link (it will take you to `chiark.greenend.org.uk` -- this is normal).

The client for performing `ssh(1)` is `putty.exe` and the tool for `scp(1)` is
`pscp.exe`.

