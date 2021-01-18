with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Text_IO; use Ada.Text_IO;

--https://rosettacode.org/wiki/Singly-linked_list/Element_insertion#Ada Used as base.

-- Value refers to the actual data in the node. Number is the entire list.
-- inked list implemntation has the one column at the tail. 
package body integer_linkedlist  is
    
--  This function determines whether the number is positive or negative.
    function isPositive(list: in linkedListHead) return boolean is
    begin

        return list.isPositive;

    end isPositive;

--  Changes sign to positive.
    procedure makePos(list: in out linkedListHead) is
    begin

        list.isPositive := true;

    end makePos;

--  Changes sign to negative.
    procedure makeNeg(list: in out linkedListHead) is
    begin

        list.isPositive := false;

    end makeNeg;

--  CInserts to back of list.
    procedure insertBack(data: in integer; list: in out linkedListHead) is
    
    insertNode : linkAccess;
    tempNode : linkAccess;

    begin
        
        insertNode := new linkNode;

--Incase it is the first node.
        if list.length = 0 then

            list.tail := insertNode;
            list.head := insertNode;

            insertNode.data := data;

        else
--Otherwise insert back.
            tempNode := list.tail;
            tempNode.next := insertNode;

            insertNode.next := NULL;
            insertNode.prev := tempNode;
            insertNode.data := data;

            list.tail := insertNode;

        end if;

        list.length := list.length+1;

    end insertBack;
--Inserts to teh front of list
    procedure insertFront(data: in integer; list: in out linkedListHead) is

    insertNode : linkAccess;
    tempNode : linkAccess;

    begin
--Incase it is the first node.       
        insertNode := new linkNode;

        if list.length = 0 then

            list.tail := insertNode;
            list.head := insertNode;

            insertNode.data := data;

        else
--Insert at the head
            tempNode := list.head;
            tempNode.prev := insertNode;

            insertNode.next := tempNode;
            insertNode.prev := NULL;
            insertNode.data := data;

            list.head := insertNode;

        end if;

        list.length := list.length+1;

    end insertFront;

-- Removes from front
    procedure removeFront(list: in out linkedListHead) is

    tempNode : linkAccess;

    begin

        tempNode := list.head;
        tempNode := tempNode.next;
        tempNode.prev := NULL;
        list.head:= tempNode;
        list.length := list.length-1;

    end removeFront;

--Prints out the list to the console.
    procedure displayList(list: in out linkedListHead) is

    numString :  unbounded_string;
    tempNode : linkAccess;

    stringCount: integer; 

    begin
    
        tempNode := list.tail;
        stringCount := 0;

        delete(numString,1,length(numString));

--Loop through the list, converting the integer to a string
        while tempNode /= NULL loop
            
            insert(numString,1,Integer'Image(tempNode.data));

            tempNode := tempNode.prev;
            stringCount := stringCount+1;

        end loop;

-- Prints the negative sign if the number is negative        
        if(isPositive(list) = false) then

            insert(numString,1,"-");

        end if;
 
        put(numString);

    end displayList;

-- Gets tthe length
    function getLength(list: in linkedListHead) return integer is
    begin

        return list.length;

    end getLength;

--Cleans the list, nothing remains
    procedure clearList(list: in out linkedListHead) is
    begin

        list.length := 0;
     
        list.isPositive := true;

        list.head := NULL;
        list.tail := NULL;

    end clearList;

--Copies a list.
    procedure copyList(newCopy: in out linkedListHead; oldCopy: in linkedListHead) is

    tempNode : linkAccess;
    begin

        clearList(newCopy);

        tempNode := oldCopy.head;

        --Adding some changes here, dopuble check does not break stuff.

        newCopy.isPositive := oldCopy.isPositive;

        for i in integer range 1..oldCopy.length loop

            if tempNode /= NULL then

                 insertBack(tempNode.data,newCopy);

                 tempNode :=  tempNode.next;

            end if;

        end loop;

    end copyList;

--Adds two numbers together. NOTE: SUBTRACTION DOES USE THIS FUNCTION. Explained below.
    procedure addNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;
    tempHead : linkedListHead;
    loopLength : integer;
    carry: integer;
    tempAnswer: integer;

    begin
--Ensures that the answer is blank.

        clearList(answer);

--If both operands are the same we can add normally. If they are not, then we must subtract

        if operandOne.isPositive = operandTwo.isPositive then

            answer.isPositive := operandOne.isPositive;
            tempNode := operandOne.tail;
            tempTwo := operandTwo.tail;

            loopLength := operandOne.length;

--Ensures that the top number is always the larger of the two.

            if operandOne.length < operandTwo.length then

                loopLength := operandTwo.length;

            end if;

            carry := 0;
            tempAnswer := 0;

--Calculating addition here  
     
            for i in integer range 1..loopLength loop

-- 3 Cases, First is the normal addition of two numbers.

                if tempTwo /= NULL and tempNode /= NULL then
 
                    tempAnswer := tempTwo.data + tempNode.data + carry;
                    tempTwo := tempTwo.prev;               
                    tempNode := tempNode.prev;

--Second is when the second operand is smaller and runs out. Since the number is smaller, we can just carry them over.

                elsif tempNode /= NULL then

                     tempAnswer := tempNode.data + carry;
                     tempNode := tempNode.prev;

--Third, Same as the previous option, but the other list incase something messes up.

                elsif tempTwo /= NULL then

                     tempAnswer := tempTwo.data + carry;
                     tempTwo := tempTwo.prev; 

                end if;

-- If the two numbers are larger than 10, we carry here.
        
                carry := 0;

                if tempAnswer > 9 then

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;

                end if;

--Used when subtracting, Does the negative carry.

                if tempAnswer < 0 then

                    carry := -1;
                    tempAnswer := tempAnswer mod 10;

                end if;

                insertFront(tempAnswer,answer);

            end loop;  
     
--Incase the last two numbers are larger than 10.

            if carry > 0 then

                 while tempAnswer > 9 or tempAnswer < -9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;
                    insertFront(tempAnswer,answer);

                 end loop;

                insertFront(carry,answer);

            end if;

--Incase the last two numbers needed a carry;

            if carry < 0 then

                tempNode := answer.head;
                tempNode.data := tempNode.data-1;

            end if;

        else 

-- If we are adding a negative and a positive number, it is essentially subtraction

            tempHead := operandTwo;
            flipSign(tempHead);
            subNums(operandOne,tempHead,answer);

        end if;

    end;

--Calculating subtraction. 
--NOTE: When subtracting we are adding a negative number to positive number. Therefore, by flipping the sign on each value and sending that to addition, it is subtraction.
--e.g 1-1 = 1+(-1) , 2 -(-2) = 2+2, etc.

    procedure subNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;
    tempHead : linkedListHead;

--The purpose behind these two vars is to get rid of the annoying warning: actuals for this call may be in wrong order
    tempListGetRidOfWarningA : linkedListHead;
    tempListGetRidOfWarningB : linkedListHead;

    begin

        clearList(answer);

--Check if the two are the same sign, if they are, subtract normally.

        if operandOne.isPositive = operandTwo.isPositive then

            answer.isPositive := operandOne.isPositive;

            tempNode := operandOne.head;
            tempTwo := operandTwo.head;

--Following statements ensures that the large numbers on top.


--This one indicate the first number is longer, there fore larger and will remain the same sign. We then flip the sign on each value and add. 

            if operandOne.length > operandTwo.length then

                for i in integer range 1..operandTwo.length loop

                    tempTwo.data := tempTwo.data*(-1);
                    tempTwo := tempTwo.next;

                end loop;

                addNums(operandOne,operandTwo,answer);

--This one indicates that the second number is longer, so we know that the sign will be inverse. 
--e.g. 4-6 = -2 and (-4)-(-6) = -2

            else if operandOne.length < operandTwo.length then
                
                for i in integer range 1..operandOne.length loop

                    tempNode.data := tempNode.data*(-1);
                    tempNode := tempNode.next;

                end loop;

--Second list is large so subtract the first from the second.

                tempListGetRidOfWarningA := operandOne;
                tempListGetRidOfWarningB := operandTwo;

                addNums(tempListGetRidOfWarningB,tempListGetRidOfWarningA,answer);

                flipSign(answer);

            else

--If the numbers are the same length, we must find a larger value. This iterates over comparing the two.

                for i in integer range 1..operandOne.length loop

--Checks to ensure we have valid nodes. The loops and such are copied from above, similair ideas.

                        if tempNode /= NULL and tempTwo /= NULL then

--Checks to see first list is larger. 
--This one indicate the first number is longer, there fore larger and will remain the same sign. We then flip the sign on each value and add. 

                             if tempNode.data > tempTwo.data then

                                tempTwo := operandTwo.head;

                                for i in integer range 1..operandTwo.length loop

                                    tempTwo.data := tempTwo.data*(-1);
                                    tempTwo := tempTwo.next;

                                end loop;

                                addNums(operandOne,operandTwo,answer);

                                exit;
--Checks to see second list is larger. 
--This one indicates that the second number is longer, so we know that the sign will be inverse. 
--e.g. 4-6 = -2 and (-4)-(-6) = -2

                            elsif tempNode.data < tempTwo.data then
                   
                               tempNode := operandOne.head;
        
                               for i in integer range 1..operandOne.length loop

                                   tempNode.data := tempNode.data*(-1);
                                   tempNode := tempNode.next;

                               end loop;

--Second list is large so subtract the first from the second.

                               tempListGetRidOfWarningA := operandOne;
                               tempListGetRidOfWarningB := operandTwo;

                               addNums(tempListGetRidOfWarningB,tempListGetRidOfWarningA,answer);

                               flipSign(answer);

--This checks to see if we are at the end. If so this means the values are the same, thus zero. We flip them anyways and run it. 

                            elsif i = operandOne.length then

                                tempTwo := operandTwo.head;

                                for i in integer range 1..operandTwo.length loop

                                    tempTwo.data := tempTwo.data*(-1);
                                    tempTwo := tempTwo.next;

                                end loop;


                                addNums(operandOne,operandTwo,answer);

                                exit;
                    
                            else 

                                tempNode := tempNode.next;
                                tempTwo := tempTwo.next;
        
                            end if; 

                      end if;

                  end loop;

              end if;

           end if;

        else 

--This is for when the two signs differ. We flip the second and add.
--e.g. 4-(-5) = 4+5.

           tempHead := operandTwo;
           flipSign(tempHead);
           addNums(operandOne,tempHead,answer);

        end if;

--Gets rid of zero padding

        if answer.head /= NULL then
    
            while answer.head.data = 0 and answer.length > 1 loop

                removeFront(answer);

            end loop;

       end if;

    end subNums;

--Flips signs

    procedure flipSign(list: in out linkedListHead) is
    begin
        if isPositive(list) = false then

            list.isPositive := true;

        else

            list.isPositive := false;

        end if;

    end flipSign;

--Uses long form multiplication
    procedure multiNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;

    tempListOne : linkedListHead;
    tempListTwo : linkedListHead;

    loopLengthOne : integer;
    loopLengthTwo : integer;
    carry: integer;

    tempAnswer: integer;

    begin

       clearList(answer);

       tempNode := operandOne.tail;
       tempTwo := operandTwo.tail;

       loopLengthOne := operandOne.length;
       loopLengthTwo := operandTwo.length;

       carry := 0;
       tempAnswer := 0;

--The loop for one number, iterates over that.
      
       for i in integer range 1..loopLengthOne loop

           clearList(tempListOne);

           tempTwo := operandTwo.tail;

--Multiply node across entire number.
           carry := 0; 

           for x in integer range 1..loopLengthTwo loop         

               tempAnswer := tempTwo.data * tempNode.data + carry;

               tempTwo := tempTwo.prev;

               carry := 0;
--Carry incase the value is larger than a single digit. 

               if tempAnswer > 9 then
                  
                   carry := tempAnswer / 10;
                   tempAnswer := tempAnswer mod 10;

               end if;

               insertFront(tempAnswer,tempListOne);

           end loop;

--Carry incase we have any remaining stuff.

           if carry > 0 then
   
               tempAnswer := carry;

               while tempAnswer > 9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;


               end loop;

               insertFront(carry,tempListOne);

           end if;

--Need to ensure you are multiplying by tens or hundreds, so we pad the zeros. 
       for j in integer range 1..(i-1) loop

           insertBack(0,tempListOne);

       end loop;

--Adds the values to get the answer.

           addNums(tempListOne,tempListTwo,answer);

           copyList(tempListTwo,answer);

           tempNode := tempNode.prev;

       end loop;

--Fixes signs.
       if operandOne.isPositive = operandTwo.isPositive then

            makePos(answer);

       else
       
            makeNeg(answer);

       end if;

    end multiNums;

    procedure factorialNum(operandOne: in linkedListHead; answer: in out linkedListHead)is

--fact list stores the current factiorial

    tempAnswerList : linkedListHead;
    factList : linkedListHead;
    tempList : linkedListHead;
    tempNode : linkAccess;
    oneList : linkedListHead;

--Hard coded the small and simple cases, this flag is used to notify that. 
    
    baseFlag : boolean;

    counter : integer;

    begin

        clearList(answer);

        tempNode := operandOne.tail;
       
        if operandOne.length = 1 then


            if tempNode.data = 0 or tempNode.data = 1 then

               insertBack(1,answer);
               baseFlag := true;

            elsif tempNode.data = 2 then

               insertBack(2,answer);
               baseFlag := true;

            end if;
        end if;

        if isPositive(operandOne) = false then

           put_line("Error with input.");
           baseFlag := true;

        end if;

        if baseFlag = false then

--Base Case here, factList contains the decrements, tempAnswer contains the running total.
--Setup

            copyList(tempAnswerList,operandOne);
            copyList(factList,operandOne);
            insertBack(1,oneList);
--Decrement                        
            subNums(factList,oneList,tempList);
            copyList(factList,tempList);
            clearList(tempList);         
--Now factList is equal to operandOne -1.

            while factList.length > 1 loop

                 multiNums(tempAnswerList,factList,tempList);
                 clearList(tempAnswerList);
                 copyList(tempAnswerList,tempList);

                 clearList(oneList);
                 insertBack(1,oneList);

                 subNums(factList,oneList,tempList);
                
                 copyList(factList,tempList);
                 clearList(tempList);  
--The subtraction function leaves oneList values as negative, we clear the list and get a fresh one.

            end loop;

            counter := factList.head.data;

            while counter > 1 loop

                multiNums(tempAnswerList,factList,tempList);
                clearList(tempAnswerList);
                copyList(tempAnswerList,tempList);
--Decrement               
                clearList(tempList);          
                counter := counter -1;

                clearList(factList);
                insertBack(counter,factList); 

            end loop;

            copyList(answer,tempAnswerList);

        end if;
 
    end factorialNum;

end integer_linkedlist ;