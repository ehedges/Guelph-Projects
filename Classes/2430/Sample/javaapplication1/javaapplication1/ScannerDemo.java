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

public class ScannerDemo {
    
    public static void main(String[] args) {

        Scanner keyboard = new Scanner(System.in);
    
        System.out.println("Enter the number of pads followed by");
        System.out.println("the number of peas in a pod:");
        
        int numberOfPods = 0;
        if( keyboard.hasNextInt() ) 
            numberOfPods = keyboard.nextInt();
        
        int peasPerPod = 0;
        if( keyboard.hasNextInt() )
            peasPerPod = keyboard.nextInt();
        
        int totalNumberOfPeas = numberOfPods * peasPerPod;
        
        System.out.print(numberOfPods + " pods and ");
        System.out.println(peasPerPod + " peas per pod.");
        System.out.println("The total number of peas = " 
                + totalNumberOfPeas);
    }
}

