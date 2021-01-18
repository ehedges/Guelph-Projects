/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.HashMap;
import java.util.Scanner;

public class HashMapDemo {
   public static void main(String[] args) {
       HashMap<String, Employee> employees = 
            new HashMap<String, Employee>(10);
  
       employees.put("Joe", 
            new Employee("Joe", new Date("September", 15, 1970)));
       employees.put("Andy", 
            new Employee("Andy", new Date("August", 22, 1971)));
       employees.put("Greg", 
            new Employee("Greg", new Date("March", 9, 1972)));
       employees.put("Kiki", 
            new Employee("Kiki", new Date("October", 8, 1970)));
       System.out.println("Added Joe, Andy, Greg, and Kiki to the map.");
        Scanner keyboard = new Scanner(System.in);
        String name = "";
        do {
             System.out.print("\nEnter a name to look up the map. ");
             System.out.println("Press enter to quit.");
             name = keyboard.nextLine();
             if (employees.containsKey(name)) {
                Employee e = employees.get(name);
                System.out.println("Name found: " + e.toString());
             } else if (!name.equals("")) {
                System.out.println("Name not found");
             }
        } while (!name.equals(""));
    }
}


