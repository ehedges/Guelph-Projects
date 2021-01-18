with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with integer_linkedlist; use integer_linkedlist;

procedure unBound is


    numberInput : unbounded_string;

    operandOne: linkedListHead;
    operandTwo: linkedListHead;
    answer : linkedListHead;

    tempNum : integer;
    inputChar : character;

    procedure convertInput(inputValue : in unbounded_string; list : in out linkedListHead) is
    begin
    
           for i in 1..length(inputValue) loop

                
                if(element(inputValue,i) = '-') then

                    makeNeg(list);

                elsif((element(inputValue,i) = '+')) then    

                    makePos(list);

                else 

                    tempNum := integer'Value ((1 => element(inputValue,i)));
                    insertBack(tempNum,list);

                end if;

           end loop;          

    end convertInput;

begin

    loop

        clearList(operandOne);
        clearList(operandTwo);
        clearList(answer);

        put_line("Enter an operation: + , - , * or !. Enter Q to quit.");

        get(inputChar);

        get_line(numberInput);

        if (inputChar = 'Q') then

            exit;

        elsif (inputChar = '+') then
        
           put_line("Adding two numbers. Please Enter your first operand:");
           get_line(numberInput);

           convertInput(numberInput,operandOne);

           put_line("Please Enter your second operand:");
           get_line(numberInput);

           convertInput(numberInput,operandTwo);

           put_line("The Equation is:");
           displayList(operandOne);
           put_line(" ");
           put_line(" + ");
           displayList(operandTwo);

           addNums(operandOne,operandTwo,answer); 
          
           put_line("The Answer is");
           displayList(answer);
        elsif (inputChar = '-') then

           put_line("Subtracting two numbers. Please Enter your first operand:");
           get_line(numberInput);

           convertInput(numberInput,operandOne);

           put_line("Please Enter your second operand:");
           get_line(numberInput);

           convertInput(numberInput,operandTwo);

           put_line("The Equation is:");
           displayList(operandOne);
           put_line(" ");
           put_line(" - ");
           displayList(operandTwo);

           subNums(operandOne,operandTwo,answer); 
           put_line("The Answer is");
           displayList(answer);

        elsif (inputChar = '*') then

           put_line("Multiplying two numbers. Please Enter your first operand:");
           get_line(numberInput);

           convertInput(numberInput,operandOne);

           put_line("Please Enter your second operand:");
           get_line(numberInput);

           convertInput(numberInput,operandTwo);

           put_line("The Equation is:");
           displayList(operandOne);
           put_line(" ");
           put_line(" * ");
           displayList(operandTwo);
           
           multiNums(operandOne,operandTwo,answer); 
           put_line("The Answer is");
           displayList(answer);

        elsif (inputChar = '!') then

           put_line("Calculating factorial. Please Enter a number:");
           get_line(numberInput);
        else

           put_line("Error with input.");

        end if;

        put_line("");

    end loop;

end unBound;