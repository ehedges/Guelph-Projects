/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package newpackage;

/**
 *
 * @author Harshavardhan
 */
//using this interface inserts a compile time check to ensure 
//that classes implementing this interface implement ALL its methods
public interface IAddPainting {
    
    
    //Are these declarations correct?
    
    void addPainting(String fileName, Painting newPainting);
    void catalogItem(String fileName, String itemName, String itemCreatorName,int price);
    void listPaintings();
    
}
