package assignment2;

import java.awt.*;
import java.awt.event.*;
import javax.swing.Box;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

class GUI extends JFrame implements ActionListener {

    Button addButton, resetButton;
    TextArea messageArea;//
    JTextField callNumArea, authorsArea, titleArea, publisherArea, organizationArea, yearArea, endArea;
    JLabel welcomeLabel, callNumLabel, authorsLabel, titleLabel, publisherLabel, organizationLabel, yearLabel, choiceLabel, referenceLabel, yearEndLabel;
    JPanel southPanel, rightPanel, leftPanel, topPanel, centerPanel, callNumPanel, authorsPanel, titlePanel, publisherPanel, organizationPanel, yearPanel, choicePanel, yearEndPanel;
    JComboBox choice;
    String[] strings = {"Book", "Jounral"};
    JMenuBar commandsMenuBar;
    JMenu commands;
    JMenuItem Add, Search, Quit;
    Box verticalBox;
    int textAreaHeight;
    LibrarySearch library = new LibrarySearch();

    GUI() {

        super("Library Search");//

        choice = new JComboBox(strings);
        setLayout(new BorderLayout());//
        setSize(600, 800);//
		/*Creates start up */
        welcomeLabel = new JLabel("<html>   Welcome to Library Search!<BR> Choose a command from the \"Commands\" menu above for adding a reference, searching reference, or quitting the program.<html> ");
        referenceLabel = new JLabel("Adding a reference");
        add(welcomeLabel);
        commandsMenuBar = new JMenuBar();
        commands = new JMenu("Commands");
        commandsMenuBar.add(commands);
        add(commandsMenuBar, BorderLayout.NORTH);

        /*Adds to menu*/
        Add = new JMenuItem("Add");
        Search = new JMenuItem("Search");
        Quit = new JMenuItem("Quit");
        commands.add(Add);
        commands.add(Search);
        commands.add(Quit);
        choice.addActionListener(this);
        Add.addActionListener(this);
        Search.addActionListener(this);
        Quit.addActionListener(this);

        /*Creates the buttons and the text area*/
        addButton = new Button("Add");//
        resetButton = new Button("Reset");
        messageArea = new TextArea("");//
        rightPanel = new JPanel();

        /*Adds the buttons to the panel*/
        rightPanel.setLayout(new BorderLayout());
        rightPanel.add(addButton, BorderLayout.NORTH);
        rightPanel.add(resetButton, BorderLayout.SOUTH);
        /*Creates the fields*/
        callNumArea = new JTextField();
        authorsArea = new JTextField();
        titleArea = new JTextField();
        publisherArea = new JTextField();
        organizationArea = new JTextField();
        yearArea = new JTextField();
        endArea = new JTextField();

        /*adds to the panel*/
        leftPanel = new JPanel();
        leftPanel.setLayout(new GridLayout());

        /*pairs the panels to the labels*/
        callNumLabel = new JLabel("Call No.:");
        callNumPanel = new JPanel();
        callNumPanel.setLayout(new FlowLayout());
        callNumPanel.add(callNumLabel);
        callNumPanel.add(callNumArea);

        authorsLabel = new JLabel("Authors:");
        authorsPanel = new JPanel();
        authorsPanel.add(authorsLabel);
        authorsPanel.add(authorsArea);

        titleLabel = new JLabel("Title:");
        titlePanel = new JPanel();
        titlePanel.add(titleLabel);
        titlePanel.add(titleArea);

        publisherLabel = new JLabel("Publisher:");
        publisherPanel = new JPanel();
        publisherPanel.add(publisherLabel);
        publisherPanel.add(publisherArea);

        yearLabel = new JLabel("Year:");
        yearPanel = new JPanel();
        yearPanel.add(yearLabel);
        yearPanel.add(yearArea);

        yearEndLabel = new JLabel("Year End:");
        yearEndPanel = new JPanel();
        yearEndPanel.add(yearEndLabel);
        yearEndPanel.add(endArea);

        choiceLabel = new JLabel("Type:");
        choicePanel = new JPanel();
        choicePanel.add(choiceLabel);
        choicePanel.add(choice);

        organizationLabel = new JLabel("Organization:");
        organizationPanel = new JPanel();
        organizationPanel.add(organizationLabel);
        organizationPanel.add(organizationArea);

        /*Gets the default height, sets sizes*/
        textAreaHeight = callNumArea.getHeight();
        callNumArea.setColumns(20);
        authorsArea.setColumns(20);
        titleArea.setColumns(20);
        publisherArea.setColumns(20);
        organizationArea.setColumns(20);
        yearArea.setColumns(20);
        endArea.setColumns(20);

        /*adds to a vertical box so they stack*/
        verticalBox = Box.createVerticalBox();
        verticalBox.add(referenceLabel);
        verticalBox.add(choicePanel);
        verticalBox.add(callNumPanel);
        verticalBox.add(titlePanel);
        verticalBox.add(yearPanel);
        verticalBox.add(yearEndPanel);
        verticalBox.add(publisherPanel);
        verticalBox.add(authorsPanel);
        /*Add the box to the panel*/
        leftPanel.add(verticalBox);
        /*Add to program*/
        add(leftPanel, BorderLayout.WEST);
        add(rightPanel, BorderLayout.EAST);
        add(messageArea, BorderLayout.SOUTH);
        /*Actions*/
        addButton.addActionListener(this);//
        resetButton.addActionListener(this);

        rightPanel.setVisible(false);
        leftPanel.setVisible(false);
        messageArea.setVisible(false);
        yearEndPanel.setVisible(false);

        addWindowListener(new WindowAdapter() {//
            @Override
            public void windowClosing(WindowEvent e) {

                setVisible(false);//
                System.exit(0);//
            }
        });
        setVisible(true);//
    }

    public void actionPerformed(ActionEvent e) {
        /*strings to send*/
        String author = new String();
        String callNumber = new String();
        String title = new String();
        String publisher = new String();
        String Organization = new String();
        String year = new String();
        String endYear = new String();
        String[] keywords = null;
        Boolean result = false;
        int start = 0;
        int end = 0;

        /*Removes teh greeting message and strats up*/
        welcomeLabel.setVisible(false);
        messageArea.setVisible(true);
        rightPanel.setVisible(true);
        leftPanel.setVisible(true);
        /*Choose between journal and book*/
        if (choice.getSelectedIndex() == 0) {
            authorsPanel.setVisible(true);
            publisherLabel.setText("Publisher:");
        }
        if (choice.getSelectedIndex() == 1) {
            authorsPanel.setVisible(false);
            publisherLabel.setText("Organization:");
        }

        /* Handle buttons*/
        if (e.getSource() == addButton) {//

            if (addButton.getLabel().matches("Add")) {
                try {
                    callNumber = callNumArea.getText();
                    title = titleArea.getText();
                    year = yearArea.getText();
                    author = authorsArea.getText();
                    publisher = publisherArea.getText();

                    if (choice.getSelectedIndex() == 0 && callNumber.length() > 0 && title.length() > 0 && year.length() == 4) {
                        library.add(callNumber, title, publisher, year, author, "Book", messageArea);
                        messageArea.setText(" ");
                    } else if (choice.getSelectedIndex() == 1 && callNumber.length() > 0 && title.length() > 0 && year.length() == 4) {
                        library.add(callNumber, title, publisher, year, author, "Journal", messageArea);
                        messageArea.setText(" ");
                    } else {
                        messageArea.setText("Error when adding");
                    }
                } catch (Exception ex) {
                    messageArea.setText("Error when adding");
                }

            } else if (addButton.getLabel().matches("Search")) {
                callNumber = callNumArea.getText();
                title = titleArea.getText();
                year = yearArea.getText();
                author = authorsArea.getText();
                keywords = title.split("[ ,\n]+");

                try {
                    start = Integer.parseInt(yearArea.getText());
                } catch (Exception ex) {
                }
                try {
                    end = Integer.parseInt(endArea.getText());
                } catch (Exception ex) {
                }
                System.out.println(start);
                endArea.setVisible(true);
                library.search(callNumber, keywords, start, end, messageArea);
                System.out.println("Search");

            }

        }
        /*sets everything blank*/
        if (e.getSource() == resetButton) {//
            messageArea.setText(" ");
            callNumArea.setText("");
            authorsArea.setText("");
            titleArea.setText("");
            publisherArea.setText("");
            organizationArea.setText("");
            yearArea.setText("");
            endArea.setText("");
        }
        /*Switches add button to search and back hides some panels as well*/
        if (e.getSource() == Add) {
            referenceLabel.setText("Adding a reference");
            addButton.setLabel("Add");
            yearLabel.setText("Year:");
            yearEndPanel.setVisible(false);
            publisherPanel.setVisible(true);
            choicePanel.setVisible(true);
            if (choice.getSelectedIndex() != 0) {
                authorsPanel.setVisible(false);
            } else {
                authorsPanel.setVisible(true);
            }
        }
        if (e.getSource() == Search) {//  
            referenceLabel.setText("Search a reference");
            addButton.setLabel("Search");
            yearLabel.setText("Year Start:");
            yearEndPanel.setVisible(true);
            publisherPanel.setVisible(false);
            choicePanel.setVisible(false);
            if (choice.getSelectedIndex() != 0) {
                authorsPanel.setVisible(false);
            } else {
                authorsPanel.setVisible(true);
            }

        }

        if (e.getSource() == Quit) {//
            setVisible(false);
            System.exit(0);
        }

    }

    public static void main(LibrarySearch library) {

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new GUI();
            }
        });
    }
}
