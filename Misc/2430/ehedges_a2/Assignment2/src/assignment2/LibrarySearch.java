package assignment2;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * LibrarySearch class
 *
 * @author Evan Hedges, origional code proviuded by Fei Song
 *
 * A class that adds, maintains, and searches for books and journals.
 *
 * Copyright: This code is intended to help you with the implementation of your
 * assignments for CIS*2430 (Fall 2015). You are allowed to use it as a starting
 * point for your Assignments Two and Three, but you need to acknowledge it in
 * your README file. Any use, sharing, or re-distribution beyond this course is
 * prohibited.
 */
public class LibrarySearch {

// Create the hasmap
    private ArrayList<Reference> reference = new ArrayList<Reference>();
    HashMap<String, ArrayList<Integer>> theMap = new HashMap<String, ArrayList<Integer>>(100);

    public static final String[] REFERENCE_TYPES = new String[]{"book", "journal", "b", "j"};

    public LibrarySearch() {

    }

    /*
     * Add a valid book
     */
    private boolean addBook(Book book, String fileName, Boolean input) {
        int key = 0;
        int temp = 0;
        /*check for duplicates*/
        for (Reference reference1 : reference) {
            if (reference1.keyEquals(book)) {
                return false;
            }
        }
        /*Generate Keys and add to arraylist*/
        reference.add(book);
        temp = reference.size();
        String[] tokens = book.title.split("[ ,\n]+");
        for (String token : tokens) {
            if (!theMap.containsKey(token)) {
                theMap.put(token, new ArrayList<Integer>());
            }
            theMap.get(token).add(temp);
        }

        if (input == false && fileName != null) {
            book.update(fileName);
        }
        return true;
    }

    /*
     * Add a valid journal
     */
    private boolean addJournal(Journal journal, String fileName, Boolean input) {
        int key = 0;
        String title;
        int temp = 0;
        /*check for duplicates*/
        for (Reference reference1 : reference) {
            if (reference1.keyEquals(journal)) {
                return false;
            }
        }
        /*Generate Keys and add to arraylist*/
        reference.add(journal);
        temp = reference.size();
        String[] tokens = journal.title.split("[ ,\n]+");
        for (String token : tokens) {
            if (!theMap.containsKey(token)) {
                theMap.put(token, new ArrayList<Integer>());
            }
            theMap.get(token).add(temp);
        }

        if (input == false && fileName != null) {
            journal.update(fileName);
        }
        return true;
    }

    /**
     * Create a book or journal from the input and add it to the appropriate
     * list
     *
     * @param input
     * @param fileName
     */
    public void add(Scanner input, String fileName) {
        String type;
        do {
            System.out.print("Enter a reference type (book or journal)> ");
            type = input.nextLine();
        } while (!matchedKeyword(type, REFERENCE_TYPES));

        String callNumber = "";
        do {
            System.out.print("Enter a call number> ");
            callNumber = input.nextLine();
            if (callNumber.isEmpty() == true) {
                System.out.print("Invalid input\n");
            }
        } while (callNumber.isEmpty());

        String authors = "";
        if (type.equalsIgnoreCase("book") || type.equalsIgnoreCase("b")) {
            System.out.print("Enter a list of authors separated by commas> ");
            authors = input.nextLine();
            if (authors.matches("^[~]+$")) {
                System.out.print("Invalid author> ");
                authors = null;
            }
        }

        String title = "";
        do {
            System.out.print("Enter a title> ");
            title = input.nextLine();
            if (title.isEmpty() == true) {
                System.out.print("Invalid input \n");
            }

        } while (title.isEmpty());

        String publisher = "";
        if (type.equalsIgnoreCase("book") || type.equalsIgnoreCase("b")) {
            System.out.print("Enter a publisher> ");
            publisher = input.nextLine();
        }

        String organizer = "";
        if (type.equalsIgnoreCase("journal") || type.equalsIgnoreCase("j")) {
            System.out.print("Enter an organizer> ");
            organizer = input.nextLine();
        }

        int year = 0;
        do {
            System.out.print("Enter a year (between 1000 and 9999)>");
            String yearValue = null;
            do {
                yearValue = input.nextLine();
                if (!yearValue.matches("^[0-9~]+$")) {
                    System.out.print("Invalid input>");
                }
            } while (!yearValue.matches("^[0-9~]+$"));
            year = yearValue.isEmpty() ? 0 : Integer.parseInt(yearValue);

        } while (year < 1000 || year > 9999);

        boolean result = true;
        if (type.equalsIgnoreCase("book") || type.equalsIgnoreCase("b")) {
            result = addBook(new Book(callNumber, title, publisher, year, authors), fileName, false);
        } else {
            result = addJournal(new Journal(callNumber, title, organizer, year), fileName, false);
        }
        if (!result) {
            System.out.println("Add failed: there is another reference with the same call number and year");
        }
    }

    /* 
     * Check if a keyword is on a list of tokens
     */
    private boolean matchedKeyword(String keyword, String[] tokens) {
        for (String token : tokens) {
            if (keyword.equalsIgnoreCase(token)) {
                return true;
            }
        }
        return false;
    }

    /*
     * Check if all keywords are in a string 
     */
    private boolean matchedKeywords(String[] keywords, String title) {
        String[] tokens = title.split("[ ,\n]+");
        for (String keyword : keywords) {
            if (!matchedKeyword(keyword, tokens)) {
                return false;
            }
        }
        return true;
    }

    /*
     * Search for all references that satisfy a search request
     */
    private void searchReference(String callNumber, String[] keywords, int startYear, int endYear) {
        System.out.println("Reference searching...");
        for (Reference reference1 : reference) {
            if ((callNumber.equals("") || reference1.getCallNumber().equalsIgnoreCase(callNumber)) && (keywords == null || matchedKeywords(keywords, reference1.getTitle())) && (reference1.getYear() >= startYear && reference1.getYear() <= endYear)) {
                System.out.println(reference1);
            }
        }
    }

    /*Leftover code from Feisong
        
     * Search for all journals that satisfy a search request
	 
     private void searchJournals( String callNumber, String[] keywords, int startYear, int endYear ) {
     for( int i = 0; i < reference.size(); i++ ) 
     if( (callNumber.equals("") || reference.get(i).getCallNumber().equalsIgnoreCase(callNumber)) &&
     (keywords == null || matchedKeywords(keywords, reference.get(i).getTitle())) &&
     (reference.get(i).getYear() >= startYear && reference.get(i).getYear() <= endYear) )
     System.out.println( reference.get(i) ); 		
     }
     */
    /**
     * Gather a search request and find the matched books and journals in the
     * related list(s)
     *
     * @param input
     */
    public void search(Scanner input) {
        /* get the input fields*/
        System.out.print("Enter a call number> ");
        String callNumber = input.nextLine();
        System.out.print("Enter title keywords> ");
        String[] keywords = null;
        Boolean hashSearch = false;
        String line = input.nextLine();
        if (!line.isEmpty()) {
            keywords = line.split("[ ,\n]+");
        }

        int startYear = Integer.MIN_VALUE, endYear = Integer.MAX_VALUE;
        boolean valid;
        /* get the year,*/
        do {
            valid = true;
            System.out.print("Enter a time period as startYear-endYear, or year> ");

            line = input.nextLine();
            /*check for non numbers and range*/
            if (!line.equals("") && line.matches("^[0-9-]+$")) {
                int hyphen = line.indexOf('-');
                if (hyphen < 0) /*SIngle year*/ {
                    startYear = endYear = Integer.parseInt(line);
                } else {
                    /*Range of years*/
                    String startValue = line.substring(0, hyphen);
                    startYear = startValue.equals("") ? Integer.MIN_VALUE : Integer.parseInt(startValue);
                    String endValue = line.substring(hyphen + 1);
                    endYear = endValue.equals("") ? Integer.MAX_VALUE : Integer.parseInt(endValue);

                    if (startYear > endYear) {
                        valid = false;
                    }
                }
            } else {
                System.out.print("Error with years procceding\n");
            }

        } while (!valid);

        // search for matched references
        System.out.println("Matched references: ");
        if (keywords != null) {
            hashSearch = searchHashMap(callNumber, keywords, startYear, endYear);
        }
        if (hashSearch == false) {
            searchReference(callNumber, keywords, startYear, endYear);
        }
        /*searchJournals( callNumber, keywords, startYear, endYear );*/
    }
    /*test
     public static void main( String[] args ) {
     Scanner input = new Scanner( System.in );
     LibrarySearch library = new LibrarySearch();
     String command;
     do {
     System.out.print( "Enter add, search, or quit> " );
     command = input.nextLine();
     if( command.equalsIgnoreCase("add") || command.equalsIgnoreCase("a") )
     library.add( input );
     else if( command.equalsIgnoreCase("search") || command.equalsIgnoreCase("s") )
     library.search( input );			
     } while( !command.equalsIgnoreCase("quit") && !command.equalsIgnoreCase("q") );
     }
     */

    Boolean savedData(String fileName) {
        Scanner inputStream = null;
        String values = null;
        String temp = null;
        boolean result = true;
        StringTokenizer tokens;
        try {

            inputStream = new Scanner(new FileInputStream(fileName));
        } catch (FileNotFoundException ex) {
            System.out.println("Error opening file");
            return false;
        }

        while (inputStream.hasNextLine()) {
            temp = null;
            values = inputStream.nextLine();
            System.out.println(values);
            tokens = new StringTokenizer(values, "~");
            if (tokens.countTokens() > 1) {
                temp = tokens.nextToken();
                System.out.println(temp + "\n");
                if (temp.matches("Book")) {
                    result = addBook(new Book(tokens.nextToken(), tokens.nextToken(), tokens.nextToken(), Integer.parseInt(tokens.nextToken()), tokens.nextToken()), fileName, true);
                }
                if (temp.matches("Journal")) {

                    result = addJournal(new Journal(tokens.nextToken(), tokens.nextToken(), tokens.nextToken(), Integer.parseInt(tokens.nextToken())), fileName, true);
                }
                if (!result) {
                    System.out.println("Add failed.");
                }

            } else {
                System.out.println("Trying to input empty file.");
            }
        }
        return true;
    }
    /*Creats a key for the hash map*/

    public int generateKey(String title) {
        int key = 0;
        int value = 0;
        int hashSize = 0;
        char temp;
        for (int i = 0; i < title.length(); i++) {
            temp = Character.toLowerCase(title.charAt(i));
            value += temp * 33;
        }
        if (theMap.size() < 100) {
            hashSize = 100;
        }
        key = value % hashSize;
        return key;
    }
    /*searches using hash method*/

    private Boolean searchHashMap(String callNumber, String keywords[], int startYear, int endYear) {

        System.out.println("Hash searching...");
        ArrayList<Integer> index = null;
        ArrayList<Integer> indexTwo = null;
        int value = 0;
        /*loops checking for duplicates*/
        for (int i = 0; i < keywords.length; i++) {

            index = theMap.get(keywords[i]);

            if (index != null) {
                System.out.println("Index recieved");
                for (int j = 0; j < keywords.length; j++) {
                    System.out.println("Checking duplicates");
                    indexTwo = theMap.get(keywords[i]);
                    if (i != j && indexTwo != null) {
                        System.out.println("Keeping duplicates");
                        index = checkList(index, indexTwo); /*returns empty list if none match*/

                        if (index.isEmpty()) {
                            return false;
                        }
                    }
                }
            }

        }

        if (index == null) {
            System.out.println("Error Finding using Hash search.");
            return false;
        }
        /*printing*/
        for (Integer index1 : index) {
            System.out.println("Printing");
            value = index1 - 1;
            if ((callNumber.equals("") || reference.get(value).getCallNumber().equalsIgnoreCase(callNumber))
                    && (keywords == null || matchedKeywords(keywords, reference.get(value).getTitle()))
                    && (reference.get(value).getYear() >= startYear && reference.get(value).getYear() <= endYear)) {
                System.out.println(reference.get(value));
            }
        }

        return true;
    }
    /*compairs the list and keeps te ones that show up in both*/

    private ArrayList<Integer> checkList(ArrayList<Integer> listOne, ArrayList<Integer> listTwo) {

        ArrayList<Integer> same = new ArrayList<Integer>();

        int i;
        int j;

        for (Integer listOneNum : listOne) {
            for (Integer listTwoNum : listTwo) {
                if (listTwoNum == listOneNum) {
                    same.add(listTwoNum);
                }

            }

        }
        return same;
    }
}
