/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.util.ArrayList;

public class InheritanceDemo {

    public static void main(String[] args) {
        Employee e = new Employee("Joe Worker", new Date("January", 1, 2004));
        HourlyEmployee h = new HourlyEmployee("Joe Worker",
                new Date("January", 1, 2004), 50.50, 160);

        /*ArrayList<Employee> people = new ArrayList<Employee>();
        people.add(e);
        people.add(h);
        e = h;  // upcasting
        if (e instanceof HourlyEmployee) {
            h = (HourlyEmployee) e;     // downcasting
        }*/
        System.out.println(e.toString());
        System.out.println(h.toString());

        System.out.println();
        if (e.equals(h)) {
            System.out.println("An emplyee is the same as an hourly employee");
        } else {
            System.out.println("An employee is not the same as an hourly employee");
        }

        if (h.equals(e)) {
            System.out.println("An hourly employee is the same as an employee");
        } else {
            System.out.println("An hourly employee is not the same as an employee");
        }

        System.out.println();
        System.out.println("joe's longer name is " + h.getName());

        System.out.println("Changing joe's name to Josephine.");
        h.setName("Josephine");

        System.out.println("joe's record is as follows:");
        System.out.println(h.toString());
    }
}
