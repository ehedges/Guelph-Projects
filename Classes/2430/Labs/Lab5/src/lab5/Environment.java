/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab5;

/**
 *
 * @author Harshavardhan
 */
public class Environment {
    
    private boolean lights = false;     //initialize lights to OFF
    private boolean fan = false;        //initialize fan to OFF
  
    public Environment(boolean lights, boolean fan){
        this.lights = lights;
        this.fan = fan;
                
    }
    
    public boolean getLights() {
        return lights;
    }
    
    public void toggleLights() {
        lights = !lights;       //toggle lights variable's value
    }
    
    public boolean getFan() {
        return fan;
    }
    
    public void toggleFan() {
        fan = !fan;              //toggle fan variable's value
    }
    
}
