with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Text_IO; use Ada.Text_IO;

package body integer_linkedlist  is

    stringCount: integer; 
    carry: integer;
    tempAnswer: integer;
    
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

    procedure insertFront(data: in integer; list: in out linkedListHead) is

    insertNode : linkAccess;
    tempNode : linkAccess;

    begin
        
        insertNode := new linkNode;

        if list.length = 0 then

            list.tail := insertNode;
            list.head := insertNode;

            insertNode.data := data;

        else

            tempNode := list.head;
            tempNode.prev := insertNode;

            insertNode.next := tempNode;
            insertNode.prev := NULL;
            insertNode.data := data;

            list.head := insertNode;

        end if;

        list.length := list.length+1;

    end insertFront;

    procedure removeFront(list: in out linkedListHead) is

    tempNode : linkAccess;

    begin

        tempNode := list.head;
        tempNode := tempNode.next;
        tempNode.prev := NULL;
        list.head:= tempNode;
        list.length := list.length-1;

    end removeFront;

    procedure displayList(list: in out linkedListHead) is

    numString :  unbounded_string;
    tempNode : linkAccess;

    begin
    
        tempNode := list.tail;
        stringCount := 0;

        delete(numString,1,length(numString));

        while tempNode /= NULL loop
            
            insert(numString,1,Integer'Image(tempNode.data));

            tempNode := tempNode.prev;
            stringCount := stringCount+1;

        end loop;
        
        if(isPositive(list) = false) then

            insert(numString,1,"-");

        end if;
 
        put(numString);

    end displayList;

    function getLength(list: in linkedListHead) return integer is
    begin

        return list.length;

    end getLength;

    procedure clearList(list: in out linkedListHead) is
    begin

        list.length := 0;
     
        list.isPositive := true;

        list.head := NULL;
        list.tail := NULL;

    end clearList;

    procedure addNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;
    tempHead : linkedListHead;
    loopLength : integer;

    begin

        clearList(answer);

        if operandOne.isPositive = operandTwo.isPositive then

            answer.isPositive := operandOne.isPositive;
            tempNode := operandOne.tail;
            tempTwo := operandTwo.tail;

            loopLength := operandOne.length;

            if operandOne.length < operandTwo.length then

                loopLength := operandTwo.length;

            end if;

            carry := 0;
            tempAnswer := 0;
        
            for i in integer range 1..loopLength loop

                if tempTwo /= NULL and tempNode /= NULL then
 
                    tempAnswer := tempTwo.data + tempNode.data + carry;
                    tempTwo := tempTwo.prev;               
                    tempNode := tempNode.prev;

                elsif tempNode /= NULL then

                     tempAnswer := tempNode.data + carry;
                     tempNode := tempNode.prev;

                elsif tempTwo /= NULL then

                     tempAnswer := tempTwo.data + carry;
                     tempTwo := tempTwo.prev; 

                end if;
          
                carry := 0;

                if tempAnswer > 9 then

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;

                end if;

                if tempAnswer < 0 then

                    carry := -1;
                    tempAnswer := tempAnswer mod 10;

                end if;

                insertFront(tempAnswer,answer);

            end loop;       

            if carry > 0 then

                 while tempAnswer > 9 or tempAnswer < -9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;
                    insertFront(tempAnswer,answer);

                 end loop;

                insertFront(carry,answer);

            end if;

            if carry < 0 then

                tempNode := answer.head;
                tempNode.data := tempNode.data-1;

            end if;

        else 

            tempHead := operandTwo;
            flipSign(tempHead);
            subNums(operandOne,tempHead,answer);
        end if;

    end;

    procedure subNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;
    tempHead : linkedListHead;

    begin

        clearList(answer);

        if operandOne.isPositive = operandTwo.isPositive then

            answer.isPositive := operandOne.isPositive;

            tempNode := operandOne.head;
            tempTwo := operandTwo.head;

            if operandOne.length > operandTwo.length then

                for i in integer range 1..operandTwo.length loop

                    tempTwo.data := tempTwo.data*(-1);
                    tempTwo := tempTwo.next;

                end loop;

                addNums(operandOne,operandTwo,answer);

            else if operandOne.length < operandTwo.length then
                
                for i in integer range 1..operandOne.length loop

                    tempNode.data := tempNode.data*(-1);
                    tempNode := tempNode.next;

                end loop;

                addNums(operandTwo,operandOne,answer);

                flipSign(answer);

            else

                for i in integer range 1..operandOne.length loop

                        if tempNode /= NULL and tempTwo /= NULL then

                             if tempNode.data > tempTwo.data then

                                tempTwo := operandTwo.head;

                                for i in integer range 1..operandTwo.length loop

                                    tempTwo.data := tempTwo.data*(-1);
                                    tempTwo := tempTwo.next;

                                end loop;

                                addNums(operandOne,operandTwo,answer);

                                exit;

                            elsif tempNode.data < tempTwo.data then
                   
                               tempNode := operandOne.head;
        
                               for i in integer range 1..operandOne.length loop

                                   tempNode.data := tempNode.data*(-1);
                                   tempNode := tempNode.next;

                               end loop;

                               addNums(operandTwo,operandOne,answer);

                               flipSign(answer);

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

           tempHead := operandTwo;
           flipSign(tempHead);
           addNums(operandOne,tempHead,answer);

        end if;

        if answer.head /= NULL then
    
            while answer.head.data = 0 and answer.length > 1 loop

                removeFront(answer);

            end loop;

       end if;

    end subNums;

    procedure flipSign(list: in out linkedListHead) is
    begin
        if isPositive(list) = false then

            list.isPositive := true;

        else

            list.isPositive := false;

        end if;

    end flipSign;


    procedure multiNums(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    tempNode : linkAccess;
    tempTwo : linkAccess;

    tempListOne : linkedListHead;
    tempListTwo : linkedListHead;

    loopLengthOne : integer;
    loopLengthTwo : integer;
    placeCounter : integer;

    begin

       clearList(answer);

       tempNode := operandOne.tail;
       tempTwo := operandTwo.tail;

       loopLengthOne := operandOne.length;
       loopLengthTwo := operandTwo.length;

       carry := 0;
       tempAnswer := 0;
        
       for i in integer range 1..loopLengthOne loop

           clearList(tempListOne);

           tempTwo := operandTwo.tail;

           for x in integer range 1..loopLengthTwo loop         

               tempAnswer := tempTwo.data * tempNode.data + carry;

               tempTwo := tempTwo.prev;

               carry := 0;

               if tempAnswer > 9 then
                  
                   carry := tempAnswer / 10;
                   tempAnswer := tempAnswer mod 10;

               end if;

               insertFront(tempAnswer,tempListOne);

           end loop;

           if carry > 0 then
   
               tempAnswer := carry;

               while tempAnswer > 9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;


               end loop;

               insertFront(carry,tempListOne);

           end if;

       for j in integer range 1..(i-1) loop

           insertBack(0,tempListOne);

       end loop;
put("TEMPNODE DATA");
put(tempNode.data);
put_line("TEmplistOne:");
           displayList(tempListOne);
put(" ");
           addNums(tempListOne,tempListTwo,answer);
displayList(tempListTwo);
put_line("Answer");
displayList(answer);
           copyList(tempListTwo,answer);

           tempNode := tempNode.prev;
put_line(" ");
       end loop;

       if operandOne.isPositive = operandTwo.isPositive then

            makePos(answer);

       else
       
            makeNeg(answer);

       end if;

    end multiNums;

    procedure factorialNum(operandOne: in linkedListHead; answer: in out linkedListHead)is

    tempAnswerList : linkedListHead;
    factList : linkedListHead;
    tempList : linkedListHead;
    tempNode : linkAccess;
    oneList : linkedListHead;
    baseFlag : boolean;

    begin

        tempNode := operandOne.tail;

        baseFlag := false;
       
        if operandOne.length = 1 then

            baseFlag := true;

            if tempNode.data < 0 then

               put_line("Error with input");

            elsif tempNode.data = 0 or tempNode.data = 1 then

               insertBack(1,answer);

            elsif tempNode.data = 2 then

               insertBack(2,answer);
            end if;
        end if;

        if baseFlag = false then

        insertBack(1,oneList);

        copyList(tempAnswerList,operandOne);
        copyList(factList,operandOne);

        subNums(factList,oneList,tempList);
        copyList(factList,tempList);
        clearList(tempList);
        multiNums(tempAnswerList,factList,tempList);
        
        copyList(tempAnswerList,tempList);                

        copyList(answer,tempAnswerList);

        end if;

    end factorialNum;

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

end integer_linkedlist ;