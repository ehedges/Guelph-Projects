/*
 * Lab Assignment 5
   
   Author: Harsh
 */ 

package lab5;

import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import javax.swing.*;

public class Lab5 {
    JPanel cards; //a panel that uses CardLayout
    final static String Home1 = "Home 1"; 
    final static String Office = "Office";
    final static String Home2 = "Home 2";
    
    static JMenuItem menuItem;                  // a menuitem for the top level menu
    JLabel LWelcomeText = new JLabel("Welcome to Home 1");      //label to show current environment
    JLabel LCurrStatus = new JLabel("Current status");
    JLabel LLightStatus = new JLabel("Lights: ");
    JLabel LFanStatus = new JLabel("Fan: ");
    
    /**************initialize all three environments****************/
    Environment EHome1 = new Environment(true, false);              //In Home1, lights are ON and fans are OFF
    Environment EOffice = new Environment(false, true);             //In Home1, lights are OFF and fans are ON
    Environment EHome2 = new Environment(false, false);             //In Home2, lights are OFF and fans are OFF
    
    String comboBoxItems[] = { Home1, Office, Home2 };
    JComboBox envOptions = new JComboBox(comboBoxItems);
    
    public void addComponentToPane(Container pane) {
        //Put the JComboBox in a JPanel to get a nicer look.
        JPanel comboBoxPane = new JPanel(); //use FlowLayout
        JPanel status = new JPanel(); 
        
        //Set scroll pane flow from top to bottom.
        status.setLayout(new BoxLayout(status, BoxLayout.PAGE_AXIS));
        
        
        /*******************************create the status pane*************/
        
        //Center all three labels in their container
        LWelcomeText.setAlignmentX(Component.CENTER_ALIGNMENT);
        LWelcomeText.setForeground(Color.BLUE);
        LCurrStatus.setAlignmentX(Component.CENTER_ALIGNMENT);
        LCurrStatus.setForeground(Color.RED);
        LLightStatus.setAlignmentX(Component.CENTER_ALIGNMENT);
        LFanStatus.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        //Add these labels to the container, which is a JPanel
        status.add(LWelcomeText);
        status.add(LCurrStatus);
        status.add(LLightStatus);
        status.add(LFanStatus);
        
        /*****************************************************************/
        //initialize labels for program start
        initializeState();
        
        //listener for combo box
        //ItemListener is an interface containing the method itemStateChanged
        //this method is invoked when an event gets fired on the combo box
        envOptions.addItemListener(new ItemListener(){
            @Override
            public void itemStateChanged(ItemEvent e){
                //System.out.println(e.getItem() + " " + e.getStateChange() );
                
                //check which item in the combo box has been selected and load that environment's status
                /*****************************************************************/
                if(e.getItem().toString().equals("Home 1"))
                {
                    if(EHome1.getLights())
                        LLightStatus.setText("Lights: ON");
                    else
                        LLightStatus.setText("Lights: OFF");
                    
                    if(EHome1.getFan())
                        LFanStatus.setText("Fan: ON");
                    else
                        LFanStatus.setText("Fan: OFF");
                        
                }
                
                else if(e.getItem().toString().equals("Office"))
                {
                    if(EOffice.getLights())
                        LLightStatus.setText("Lights: ON");
                    else
                        LLightStatus.setText("Lights: OFF");
                    
                    if(EOffice.getFan())
                        LFanStatus.setText("Fan: ON");
                    else
                        LFanStatus.setText("Fan: OFF");
                    //write code similar to above, but for Office
                    //load Office's Lights and Fan statuses here
                        
                }
                
                if(e.getItem().toString().equals("Home 2"))
                {
                    if(EHome2.getLights())
                        LLightStatus.setText("Lights: ON");
                    else
                        LLightStatus.setText("Lights: OFF");
                    
                    if(EHome2.getFan())
                        LFanStatus.setText("Fan: ON");
                    else
                        LFanStatus.setText("Fan: OFF");
                    //write code similar to above, but for Office
                    //load Office's Lights and Fan statuses here
                        
                }
                
                /*****************************************************************/
                
                
                //initialize the cards in the CardLayout
                LWelcomeText.setText("Welcome to " + e.getItem());
                CardLayout cl = (CardLayout)(cards.getLayout());
                cl.show(cards, (String)e.getItem());
            }
        });
       
        comboBoxPane.add(envOptions);
        
        
        //this method creates our three cards (JPanels) for us
        createCards();
        
        //add the combo box at the top of the pane
        pane.add(comboBoxPane, BorderLayout.PAGE_START);
        
        //add the status pane at the center of the main container
        pane.add(status, BorderLayout.CENTER);
        
        //add the cards (3 panels containing Toggle buttons) at the bottom of the main container
        pane.add(cards, BorderLayout.PAGE_END);
    }
    
    /*
    Initializes the form using initial program state
    */
    private void initializeState() {
        if(envOptions.getSelectedItem().toString().equals("Home 1")) {
            if(EHome1.getFan())
                LFanStatus.setText("Fan: ON");
            else
                LFanStatus.setText("Fan: OFF");
            
            if(EHome1.getLights())
                LLightStatus.setText("Lights: ON");
            else
                LLightStatus.setText("Lights: OFF");
        }
         if(envOptions.getSelectedItem().toString().equals("Home 2")) {
            if(EHome2.getFan())
                LFanStatus.setText("Fan: ON");
            else
                LFanStatus.setText("Fan: OFF");
            
            if(EHome2.getLights())
                LLightStatus.setText("Lights: ON");
            else
                LLightStatus.setText("Lights: OFF");
        } 
          if(envOptions.getSelectedItem().toString().equals("Office")) {
            if(EHome2.getFan())
                LFanStatus.setText("Fan: ON");
            else
                LFanStatus.setText("Fan: OFF");
            
            if(EHome2.getLights())
                LLightStatus.setText("Lights: ON");
            else
                LLightStatus.setText("Lights: OFF");
        } 
    }
    
    private void createCards() {
        //Create the "cards".
        JPanel card1 = new JPanel();
        JButton lightsHome1 = new JButton("Toggle Lights");
        JButton fanHome1 = new JButton("Toggle Fan");
        card1.add(lightsHome1);
        card1.add(fanHome1);
        
        lightsHome1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
               EHome1.toggleLights();
               
               if(EHome1.getLights())
                  LLightStatus.setText("Lights: ON");
               else
                  LLightStatus.setText("Lights: OFF"); 
                
               
               Random rand = new Random();
               
               //toggle lights in Office with probability 1/5
               boolean val = rand.nextInt(5)==0;
               
               if(val) {
                   if(EOffice.getLights())
                       System.out.println("Lights in the Office were ON");
                   else
                       System.out.println("Lights in the Office were OFF");
                   
                   EOffice.toggleLights();
                   
                   if(EOffice.getLights())
                       System.out.println("Lights in the Office are now toggled to ON");
                   else
                       System.out.println("Lights in the Office are now toggled to OFF");
               }
               
               //run the random number generation again since probabilities are INDEPENDENT.
               val = rand.nextInt(5) == 0;
               
               if(val){
                   if(EHome2.getLights())
                       System.out.println("Lights in Home 2 were ON");
                   else
                       System.out.println("Lights in Home 2 were OFF");
                   
                   EHome2.toggleLights();
                   
                   if(EHome2.getLights())
                       System.out.println("Lights in Home 2 are now toggled to ON");
                   else
                       System.out.println("Lights in Home 2 are now toggled to OFF");
               }
                   
                   
            }
        });
        
        fanHome1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                EHome1.toggleFan();
                
                EOffice.toggleFan();
                
                EHome2.toggleFan();
               
            }
        });
        
        JPanel card2 = new JPanel();
        JButton lightsOffice = new JButton("Toggle Lights");
        JButton fanOffice = new JButton("Toggle Fan");
        card2.add(lightsOffice);
        card2.add(fanOffice);
        
        lightsOffice.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                 if(EHome1.getLights())
                  LLightStatus.setText("Lights: ON");
               else
                  LLightStatus.setText("Lights: OFF"); 
                
               
            }
        });
        
        JPanel card3 = new JPanel();
        JButton lightsHome2 = new JButton("Toggle Lights");
        JButton fanHome2 = new JButton("Toggle Fan");
        card3.add(lightsHome2);
        card3.add(fanHome2);
        
        lightsHome2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                 if(EHome1.getLights())
                  LLightStatus.setText("Lights: ON");
               else
                  LLightStatus.setText("Lights: OFF"); 
                
               
            }
        });
        
        fanHome2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                 if(EHome2.getLights())
                  LFanStatus.setText("Fan: ON");
               else
                  LFanStatus.setText("Fan: OFF"); 
                
               
            }
        });
        
        //Create the panel that contains the "cards".
        cards = new JPanel(new CardLayout());
        cards.add(card1, Home1);
        cards.add(card2, Office);
        cards.add(card3, Home2);
        
    }
    
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event dispatch thread.
     */
    private static void createAndShowGUI() {
        
        JMenuBar menuBar;
        JMenu menu, submenu;
        
        /**********menu code**********/
            
        //Create the menu bar.
        menuBar = new JMenuBar();

        //Build the first menu.
        menu = new JMenu("Menu");
        menu.setMnemonic(KeyEvent.VK_M);
        menuBar.add(menu);
        
        menuItem = new JMenuItem("Quit",
                         KeyEvent.VK_Q);
        menu.add(menuItem);
        
        menuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                quit();
            }
        });
        
        /*****************************/
        
        //Create and set up the window.
        JFrame frame = new JFrame("CardLayoutDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        //Create and set up the content pane.
        Lab5 demo = new Lab5();
        demo.addComponentToPane(frame.getContentPane());
        
        frame.setJMenuBar(menuBar);
        
        //Display the window.
        frame.pack();
        frame.setVisible(true);
        
        // frame.setJMenuBar(menuBar);

    }
    
    private static void quit() {
        
        System.exit(0);
    }
    
    public static void main(String[] args) {
        /* Use an appropriate Look and Feel */
        try {
            //UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
            UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
        } catch (UnsupportedLookAndFeelException ex) {
            ex.printStackTrace();
        } catch (IllegalAccessException ex) {
            ex.printStackTrace();
        } catch (InstantiationException ex) {
            ex.printStackTrace();
        } catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }
        /* Turn off metal's use of bold fonts */
        UIManager.put("swing.boldMetal", Boolean.FALSE);
        
        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}
