/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

/**
 *
 * @author fsong
 */
import java.util.*;
//import java.util.ArrayList;

public class ArrayOfScores2 {

    //int size;
    
    /**
    Reads in 5 scores and shows how much each
    score differs from the highest score.
     */
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        ArrayList<Double> scores = new ArrayList<Double>(10);

        int size = 0;
        do {
            //Scanner keyboard = new Scanner(System.in);
            System.out.println("Ener a positive integer: ");
            String strValue = keyboard.nextLine();
            if (strValue.matches("[0-9]+")) {
                size = Integer.parseInt(strValue);
            }
        } while (size <= 0);
        
        //Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter " + size + " scores:");
        scores.add(keyboard.nextDouble());
        double max = scores.get(0);
        for (int index = 1; index < size; index++) {
            scores.add(keyboard.nextDouble());
            if (scores.get(index) > max) {
                max = scores.get(index);
            }
        }

        System.out.println("The highest score is " + max);
        System.out.println("The scores are:");
        for (int index = 0; index < scores.size(); index++) {
            System.out.println(scores.get(index) + " differs from max by "
                    + (max - scores.get(index)));
        }
    }
}
