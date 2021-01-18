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
 * PaintingGalleries do not buy any paintings from other galleries.
 * They also do not have any sculptures.
 */
public class PaintingGallery extends AbstractArtGallery {
    
     public PaintingGallery(int id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public void listPaintings() {
        //write code to list gallery's paintings here
        
         for(int i=0; i<paintings.size();i++) {
            System.out.println(paintings.get(i).getName());
        }
    }
    
}
