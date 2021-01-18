/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Evan Hedges, origional code proviuded by Fei Song
 */
public class Assignment3 {

    /**
     * Tests args navigate to the source code in file assignment2 type javac
     * *.java back out,then java assignment2.Assignment2 textfile.txt
     * textfile.txt
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        LibrarySearch library = new LibrarySearch();
        String fileName = null;
        String inputFile = null;
        Scanner input = new Scanner(System.in);
        String test = "124ERERrtrtr";
        String command;

        Boolean savedData = true;
        int i = 0;

        System.out.print("Check number of arguments...");

        for (String s : args) {
            System.out.println(s);
            System.out.print(i + "\n");
            i++;
            if (i == 1 && inputFile == null) {
                inputFile = s;
                System.out.print("\nFile:" + inputFile + "\n");
            }

            fileName = s;
        }
        System.out.print("Arguments found:" + i);
        System.out.print("\nFile:" + fileName + "\n");
        /* If there is an input and output file, otherwise just output*/
        if (i > 1 && inputFile != null) {
            System.out.print("Uploading input file" + inputFile + "\n");
            savedData = library.savedData(inputFile);
        } else if (i > 0 && fileName != null && fileName.matches(inputFile) == true) {
            System.out.print("Uploading input file" + inputFile + "\n");
            savedData = library.savedData(fileName);
        }
        /* Main beginning of the program*/

        /*First menu*/
        if (i < 3) {
            do {
                System.out.print("Enter add, search, or quit> ");
                command = input.nextLine();
                if (command.equalsIgnoreCase("add") || command.equalsIgnoreCase("a")) {
                    library.add(input, fileName);
                } else if (command.equalsIgnoreCase("search") || command.equalsIgnoreCase("s")) {
                    library.search(input);
                }
            } while (!command.equalsIgnoreCase("quit") && !command.equalsIgnoreCase("q"));
        } else {
            System.out.print("Too many arguments");
        }
    }
}
