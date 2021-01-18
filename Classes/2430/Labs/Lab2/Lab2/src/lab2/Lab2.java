/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab2;

import java.util.Scanner;
import java.util.StringTokenizer;
/**
 *
 * @author Evan Hedges 0898140
 */
public class Lab2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        int value = 0;
        int stringLength = 0;
        
        boolean exist = false;
        
        
        String string = "";
       //Loops through the options
        while (value == 0)
        {    
            System.out.println("\nChoose a number:\n1. Input String \n2. Print String \n3. Reverse the String \n4. Tokenize String\n5. Count spaces in the string\n6. Check for a number in the string\n7. Count Vowels\n8. Count Consonants\n9. Exit Program!\n");

            Scanner scan = new Scanner(System.in);
            String input = scan.nextLine();
        
       
        //String length at the bottom o the switch
            switch (input)
            {
          
                case "1":
                //input string
                    do
                    {
                        System.out.println("\nPlease input a string:\n");
                        Scanner stringInput = new Scanner(System.in);
                        string = stringInput.nextLine();
                        exist = true;
                    }
                    while("".equals(string));
                    break;
                
                case "2":
                    //print
                    if (exist==true)
                    {
                    
                        System.out.println(string);
                
                    }
                    else
                    {
                
                        System.out.println ("\nNo string exists\n");
                        
                    }
                
                   break;
                
                case "3":
                    //reverse
                    if (exist==true)
                    {
                           
                        String reverseString = "";
                
                                
                    for (int i = stringLength-1; i >= 0 ;i--)
                    {
                   
                        reverseString += string.charAt(i);
                                           
                    }
                
                        string = reverseString;
                    
                        System.out.println(string);
                
                    }
                    else
                    {
                    
                        System.out.println("\nNo string exists\n");
                
                    }
                    break;
                
                case "4":
                    //TOkenize, remove spaces.
                    if (exist==true)
                    {
                                  
                    
                        StringTokenizer tokens = new StringTokenizer(string, " ");
                           
                        int numTokens =  tokens.countTokens(); 
                        
                        System.out.println("Total number of tokens found: " + numTokens);
                        
                        for (int i = 0; i<numTokens; i++)
                        {
                                                   
                            System.out.println(tokens.nextToken());
                            
                        
                        }
                        
                    System.out.println("Total number of tokens found: 0");
                    
                    }
                    else
                    {
                    
                        System.out.println("\nNo string exists\n");
                
                    }
                    break;
                
                case "5":
                    //count the number of spaces.
                    if (exist==true)
                    {
                
                    
                        int numTokens = 0;
                
                        for (int i = stringLength-1; i >= 0 ;i--)
                        {
                        
                            if(string.charAt(i) == ' ' || string.charAt(i) == '\t')
                            {
                            
                                numTokens++;
                            
                            }
                        
                        }
                        System.out.println("Num of spaces "+numTokens+".");

                    }
                    else
                    {
                 
                        System.out.println("\nNo string exists\n");
                
                    }
                    break;
                
                case "6":
                    //CHeck to see if there is digits.          
                    if (exist==true)
                    {               
                        
                        System.out.println(string.matches("(.)*(\\d)(.)*"));
                    
                
                    }
                    else
                    {
                
                        System.out.println("\nNo string exists\n");
                
                    }
                break;
                
                case "7":
                    //CHeck for vowels.
                    if (exist==true)
                    {
                
                        String vowels ="aeiouAEIOU";
                        
                        int vowelCount = 0;
                    
                        for (int i = stringLength-1; i >= 0 ;i--)
                        {
                   
                            for( int j = vowels.length()-1; j >=0;j -- )
                            {
                             
                                if(string.charAt(i) == vowels.charAt(j))
                                {
                                    
                                    vowelCount++;
                                    
                                }
                            
                            }
                            
                        }
                
                        System.out.println("There are " + vowelCount + " vowels.");
                    }
                    else
                    {
                 
                        System.out.println("\nNo string exists\n");
                    }
                    break;
                
                case "8":
                    //CHeck for consanents.
                    if (exist==true)
                    {
                
                        String consonants ="qwrtypsdfghjklzxcvbnmQWRTYPSDFGHJKLZXCVBNM";
                        
                        int consonantsCount = 0;
                    
                        for (int i = stringLength-1; i >= 0 ;i--)
                        {
                   
                            for( int j = consonants.length()-1; j >=0;j -- )
                            {
                             
                                if(string.charAt(i) == consonants.charAt(j))
                                {
                                    
                                    consonantsCount++;
                                    
                                }
                            
                            }
                            
                        }
                
                        System.out.println("There are " + consonantsCount + " consonants.");
                 
                    }
                    else
                    {
                
                        System.out.println("\nNo string exists\n");
                
                    }
                    break;
                
                case "9":
                    //Quit
                    System.out.println("Quitting...");
                    value = 1;
               
                    break;
                default:
                    System.out.println("\nInvalid input");
                

                
            }
        
        stringLength = string.length();  
        
        }
    }
    
}
