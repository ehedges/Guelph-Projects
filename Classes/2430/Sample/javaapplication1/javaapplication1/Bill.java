/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.Scanner;

public class Bill {

    public static final double RATE = 150.00; //Dollars per quarter hour
    private int hours;
    private int minutes;
    private double fee;
    
    public Bill(int hours, int minutes) {
        this.hours = hours;
        this.minutes = minutes;
    }
    
    public Bill() {
        hours = 0;
        minutes = 0;
    }
    
    public int getHours() {
        return hours;
    }
    
    public boolean setHours(int h) {
        if( h>= 0 ) {
            hours = h;
            return true;
        } else
            return false;
    }
    
    public boolean equals(Bill other) {
        if (other == null) {
            return false;
        } else {
            return hours == other.hours
                    && minutes == other.minutes
                    && fee == other.fee;
        }
    }

    public String toString() {
        return hours + " hours, " + minutes + " minutes for a fee of $" + fee;
    }

    public void inputTimeWorked(Scanner keyboard) {
        System.out.println("Enter number of full hours worked");
        System.out.println("followed by number of minutes:");
        //Scanner keyboard = new Scanner(System.in);
        hours = keyboard.nextInt();
        minutes = keyboard.nextInt();
    }

    private static double computeFee(int hoursWorked, int minutesWorked) {
        minutesWorked = hoursWorked * 60 + minutesWorked;
        int quarterHours = minutesWorked / 15;   // Any remaining fraction of a
        // quarter hour is not charged for.
        return quarterHours * RATE;
    }

    public void updateFee() {
        int hours = 0;
        fee = computeFee(this.hours, minutes);
    }

    public void outputBill() {
        System.out.println("Time worked: ");
        System.out.println(hours + " hours and " + minutes + " minutes");
        System.out.println("Rate: $" + RATE + " per quarter hour.");
        System.out.println("Amount due: $" + fee);
    }
}

