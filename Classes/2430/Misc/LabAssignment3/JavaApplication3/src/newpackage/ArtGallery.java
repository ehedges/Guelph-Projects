/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package newpackage;

import java.util.ArrayList;

/**
 *
 * @author Harshavardhan
 * This concrete class implements methods specific to itself.
 * Since only ArtGalleries in the problem can buy paintings from other ArtGalleries,
 * and since PaintingGalleries cannot, we include that method here since it is 
 * specific to only ArtGalleries.
 * 
 * This class implements IAddSculpture because only the ArtGallery has sculptures.
 */
public class ArtGallery extends AbstractArtGallery implements IAddSculpture{
    
    int availableFunds;
    
    public ArtGallery(int id, String name, int availableFunds) {
        this.id = id;
        this.name = name;
        this.availableFunds = availableFunds;
    }
    
    public int getId() {
        return id;
    }
    
    public int getAvailableFunds() {
        return availableFunds;
    }
    
    public void setAvailableFunds(int newFunds) {
        availableFunds = newFunds;
    }
    
    
    public String getName() {
        return name;
    }
    
    public ArrayList<Painting> ggetPaintings() {
        return paintings;
    }
    
    public ArrayList<Sculpture> getSculptures() {
        return sculptures;
    }
     
    
    @Override
    public void addSculpture(String fileName, Sculpture newSculpture) {
        storeSculpture(newSculpture);
        int price=0;
        catalogItem(fileName, newSculpture.getName(), newSculpture.getSculptorName(), price);
    }
    
    @Override
    public void listPaintings() {
        for(int i=0; i<paintings.size();i++) {
            System.out.println(paintings.get(i).getName());
        }
    }

    public void storeSculpture(Sculpture newSculpture) {
       //write codes to add sculpture object to ArrayList of sculptures 
        sculptures.add(newSculpture);
    }
    
    @Override
    public void listSculptures() {
        for(int i=0; i< sculptures.size();i++) {
            System.out.println(sculptures.get(i).getName());
        }
    }
    
    public void buy(ArtGallery source, ArtGallery destination, String paintingName) {
        
        //write code to transfer painting from source to destination.
        //Do this by searching the painting in the source list. If found,
        //fetch its price and check if destination has funds available to buy
        //Do defensive programming as usual
        //once painting has been transferred from source to destination
        //decrement destination's funds and increment source's funds
        //by amount equal to the price of the painting
        
        
        
        int i = 0;
        int index = 0;
        
        for (i=0; i<source.paintings.size(); i++)
        {
            
            Painting temp = source.paintings.get(i);
            String tempString = temp.getName();
            if(tempString.equals(paintingName))
            {
                if(destination.availableFunds >= temp.getPrice())
                {
                    
                    destination.availableFunds = destination.availableFunds - temp.getPrice();
                    source.availableFunds += temp.getPrice();
                    index = source.paintings.indexOf(temp);
                    destination.paintings.add(temp);
                    source.paintings.remove(index);
                }
                        
                else
                {
                    System.out.println("Not enough money.\n");
                }
            }
            else
            {
                System.out.println("The paiting does not exist.\n");
            }
        }
        
       //begin for loop 
            
            
        //find painting    
           
                //painting found. now check if destination has funds to buy
        //check if funds are available to buy     
                    
                    //destination has funds. 
                    //now transfer painting from source to destination 
                    
        //add painting to destination
             
        //remove from source gallery          
                    
        //decrement funds of destination by amount equal to price of painting
                    
        //increment funds of destination by amount equal to price of painting
                    
                    
                    //transaction complete
                
            
        
        
    }
    
}
