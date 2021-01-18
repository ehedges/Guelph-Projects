/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.*;
//import java.util.Iterator;

public class HashSetIteratorDemo
{
    public static void main(String[] args)
    {
        Collection<String> s = new ArrayList<String>( );

        s.add("health");
        s.add("love");
        s.add("money");
        s.add("health");

        System.out.println("The set contains:");

        Iterator<String> i = s.iterator( );
        while (i.hasNext( ))
            System.out.println(i.next( ));

        i.remove( );

        System.out.println( );
        System.out.println("The set now contains:");

        i = s.iterator( );
        while (i.hasNext( ))
            System.out.println(i.next( ));

        System.out.println("End of program.");
    }
}
 


