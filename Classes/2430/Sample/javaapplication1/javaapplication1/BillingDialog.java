/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.Scanner;

public class BillingDialog {

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Welcome to the law offices of");
        System.out.println("Dewey, Cheatham, and Howe.");
        Bill yourBill = new Bill();
        yourBill.inputTimeWorked(keyboard);
        yourBill.updateFee();
        //yourBill.outputBill( );
        System.out.println(yourBill.toString());
        System.out.println("We have placed a lien on your house.");
        System.out.println("It has been our pleasure to serve you.");
    }
}
