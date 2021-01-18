package librarysearch;

/** Journal class
 *
 * @author Fei Song
 *
 * A class for representing and comparing journals.
 *
 * Copyright: This code is intended to help you with the implementation of your assignments for CIS*2430 (Fall 2015).  
 *   You are allowed to use it as a starting point for your Assignments Two and Three, but you need to acknowledge it 
 *   in your README file.  Any use, sharing, or re-distribution beyond this course is prohibited.
 */

public class Journal {
	private String callNumber;  // call number of a journal
	private String title;       // title of a journal
	private String organizer;   // organizer of a journal
	private int year;           // publication year of a journal
	
	/**
	 * Create a journal with all the required fields
	 */
	public Journal(String callNumber, String title, String organizer, int year) {
		if( valid(callNumber, title, year) ) {
			this.callNumber = callNumber;
			this.title = title;
			this.organizer = organizer;
			this.year = year;
		} else {			
			System.out.println("Invalid values for creating a journal");
			System.exit(0);
		}
	}
	
	/**
	 * Create a journal with only callNumber, title, and year
	 */
	public Journal(String callNumber, String title, int year) {
		this(callNumber, title, "", year);
	}
	
	/**
	 * A static method for validating if the information for a journal is valid
	 */
	public static boolean valid(String callNumber, String title, int year) {
		return callNumber != null && !callNumber.isEmpty() && title != null && !title.isEmpty() && year >= 1000 & year <= 9999;
	}

	/**
	 * Set a new value for callNumber
	 */
	public boolean setCallNumber(String callNumber) {
		if( callNumber == null || callNumber.isEmpty() ) {
			return false;
		} else {
			this.callNumber = callNumber;
			return true;
		}
	}
	
	/**
	 * Set a new value for title
	 */
	public boolean setTitle(String title) {
		if( title == null || title.isEmpty() ) {
			return false;
		} else {
			this.title = title;
			return true;
		}
	}

	/**
	 * Set a new value for organizer
	 */
	public void setOrganizer(String organizer) {
		this.organizer = organizer;
	}

	/**
	 * Set a new value for year
	 */
	public boolean setYear(int year) {
		if( year <1000 || year > 9999 ) {
			return false;
		} else {
			this.year = year;
			return true;
		}
	}
	
	/**
	 * Get the value of call number
	 */
	public String getCallNumber() {
		return callNumber;
	}
	
	/**
	 * Get the value of title
	 */
	public String getTitle() {
		return title;
	}
	
	/**
	 * Get the value of organizer
	 */
	public String getOrganizer() {
		return organizer;
	}
	
	/**
	 * Get the value of year
	 */
	public int getYear() {
		return year;
	}
	
	/**
	 * Check for the equality of two journals
	 */
	public boolean equals(Journal other) {
		if (other == null)
			return false;
		else 
			return callNumber.equalsIgnoreCase(other.callNumber) &&
			       title.equalsIgnoreCase(other.title) &&
			       organizer.equalsIgnoreCase(other.organizer) &&
			       year == other.year;
	}
	
	/**
	 * Check for equality of two keys
	 */
	public boolean keyEquals(Journal other) {
		if( other == null )
		 	return false;
		else
			return callNumber.equalsIgnoreCase(other.callNumber) &&
			       year == other.year;
	}
	
	/**
	 * Show the content of a journal in a string
	 */
	public String toString() {
		return "Journal: " + callNumber + ". \"" +
			title + "\". " +
			organizer + ", " + year + ".";
	}
	
	public static void main(String[] args) {
                Journal aJournal = new Journal( "P98.C6116", "Computational Linguistics", 
                                       "Association for Computational Linguistics", 2008 );
		System.out.println(aJournal);
	}
}
