/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.ArrayList;

/**
 *
 * @author Frank
 */
public class ArrayListDemo {
    
    public static void main(String[] args) {
        
        ArrayList<String> list = new ArrayList<String>(20);
        ArrayList<Double> scores = new ArrayList<Double>(10);
        
        list.add("One");
        list.add("Two");
        list.add("Three");
        list.add(0, "Zero");
        
        for (int i = 0; i < list.size(); i++)
            System.out.println(list.get(i));
        
        list.remove(0);
        
           for (int i = 0; i < list.size(); i++)
            System.out.println(list.get(i));     
    }
    
}
