/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

/**
 *
 * @author Frank
 */
public class FirstProgram {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("Hello, World!");
        
        System.out.println("Let's demonstrate a simple calculation:");
        int answer;
        answer = 2 + 2;
        System.out.println("2 plus 2 is " + answer);
        
        String greeting = "Hello";
        String javaClass = "CIS*2430 class";
        System.out.println(greeting + " " + javaClass + "!");
        System.out.println("greeting = " + greeting);
        
        greeting = greeting + " " + javaClass;
        String greeting2 = new String("Hello CIS*2430 class");
        if (greeting == greeting2)
            System.out.println("An example of co-reference");
        else
            System.out.println("Two different references");
        if (greeting.equals(greeting2))
            System.out.println("An example of idential strings");
        else
            System.out.println("Two different objects");
     
    }
    
}
