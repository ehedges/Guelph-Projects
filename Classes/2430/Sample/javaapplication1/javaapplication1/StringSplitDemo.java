/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.Scanner;

public class StringSplitDemo {

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        String delimiters = "[, ]+"; //Comma and blank space

        boolean isValid = false;
        do {
            System.out.println("Enter your last name");
            System.out.println("followed by your first and middle names.");
            System.out.println("If you have no middle name,");
            System.out.println("enter \"None\".");
            String inputLine = keyboard.nextLine();

            String[] names = inputLine.split(delimiters);
            if (names.length < 2) {
                //int localVar = 5;
                continue;
            }
            //System.out.println("localVar = " + localVar);
            String middleName = "";
            if (names.length > 2 && !names[2].equalsIgnoreCase("None")) {
                middleName = names[2];
            }

            System.out.println("Hello " + names[1]
                    + " " + middleName + " " + names[0]);

        } while (isValid);
    }
}
