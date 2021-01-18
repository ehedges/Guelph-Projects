package librarysearch;

import java.util.Scanner;

/** LibrarySearchDemo class
 *
 * @author Fei Song
 *
 * Copyright: This code is intended to help you with the implementation of your assignments for CIS*2430 (Fall 2015).  
 *   You are allowed to use it as a starting point for your Assignments Two and Three, but you need to acknowledge it 
 *   in your README file.  Any use, sharing, or re-distribution beyond this course is prohibited.
 */

public class LibrarySearchDemo {
	public static void main( String[] args ) {
		Scanner input = new Scanner( System.in );
		LibrarySearch library = new LibrarySearch();
		String command;
		do {
			System.out.print( "Enter add, search, or quit> " );
			command = input.nextLine();
			if( command.equalsIgnoreCase("add") || command.equalsIgnoreCase("a") )
				library.add( input );
			else if( command.equalsIgnoreCase("search") || command.equalsIgnoreCase("s") )
				library.search( input );			
		} while( !command.equalsIgnoreCase("quit") && !command.equalsIgnoreCase("q") );
	}
}
