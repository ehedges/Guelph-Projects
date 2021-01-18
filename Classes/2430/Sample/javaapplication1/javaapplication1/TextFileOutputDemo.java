/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;

import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

public class TextFileOutputDemo {

    public static void main(String[] args) {
        PrintWriter outputStream = null;
        //outputStream
        //            = new PrintWriter(new FileOutputStream("stuff.txt"));
        try {
           outputStream
                    = new PrintWriter(new FileOutputStream("stuff.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("Error opening the file stuff.txt.");
            System.exit(0);
        }

        System.out.println("Writing to file.");

        outputStream.println("The quick brown fox");
        outputStream.println("jumped over the lazy dog.");

        outputStream.close();

        System.out.println("End of program.");
    }
}
