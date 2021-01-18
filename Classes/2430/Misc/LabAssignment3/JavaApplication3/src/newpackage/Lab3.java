/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package newpackage;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;


/**
 *
 * @author Harshavardhan
 */
public class Lab3 {
    
    public static void main(String args[]) {
        
        ArrayList<ArtGallery> artGalleries = new ArrayList<ArtGallery> ();
        ArrayList<PaintingGallery> paintingGalleries = new ArrayList<PaintingGallery>();
        
        ArtGallery tempArt = new ArtGallery(0,"NY", 2000);
        artGalleries.add(tempArt);
        
        tempArt = new ArtGallery(1,"Toronto", 5000);
        artGalleries.add(tempArt);
        
        PaintingGallery tempPaint = new PaintingGallery(2,"Vancouver");  
        paintingGalleries.add(tempPaint);
        
        tempPaint = new PaintingGallery(3,"Seattle");  
        paintingGalleries.add(tempPaint);
        
        String tempInput = new String();
        String painter = new String();
        String paintingName = new String();
        int index = 0;
        
        int price = 0;
        int quit = 0;

        String fileName = "test.txt";
        //Begin by creating two ArrayLists. 
        //One will hold two ArtGallery objects.
        //Assign them IDs, Names and Funds of 0,NY,2000
        //and 1,Toronto,5000 respectively.0
        
         //The second ArrayList will hold two PaintingGallery objects.
        //Assign them IDs and Names of 2, Vancouver
        //and 3, Seattle respectively.
        
        BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));
        int galleryChoice = 0;
        int opChoice = 0;
        
        while(galleryChoice != 4) {
            
            opChoice = 0;
            
            //print first menu
            System.out.println("\nSelect an art gallery supermarket or press 4 to exit: "
                    + "\n0. NY" 
                    + "\n1. Toronto"
                    + "\n2. Vancouver"
                    + "\n3. Seattle");
            
            try {
                galleryChoice = Integer.parseInt(scan.readLine());
                
                //exit if user selects 4
                if(galleryChoice == 4) {
                    System.exit(0);
                }
                else if(galleryChoice == 0 || galleryChoice == 1)
                {
                //print message if invalid user choice
               
                    while(opChoice != 6) {
                    
                        //show second menu
                        System.out.println("\nSelect an operation: "
                            + "\n1. List Paintings"
                            + "\n2. Add Paintings" 
                            + "\n3. List Sculptures"        //show this only for ArtGalleries, not PaintingGalleries 
                            + "\n4. Add Sculptures"         //show this only for ArtGalleries, not PaintingGalleries 
                            + "\n5. Buy Paintings"          //show this only for ArtGalleries, not PaintingGalleries 
                            + "\n6. Back to gallery selection");

                        opChoice = Integer.parseInt(scan.readLine());
            
                         switch(opChoice) {
                            case 1: 
                                     System.out.println("The paintings are:\n");
                                    artGalleries.get(galleryChoice).listPaintings();
                                break;

                            case 2: 
                                
                                System.out.println("Please input the painter's name.\n");
                                painter = scan.readLine();
                                System.out.println("Please input the painting's name.\n");
                                paintingName = scan.readLine();
                                System.out.println("Please input the pricee.\n");                       
                                price = Integer.parseInt(scan.readLine());
                                Painting tempPainting = new Painting(painter,paintingName,price);                                
                                artGalleries.get(galleryChoice).addPainting(fileName,tempPainting);
                                //add the painting to selected gallery
                            case 3:
                                artGalleries.get(galleryChoice).listSculptures();
                                break;
                            case 4:
                                System.out.println("Please input the sculpturer's name.\n");
                                painter = scan.readLine();
                                System.out.println("Please input the sculpture's name.\n");
                                paintingName = scan.readLine();
                                System.out.println(galleryChoice);
                                Sculpture tempSculpture = new Sculpture(paintingName,painter);
                                artGalleries.get(galleryChoice).addSculpture(fileName,tempSculpture);
                                break;
                         case 5:
                                System.out.println("Please input the gallery index.\n");
                                index = Integer.parseInt(scan.readLine());
                                if(index !=galleryChoice)
                                {
                                    System.out.println("Please input the painting name.\n");
                                    tempInput  = scan.readLine();
                                    artGalleries.get(galleryChoice).buy( artGalleries.get(index),artGalleries.get(galleryChoice), tempInput);
                                }
                                else
                                {
                                    System.out.println("Trying to buy from the same gallery.\n");
                                }
                                break; 
                          default:
                                if(opChoice != 6)
                                {
                                System.out.println("invalid input : Art Galleries\n");
                                }
                        }

                  }
                }
                
                else if(galleryChoice == 2 || galleryChoice == 3)
                {
                //print message if invalid user choice
               
                    while(opChoice != 6) {
                    
                        //show second menu
                        System.out.println("\nSelect an operation: "
                            + "\n1. List Paintings"
                            + "\n2. Add Paintings" 
                            + "\n6. Back to gallery selection");
                        opChoice = Integer.parseInt(scan.readLine());
                         switch(opChoice) {
                            case 1: 
                                     System.out.println("The paintings are:\n");
                                    paintingGalleries.get(galleryChoice-2).listPaintings();
                                break;

                            case 2: 
                                
                                System.out.println("Please input the painter's name.\n");
                                painter = scan.readLine();
                                System.out.println("Please input the painting's name.\n");
                                paintingName = scan.readLine();
                                System.out.println("Please input the pricee.\n");                       
                                price = Integer.parseInt(scan.readLine());    
                                Painting tempPainting = new Painting(painter,paintingName,price);                                
                                paintingGalleries.get(galleryChoice-2).addPainting(fileName,tempPainting);
                                //add the painting to selected gallery
                                break;
 
                          default:
                                if(opChoice != 6)
                                {
                                System.out.println("invalid input: Art Gallery\n");
                                }
                        }

                  }
                }
            
            } catch (Exception ex) {
               
                 System.out.println("\nInvalid input: Choice\n");
                
            }
            
        }
    }
    
}
