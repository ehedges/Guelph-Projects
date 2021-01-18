/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

/**
 * Class Invariant: All objects have a name string, hire date, nonnegative wage
 * rate, and nonnegative number of hours worked. A name string of "No name"
 * indicates no real name specified yet. A hire date of Jan 1, 1000 indicates no
 * real hire date specified yet.
 */
public class HourlyEmployee extends Employee {

    private double wageRate;
    private double hours; //for the month

    public HourlyEmployee() {
        this("No name", new Date(), 0, 0);
    }

    /**
     * Precondition: Neither theName nor theDate is null; theWageRate and
     * theHours are nonnegative.
     */
    public HourlyEmployee(String theName, Date theDate,
            double theWageRate, double theHours) {
        super(theName, theDate);
        if ((theWageRate >= 0) && (theHours >= 0)) {
            wageRate = theWageRate;
            hours = theHours;
        } else {
            System.out.println(
                    "Fatal Error: creating an illegal hourly employee.");
            System.exit(0);
        }
    }

    /*public HourlyEmployee(HourlyEmployee originalObject) {
     super(originalObject);
     wageRate = originalObject.wageRate;
     hours = originalObject.hours;
     }*/
    public double getRate() {
        return wageRate;
    }

    public double getHours() {
        return hours;
    }

    /**
     * Returns the pay for the month.
     */
    public double getPay() {
        return wageRate * hours;
    }

    /**
     * Precondition: hoursWorked is nonnegative.
     */
    public boolean setHours(double hoursWorked) {
        if (hoursWorked >= 0) {
            hours = hoursWorked;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Precondition: newWageRate is nonnegative.
     */
    public boolean setRate(double newWageRate) {
        if (newWageRate >= 0) {
            wageRate = newWageRate;
            return true;
        } else {
            return false;
        }
    }

    public String toString() {
        return super.toString()
                + " " + wageRate + " per hour for " + hours + " hours";
    }

   
    /*public boolean equals(HourlyEmployee other) {
        if (other == null) {
            return false;
        } else {
            return name.equals(other.name)
                    && hireDate.equals(other.hireDate)
                    && wageRate == other.wageRate
                    && hours == other.hours;
        }
    }*/
    
    public boolean equals(Object other) {
        if (other == null)
            return false;
        else if (getClass() != other.getClass())
            return false;
        else {
            HourlyEmployee otherHourly = (HourlyEmployee)other;
            return super.equals(otherHourly)
                    && wageRate == otherHourly.wageRate 
                    && hours == otherHourly.hours;
        }
    }
}
