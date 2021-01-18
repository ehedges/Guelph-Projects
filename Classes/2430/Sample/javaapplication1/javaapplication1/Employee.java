/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

/**
Class Invariant: All objects have a name string and hire date.
A name string of "No name" indicates no real name specified yet.
A hire date of Jan 1, 1000 indicates no real hire date specified yet.
 */
public class Employee {

    protected String name;
    protected Date hireDate;

    public Employee() {
        this("No nsme", new Date("Jan", 1, 1000));
    }

    /**
    Precondition: Neither theName nor theDate is null.
     */
    public Employee(String theName, Date theDate) {
        if (theName == null || theDate == null) {
            System.out.println("Fatal Error creating employee.");
            System.exit(0);
        }
        name = theName;
        hireDate = new Date(theDate);
    }

    public Employee(Employee originalObject) {
        name = originalObject.name;
        hireDate = new Date(originalObject.hireDate);
    }

    public String getName() {
        return name;
    }

    public Date getHireDate() {
        return new Date(hireDate);
    }

    /**
    Precondition newName is not null.
     */
    public void setName(String newName) {
        if (newName == null) {
            System.out.println("Fatal Error setting employee name.");
            System.exit(0);
        } else {
            name = newName;
        }
    }

    /**
    Precondition newDate is not null.
     */
    public void setHireDate(Date newDate) {
        if (newDate == null) {
            System.out.println("Fatal Error setting employee hire date.");
            System.exit(0);
        } else {
            hireDate = new Date(newDate);
        }
    }

    @Override
    public String toString() {
        return (name + " " + hireDate.toString());
    }

    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        } else if (getClass() != other.getClass()) {
            return false;
        } else {
            Employee otherEmployee = (Employee) other;
            return (name.equals(otherEmployee.name)
                    && hireDate.equals(otherEmployee.hireDate));
        }
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 89 * hash + (this.name != null ? this.name.hashCode() : 0);
        hash = 89 * hash + (this.hireDate != null ? this.hireDate.hashCode() : 0);
        return hash;
    }
}
