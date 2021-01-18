package assignment2;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Book class
 *
 * @author Evan Hedges, origional code proviuded by Fei Song
 *
 * A class for representing and comparing books.
 *
 * Copyright: This code is intended to help you with the implementation of your
 * assignments for CIS*2430 (Fall 2015). You are allowed to use it as a starting
 * point for your Assignments Two and Three, but you need to acknowledge it in
 * your README file. Any use, sharing, or re-distribution beyond this course is
 * prohibited.
 */
public class Book extends Reference {

    private String authors;     // one or multiple authors separated by commas
    private String publisher;   // publisher of a book

    /**
     * Create a book with all the required fields
     */
    public Book(String callNumber, String title, String publisher, int year, String authors) {
        super(callNumber, title, year);
        if (valid(callNumber, title, year)) {
            this.authors = authors;
            this.publisher = publisher;
        } else {
            System.out.println("Invalid values for creating a book");
            System.exit(0);
        }
    }

    /**
     * Create a book with only callNumber, title, and year
     */
    public Book(String callNumber, String title, int year) {
        this(callNumber, "", title, year, "");
    }

    /**
     * A static method for validating if the information for a book is valid
     */
    public static boolean valid(String callNumber, String title, int year) {
        return callNumber != null && !callNumber.isEmpty() && title != null && !title.isEmpty() && year >= 1000 & year <= 9999;
    }

    /**
     * Set a new value for authors
     */
    public void setAuthors(String authors) {
        this.authors = authors;
    }

    /**
     * Set a new value for publisher
     */
    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    /**
     * Get the value of authors
     */
    public String getAuthors() {
        return authors;
    }

    /**
     * Get the value of publisher
     */
    public String getPublisher() {
        return publisher;
    }

    /**
     * Check for the equality of two books
     */
    public boolean equals(Book other) {
        if (other == null) {
            return false;
        } else {
            return authors.equalsIgnoreCase(other.authors)
                    && publisher.equalsIgnoreCase(other.publisher);
        }

    }

    /*Check returns the values*/
    @Override
    public String toString() {
        return "Book: " + callNumber + ". "
                + authors + ". \""
                + title + "\". "
                + publisher + ", " + year + ".";
    }
    /*testing*/

    public void update(String fileName) {
        System.out.println("Adding a book.");
        //Use the PrintWriter to get the familiar println syntax
        PrintWriter outputStream = null;
        //Use FileWriter to write to file
        //Use BufferedWriter to improve write performance by delayed buffered writes
        PrintWriter catalog;
        try {
            catalog = new PrintWriter(new BufferedWriter(new FileWriter(fileName, true)));

            //write code to print info to the file in the format:\
            catalog.println("Book~" + callNumber + "~" + title + "~" + publisher + "~" + year + "~" + authors);
            //<ItemName> by <itemCreator> for <Price>

            catalog.close();
        } catch (IOException ex) {
            Logger.getLogger(Reference.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

}
