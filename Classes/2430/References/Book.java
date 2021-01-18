package librarysearch;

/** Book class
 *
 * @author Fei Song
 *
 * A class for representing and comparing books.
 * 
 * Copyright: This code is intended to help you with the implementation of your assignments for CIS*2430 (Fall 2015).  
 *   You are allowed to use it as a starting point for your Assignments Two and Three, but you need to acknowledge it 
 *   in your README file.  Any use, sharing, or re-distribution beyond this course is prohibited.
 */

public class Book {
	private String callNumber;  // call number of a book
	private String authors;     // one or multiple authors separated by commas
	private String title;       // title of a book
	private String publisher;   // publisher of a book
	private int year;           // publication year of a book
	
	/**
	 * Create a book with all the required fields
	 */
	public Book(String callNumber, String authors, String title, String publisher, int year) {
		if( valid(callNumber, title, year) ) {
			this.callNumber = callNumber;
			this.authors = authors;
			this.title = title;
			this.publisher = publisher;
			this.year = year;
		} else {			
			System.out.println("Invalid values for creating a book");
			System.exit(0);
		}
	}
	
	/**
	 * Create a book with only callNumber, title, and year
	 */
	public Book(String callNumber, String title, int year) {
		this(callNumber, "", title, "", year);
	}
	
	/**
	 * A static method for validating if the information for a book is valid
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
	 * Set a new value for authors
	 */
	public void setAuthors(String authors) {
		this.authors = authors;
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
	 * Set a new value for publisher
	 */
	public void setPublisher(String publisher) {
		this.publisher = publisher;
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
	 * Get the value of authors
	 */
	public String getAuthors() {
		return authors;
	}
	
	/**
	 * Get the value of title
	 */
	public String getTitle() {
		return title;
	}
	
	/**
	 * Get the value of publisher
	 */
	public String getPublisher() {
		return publisher;
	}
	
	/**
	 * Get the value of year
	 */
	public int getYear() {
		return year;
	}
	
	/**
	 * Check for the equality of two books
	 */
	public boolean equals(Book other) {
		if (other == null)
			return false;
		else 
			return callNumber.equalsIgnoreCase(other.callNumber) &&
			       authors.equalsIgnoreCase(other.authors) &&
			       title.equalsIgnoreCase(other.title) &&
			       publisher.equalsIgnoreCase(other.publisher) &&
			       year == other.year;
	}

	/**
	 * Check for equality of two keys
	 */
	public boolean keyEquals(Book other) {
		if( other == null )
		 	return false;
		else
			return callNumber.equalsIgnoreCase(other.callNumber) &&
			       year == other.year;
	}
	
	/**
	 * Show the content of a book in a string
	 */
	public String toString() {
		return "Book: " + callNumber + ". " +
                        authors + ". \"" +
			title + "\". " +
			publisher + ", " + year + ".";
	}
	
	public static void main(String[] args) {
                Book aBook = new Book( "QA76.73.J38S265", "Walter Savitch, Kenrich Mock", "Absolute Java", 
                                       "Addison-Wesley", 2009 );
		System.out.println(aBook);
	}
}
