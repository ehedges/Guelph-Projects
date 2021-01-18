Evan Hedges 0898140

NOTE: This project used the code provided by Fei Song, and was adjusted for this assignment.

Running:
Navigate to the location the folder was downloaded. Enter the assignment2 folder and compile with javac *.java. go out one directory. This is where the .txt file needs to be located inorder to
be used. Type java assignment2.Assignment2 (path used for windows) to compile. If you wish to compile with files enter the file name after. ex.
java assignment2.Assignment2 test.txt test.txt
Using:
The program will prompt the user for input. Follow the directions, type into the command line and enter to procced. 

Limitations:

Test Plan:
Check each of the buttons functions works. Check that the arraylist grows in size. Check search works, check that search finds values. 


Input: Test that inputting letters in number fields do not crash it. 

Program: Test that it can search without breaking, test that it can add to the arraylist and hashmap. 

Testing:
Tested Q,q Quit, QUIT and Quit: Works. Tested inputing various numbers letters and characters into the name, author and publisher/organization: Doesn't affect the program. Test inputting 
non numbers into the year: does not crash and requires proper input. Requires there to be a title, publication year and call number. Tested no input: title, call number and year is required. 
Doesnot duplicate same items. Tested blank files, tested 0, no files 1 file, or 2 files. Requires .txt only. If files that do not exist are inputed, it will generate an output file if add is used.
Tested 