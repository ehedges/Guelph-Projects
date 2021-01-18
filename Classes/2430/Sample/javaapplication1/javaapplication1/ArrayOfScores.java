/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

/**
 *
 * @author fsong
 */
import java.util.Scanner;

public class ArrayOfScores {

    /**
    Reads in 5 scores and shows how much each
    score differs from the highest score.
     */
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        double[] score = new double[6];


        System.out.println("Enter " + score.length + " scores:");
        score[0] = keyboard.nextDouble();
        double max = score[0];
        //int index;
        for (int index = 1; index < score.length; index++) {
            score[index] = keyboard.nextDouble();
            if (score[index] > max) {
                max = score[index];
            }
        }
        //System.out.println("Show value for index: " + index);
        System.out.println("The max score is " + max);
        System.out.println("The scores are:");
        //int index;
        for (int index = 0; index < score.length; index++) {
            System.out.println(score[index] + " differs from max by "
                    + (max - score[index]));
        }
    }
}
