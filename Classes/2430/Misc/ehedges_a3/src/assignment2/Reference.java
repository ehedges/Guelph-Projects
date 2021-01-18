/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file choose Tools | Templates
 * and open the template in the editor.
 */
package assignment2;

/**
 *
 * @author Evan Hedges, some code provided by Fei Song.
 */
public class Reference {

    protected String callNumber;  // call number of a book
    protected String title;       // title of a book
    protected int year;           // publication year of a journal

    public Reference(String callNumber, String title, int year) {
        this.callNumber = callNumber;
        this.title = title;
        this.year = year;
    }

    /*set the title*/
    public boolean setTitle(String title) {
        if (title == null || title.isEmpty()) {
            return false;
        } else {
            this.title = title;
            return true;
        }
    }
    /*Sets the year*/

    public boolean setYear(int year) {
        if (year < 1000 || year > 9999) {
            return false;
        } else {
            this.year = year;
            return true;
        }
    }
    /*sets the callnumber*/

    public boolean setCallNumber(String callNumber) {
        if (callNumber == null || callNumber.isEmpty()) {
            return false;
        } else {
            this.callNumber = callNumber;
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
     * Get the value of year
     */
    public int getYear() {
        return year;
    }
    /*CHecks if two objects are the same*/

    public boolean equals(Object other) {
        if (other == null) {
            return false;
        } else if (getClass() != other.getClass()) {
            return false;
        } else {

            Reference otherReference = (Reference) other;

            return callNumber.equalsIgnoreCase(otherReference.callNumber)
                    && title.equalsIgnoreCase(otherReference.title)
                    && year == otherReference.year;

        }
    }
    /*Checks to see if callnumber is the same*/

    public boolean keyEquals(Reference other) {
        if (other == null) {
            return false;
        } else {
            return callNumber.equalsIgnoreCase(other.callNumber)
                    && year == other.year;
        }
    }

}
