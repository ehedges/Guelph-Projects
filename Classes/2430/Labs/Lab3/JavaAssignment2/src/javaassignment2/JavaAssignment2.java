/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaassignment2;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Joe
 */
public class JavaAssignment2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
    
        ArrayList<GoofBasics> GoofList = new ArrayList<GoofBasics>(3);              
        
        GoofBasics storeOne = new GoofBasics();        
        storeOne.storeName = "Sparrow Road";
        storeOne.storeID = 1;
        GoofList.add(storeOne);

        GoofBasics storeTwo = new GoofBasics();
        storeTwo.storeName = "Sinister Road";
        storeTwo.storeID = 2;
        GoofList.add(storeTwo);
        
        GoofBasics storeThree = new GoofBasics();
        storeThree.storeName = "Goblin Road";
        storeThree.storeID = 3;      
        GoofList.add(storeThree);
        int value = 0;
        
        while(value == 0)
        {
            
            System.out.println("Welcome to GoofBasics!\nSelect a supermarket or press 4 to exit:\n1.  Sinister Road\n2.  Sparrow Road\n3.  Goblin Road");
            Scanner scan = new Scanner(System.in);
            String input = scan.nextLine(); 
            switch(input)
            {
                
                case "1":
                    GoofBasics.modifyStore(GoofList.get(0));
                    break;
                    
                case "2":
                    GoofBasics.modifyStore(GoofList.get(1));
                    break;
                    
                case "3":
                    GoofBasics.modifyStore(GoofList.get(2));
                    break;
                    
                case "4":
                    
                    value = 1;
                    break;
                    
                default:
                    System.out.println("Invalid input, please try again");
                
            }
            
        }
        
    }

    private static class GoofBasics {

       
        
       private String storeName = new String();
        
       private ArrayList<Employee> employeeList = new ArrayList<>(20);
        
       private ArrayList<Product> productList = new ArrayList<Product>(20);
       
       private int storeID;    
       
       private int employeeSize = 0;
       
       private int productSize = 0;     
        
        public static GoofBasics modifyStore(GoofBasics store) {
        
            int quit = 0;
            int loop = 0;

            int i = 0;
          
            Product tempProduct = new Product();
            Employee tempEmployee = new Employee();                        
            
            while(loop ==0)
            {
                quit = 0;

                System.out.println("Please input a command:\n 1. List products\n 2. Add products\n 3. Remove Product \n 4. List Employee \n 5. Add Employee \n 6. Remove Employee\n 7. Quit \n ");
                Scanner scan = new Scanner(System.in);
                String input = scan.nextLine(); 
                tempEmployee = new Employee();  
                tempProduct = new Product();
                
                switch(input)
                {
                
                    case "1":
                    
                        System.out.println("\nThe products are \n");
                        
                        for( i = 0; i < store.productList.size();i ++)
                        {

                            tempProduct = store.productList.get(i);
                            System.out.println(tempProduct.productID +" "+ tempProduct.productName);

                        }
                        
                        break;
                    
                    case "2":
                    System.out.println("Please add a product: ");
                    input = scan.nextLine(); 
                    tempProduct.productName = input;                    
                    
                    while(quit == 0)
                    {
                        
                        System.out.println("Please input the product ID number\n");
                        input = scan.nextLine();
                        if(input.matches("^[0-9]+$"))
                        {
                            
                        tempProduct.productID = Integer.parseInt(input);
                        store.productSize++;
                        quit = 1;
                        }
                        else
                        {
                            System.out.println("Improper number\n");
                        }
                    }

                    store.productList.add(tempProduct);
                        break;
                    
                    case "3":
                    System.out.println("Please type a number to remove a product: ");
                    while(quit == 0)
                    {    
                        input = scan.nextLine();
                        if(input.matches("^[0-9]+$") && store.productSize > 0 && Integer.parseInt(input)>0 )
                        {
                            for( i =0; i < store.productList.size();i ++)
                            {
                            tempProduct = store.productList.get(i);
                                if(tempProduct.productID == Integer.parseInt(input))
                                {
                            
                                store.productList.remove(i);
                                store.productSize--;
                                quit = 1;
                                }
                            }
                        }
                        else
                        {
                            System.out.println("Improper number\n");
                            quit = 1;
                        }
                    }
                        break;
                    
                    case "4":
                        System.out.println("The Employees are \n");
                        for( i =0; i < store.employeeList.size();i ++)
                        {
                            
                            
                            tempEmployee = store.employeeList.get(i);
                            System.out.println(tempEmployee.ID+ " "+tempEmployee.employeeName);

                        }
                        
                        break;
                    
                    case "5":
                    System.out.println("Please add an Employee: ");
                    input = scan.nextLine(); 
                    tempEmployee.employeeName = input;
                                     
                    while(quit == 0)
                    {
                        System.out.println("Please input the employee ID number\n");
                        input = scan.nextLine();
                        if(input.matches("^[0-9]+$"))
                        {
                            
                        tempEmployee.ID = Integer.parseInt(input);
                        store.employeeSize++;
                        quit = 1;
                        }
                        else
                        {
                            System.out.println("Improper number\n");
                        }
                    }
                    store.employeeList.add(tempEmployee);
                        break;
                     
                    case "6":
                    System.out.println("Please type a number to remove an employee: ");
                    while(quit == 0)
                    {    
                        
                        input = scan.nextLine();
                        if(input.matches("^[0-9]+$") && store.employeeList.size()>0 && Integer.parseInt(input)>0 )
                        {
                            for( i =0; i < store.employeeList.size();i ++)
                            {
           
                                tempEmployee = store.employeeList.get(i);
                                System.out.println(tempEmployee.ID);
                                if(tempEmployee.ID == Integer.parseInt(input))
                                {
                            
                                store.employeeList.remove(i);
                                store.employeeSize--;
                                quit = 1;
                                }
                            }
                           
                        
                        
                        quit = 1;
                        }
                        else
                        {
                            System.out.println("Improper number\n");
                        }
                        quit = 1;
                    }
                        break;
                    case "7":
                        loop = 1;
                    
                    default:
                        System.out.println("Invalid input, please try again");
                
                }
                
            }
            
            return store;
            
        }
    }
        private static class Employee {

            private int ID;
        
            private String employeeName;
            
        
            
        }
        private static class Product {
            
            private String productName;

            private int productID;       
            
        }    
    }
    
    
   
 

   

