/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment1;

/**
 *
 * @author Evan Hedges, 0898140
 * CIS 2430: Object Oriented Programming
 */
import java.util.ArrayList;
import java.util.Scanner;


public class Assignment1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // Intialize variables
        ArrayList<Book> bookList = new ArrayList<>(5);
        ArrayList<Journal> journalList = new ArrayList<>(5);
        
        LibrarySearch lists = new LibrarySearch();
        
        Journal journalInput = new Journal();
        Journal compareJournal = new Journal();

        Book bookInput = new Book();
        Book compareBook = new Book();
        
        int looping = 0;
        int quit = 0;
        int lengthBook = 0;
        int lengthJournal = 0; 
        boolean addList = true;
        int i = 0;
        
        
        /*Loop to enable usage*/
        while(looping == 0)
        {
            /*Prompt for input*/
            addList = true;
            System.out.println("Welcome to the library program.\n Type add to insert books or journals into the storage.\n Type search to look for a reference.\n Type quit to exit.");
            Scanner scan = new Scanner(System.in);
            String input = scan.nextLine();
            
            /*Allows case insensitivty*/
            input = input.toLowerCase();
            
            if(input.equals("quit") || input.equals("q"))
            {
                
                looping = 1;
                
            }
            else if(input.equals("add")|| input.equals("a"))
            {
                
                quit = 0;
                while(quit != 1)
                {
                    /*chooses between journal or book type*/
                    System.out.println("Type book to add a book, or type journal to add a journal. \n");
                    input = scan.nextLine();
                    input = input.toLowerCase();
                    if(input.equals("book")|| input.equals("b"))
                    {
                        bookInput.AddBook();
                        /*checks for multiple books*/
                        for(i = 0; i<bookList.size(); i++)
                        {
                        
                            compareBook = bookList.get(i);
                            
                            if(compareBook.callNum.equals(bookInput.callNum) && compareBook.year == bookInput.year)
                            {
                            
                                addList = false;
                                
                            }
                            
                        }
                        if(addList == true)
                        {    
                            bookList.add(bookInput);
                            quit = 1;
                        }
                        else
                        {
                            System.out.println("Invalid input. \n");
                        }
                        quit = 1;
                    }
                    else if(input.equals("journal")|| input.equals("j"))
                    {
                        /*checks for multiple joursnals*/
                        journalInput.AddJournal();
                        for(i = 0; i<journalList.size(); i++)
                        {
                        
                            
                            compareJournal = journalList.get(i);
                            
                            if(compareJournal.callNum.equals(journalInput.callNum) && compareJournal.year == journalInput.year)
                            {
                            
                                addList = false;
                                
                            }
                            
                        }
                        if(addList == true)
                        {    
                            journalList.add(journalInput);
                            quit = 1;
                        }
                        else
                        {
                            System.out.println("Invalid input. \n");
                        }
                        quit = 1;
                    }
                    else if(input.equals("quit") || input.equals("q"))
                    {
                        quit = 1;
                    }        
                    else
                    {
                         System.out.println("Invalid type type.\n");
                    }
                }
                /*searching*/
            }
            else if(input.equals("search")|| input.equals("s"))
            {
                lengthBook = bookList.size();
                lengthJournal = bookList.size();
                LibrarySearch.bookSearch(bookList,lengthBook);
            }
            else
            {
                System.out.println("Invalid input: please try again\n");
            }
        }
        
    }
    
    public static class Book{
    
        private String callNum;
        private int year;
        private String title;
        private String publisher;
        private ArrayList<String> authors = new ArrayList<>(1);
        public static Book AddBook ()
    {
       Book tempBook = new Book();
        
       String testInput = null;
        
       int quit = 0;
       int testNum = 0;
         
        System.out.println("Please input the title of the book:\n");
        
        Scanner scan = new Scanner(System.in);
        String input = scan.nextLine();
           
        tempBook.title = input;
        /*requires title*/
        while(tempBook.title.length()<=1)
        {
            System.out.println("Invalid input.\n");
            input = scan.nextLine();          
            tempBook.title = input;
        
        }
        
        
        System.out.println("Please input the name of the publisher:\n");
        
            input = scan.nextLine();
            tempBook.publisher = input;
        
        /*requires year*/
        while(quit == 0)
        {
            System.out.println("Please input the year of when the book was published:\n");
            input = scan.nextLine();
            if(input.matches("^[0-9]+$"))
            {
                testNum = Integer.parseInt(input);
                if(testNum > 1000&& testNum<9999)
                {
                tempBook.year = Integer.parseInt(input);
                quit = 1;
                }
                else
                {
                    System.out.println("Improper year\n");
                }
            }
            else
            {
                 System.out.println("Invalid input \n");
            }
           
        }
        
        System.out.println("Please input the call number:");
        quit = 0;       
        testNum = 0;
        input = scan.nextLine();
        /*forces to enter a valid year after 1000 and before 9999*/
        tempBook.callNum = input;
        
        while(tempBook.callNum.length()<=1)
        {
            System.out.println("Invalid input.\n");
            input = scan.nextLine();          
            tempBook.callNum = input;
        
        }  
        
        return tempBook;
    }
    }
    
    public static class Journal
    {
        private String callNum;
        private int year;
        private String title;
        private String organization;
        
        public static Journal AddJournal()
    {
        Journal tempJournal = new Journal();
        
        String testInput = null;
        
        int quit = 0;
        int testNum = 0;
         
        System.out.println("Please input the title of the Journal:\n");
        
        Scanner scan = new Scanner(System.in);
        String input = scan.nextLine();
        
        System.out.println("Please input the title of the journal:\n");
        
         tempJournal.title = input;
        
        /*requires title*/
        while(tempJournal.title.length()<=1)
        {
            System.out.println("Invalid input.\n");
            input = scan.nextLine();          
            tempJournal.title = input;
        
        }
        
        
        System.out.println("Please input the name of the publisher:\n");
        
            input = scan.nextLine();
            tempJournal.organization = input;
        
        /*requires year*/
        while(quit == 0)
        {
            System.out.println("Please input the year of when the journal was published:\n");
            input = scan.nextLine();
            if(input.matches("^[0-9]+$"))
            {
                testNum = Integer.parseInt(input);
                if(testNum > 1000&& testNum<9999)
                {
                tempJournal.year = Integer.parseInt(input);
                quit = 1;
                }
                else
                {
                    System.out.println("Improper year\n");
                }
            }
            else
            {
                 System.out.println("Invalid input \n");
            }
           
        }
        
        System.out.println("Please input the call number:");
        quit = 0;       
        testNum = 0;
        /*forces to enter a valid year after 1000 and before 9999*/
        input = scan.nextLine(); 
        tempJournal.callNum = input;
        
        while(tempJournal.callNum.length()<=1)
        {
            System.out.println("Invalid input.\n");
            input = scan.nextLine();          
            tempJournal.callNum = input;
        
        }  
        
        return tempJournal;
    }
    }
    public static class LibrarySearch
    {

       
        /*Variables*/
       static ArrayList<Book> bookSearch = new ArrayList<>(5);       
       ArrayList<Journal> journalSearch = new ArrayList<>(5);
       /*not done search*/
        private static void bookSearch(ArrayList<Book> bookList, int lengthBook) {
            
            /*creates each of the fields
            String callNum;
            int year;
            int testNum;
            String title;
            String publisher;
            String authors;
            
            System.out.println("Please type the call number.\n");
            Scanner scan = new Scanner(System.in);
            String input = scan.nextLine();
            
            callNum = input.toLowerCase();
            
            System.out.println("Please type the title.\n");
            input = scan.nextLine();
            title = input;
            System.out.println("Please type the publisher.\n");
            input = scan.nextLine();
            publisher = input;
            System.out.println("Please type the author.\n");
            input = scan.nextLine();
            authors = input;
            System.out.println("Please type the year.\n");
            input = scan.nextLine();
            if(input.matches("^[0-9]+$"))
            {
                testNum = Integer.parseInt(input);
                if(testNum > 1000&& testNum<9999)
                {
                year = Integer.parseInt(input);
                
                }
                else
                {
                    System.out.println("Improper year.\n");
                }
            }
            else
            {
                 System.out.println("Invalid input. \n");
            }
            int i = 0;
            
            bookSearch = (ArrayList<Book>) bookList.clone();
            
            for(i = 0; i<lengthBook-1; i++) 
            {
                if(title.equalsIgnoreCase(bookSearch))
            }
            */
        }
       
       public void JournalSearch()
       {
                   
       }
    }
    
    
    
}
    


