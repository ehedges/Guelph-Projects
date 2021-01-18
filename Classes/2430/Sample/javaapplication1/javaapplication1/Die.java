/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.Scanner;
/**
 *
 * @author Frank
 */
public class Die {

    public static final int COMMON_FACES = 6;
    private int maxFaces;
    private int faceValue;

    public Die(int maxFaces) {
        if (maxFaces > 0) {
            this.maxFaces = maxFaces;
            roll();
        } else {
            System.out.println("Fatal error: maxFaces must be positive");
            System.exit(0);
        }
    }

    public Die() {
        maxFaces = COMMON_FACES;
        roll();
    }

    public int getMaxFaces() {
        return maxFaces;
    }

    public int getFaceValue() {
        return faceValue;
    }

    public boolean setMaxFaces(int maxFaces) {
        if (maxFaces > 0) {
            this.maxFaces = maxFaces;
            return true;
        } else {
            return false;
        }
    }

    public void roll() {
        faceValue = (int) (Math.random() * maxFaces + 1);
    }

    public String toString() {
        return "maxFaces = " + maxFaces + " faceValue = " + faceValue;
    }

    /** some info */
    public boolean equals(Die other) {
        if (other == null) {
            return false;
        } else {
            return maxFaces == other.maxFaces
                    && faceValue == other.faceValue;
        }
    }
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("Common maxface is " + COMMON_FACES);
        System.out.print("Please enter a maxface value: ");
        int maxFaces = input.nextInt();
        Die die1 = new Die(maxFaces);
        System.out.println(die1.toString());
        die1.roll();
        System.out.println(die1.toString());
    }
}
