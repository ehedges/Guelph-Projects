package assignment2;

import java.awt.TextArea;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;

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
    /*adds the stuff*/
    public void add(String callNumber, String title, String publisher, String yearValue, String author, String type, TextArea message) {
        int year = 0;

        boolean result = true;
        if (type.equalsIgnoreCase("book") || type.equalsIgnoreCase("b") && callNumber.isEmpty() != true && title.isEmpty() != true && !yearValue.matches("^[0-9~]+$")) {
            result = addBook(new Book(callNumber, title, publisher, yearValue.isEmpty() ? 0 : Integer.parseInt(yearValue), author), null, false);
        } else if (type.equalsIgnoreCase("journal") || type.equalsIgnoreCase("j") && callNumber.isEmpty() != true && title.isEmpty() != true && !yearValue.matches("^[0-9~]+$")) {
            result = addJournal(new Journal(callNumber, title, publisher, yearValue.isEmpty() ? 0 : Integer.parseInt(yearValue)), null, false);
        }
        if (!result) {
            message.setText("Add failed: there is another reference with the same call number and year");
        }
        System.out.println(reference.size());
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
    private void searchReference(String callNumber, String[] keywords, int startYear, int endYear, TextArea messageArea) {
        System.out.println("Reference searching...");
        for (Reference reference1 : reference) {
            System.out.println(reference);
            System.out.println("Call number " + callNumber);
            System.out.println(startYear);
            System.out.println(endYear);
            if ((callNumber.equals("") || reference1.getCallNumber().equalsIgnoreCase(callNumber)) && (keywords == null || matchedKeywords(keywords, reference1.getTitle())) && (reference1.getYear() >= startYear && reference1.getYear() <= endYear)) {
                System.out.println("Reference" + reference1);
                messageArea.setText("Title:" + reference1.title);
                messageArea.setText("CallNumber:" + reference1.title);
                messageArea.setText("Year:" + reference1.year);
                System.out.println("Here");
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
     *
     * @param callNumber
     * @param keywords
     * @param startYear
     * @param endYear
     * @param messageArea
     */
    public void search(String callNumber, String[] keywords, int startYear, int endYear, TextArea messageArea) {
        /* get the input fields*/
        System.out.println(reference.size());
        System.out.println("Matched references: ");
        System.out.println("Searching" + callNumber);
        boolean hashSearch = false;
        // search for matched references
        System.out.println("Matched references: ");
        if (keywords != null) {
            hashSearch = searchHashMap(callNumber, keywords, startYear, endYear, messageArea);
        }
        if (hashSearch == false) {
            searchReference(callNumber, keywords, startYear, endYear, messageArea);
        }/*
         searchJournals( callNumber, keywords, startYear, endYear );*/

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
    /*NOT USED*/

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

    private Boolean searchHashMap(String callNumber, String keywords[], int startYear, int endYear, TextArea messageArea) {

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
            System.out.println(reference.get(value));/*
             if ((callNumber.equals("") || reference.get(value).getCallNumber().equalsIgnoreCase(callNumber))
             && (keywords == null || matchedKeywords(keywords, reference.get(value).getTitle()))
             && (reference.get(value).getYear() >= startYear && reference.get(value).getYear() <= endYear)) {*/

            if (reference.get(value) instanceof Book) {
                Book aBook = (Book) reference.get(value);
                messageArea.append("\n\nBook\n");
                messageArea.append("\nTitle:" + aBook.title);
                messageArea.append("\nCallNumber:" + aBook.callNumber);
                messageArea.append("\nYear:" + aBook.year);
                messageArea.append("\nAuthors:" + aBook.authors);
                messageArea.append("\nPublishers:" + aBook.publisher);
            } else if (reference.get(value) instanceof Journal) {
                Journal aJournal = (Journal) reference.get(value);
                messageArea.append("\n\nJournal\n");
                messageArea.append("\nTitle:" + aJournal.title);
                messageArea.append("\nCallNumber:" + aJournal.callNumber);
                messageArea.append("\nYear:" + aJournal.year);
                messageArea.append("\nOrganization:" + aJournal.organizer);
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
