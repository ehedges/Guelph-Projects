package assignment2;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Journal class
 *
 * @author Evan Hedges, origional code provided by Fei Song
 *
 * A class for representing and comparing journals.
 *
 * Copyright: This code is intended to help you with the implementation of your
 * assignments for CIS*2430 (Fall 2015). You are allowed to use it as a starting
 * point for your Assignments Two and Three, but you need to acknowledge it in
 * your README file. Any use, sharing, or re-distribution beyond this course is
 * prohibited.
 */
public class Journal extends Reference {

    private String organizer;   // organizer of a journal

    /**
     * Create a journal with all the required fields
     */
    public Journal(String callNumber, String title, String organizer, int year) {
        super(callNumber, title, year);
        if (valid(callNumber, title, year)) {

            this.organizer = organizer;

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
     * Set a new value for organizer
     */
    public void setOrganizer(String organizer) {
        this.organizer = organizer;
    }

    /**
     * Get the value of organizer
     */
    public String getOrganizer() {
        return organizer;
    }

    /**
     * Check for the equality of two journals
     */
    public boolean equals(Journal other) {
        if (other == null) {
            return false;
        } else {
            return organizer.equalsIgnoreCase(other.organizer);
        }

    }

    /**
     * Show the content of a journal in a string
     */
    @Override
    public String toString() {
        return "Journal: " + callNumber + ". \""
                + title + "\". "
                + organizer + ", " + year + ".";
    }
    /*testing*/

    public void update(String fileName) {
        System.out.println("Adding a journal.");
        //Use the PrintWriter to get the familiar println syntax
        PrintWriter outputStream = null;
        //Use FileWriter to write to file
        //Use BufferedWriter to improve write performance by delayed buffered writes
        PrintWriter catalog;
        try {
            catalog = new PrintWriter(new BufferedWriter(new FileWriter(fileName, true)));

            //write code to print info to the file in the format:\
            catalog.println("Journal"+"~"+callNumber+"~"+title+"~"+organizer+"~"+year);
            //<ItemName> by <itemCreator> for <Price>

            catalog.close();
        } catch (IOException ex) {
            Logger.getLogger(Reference.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    public static void main(String[] args) {

        Journal aJournal = new Journal("P98.C6116", "Computational Linguistics",
                "Association for Computational Linguistics", 2008);
        System.out.println(aJournal);
    }
    
}
