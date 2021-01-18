with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
with Ada.Text_IO; use Ada.Text_IO;

package body integer_linkedlist  is

    numString :  unbounded_string;

    stringCount: integer; 
    carry: integer;
    tempAnswer: integer;

    function isPositive(list: in linkedListHead) return boolean is
    begin

        return list.isPositive;

    end isPositive;

    procedure makePos(list: in out linkedListHead) is
    begin

        list.isPositive := true;

    end makePos;

    procedure makeNeg(list: in out linkedListHead) is
    begin

        list.isPositive := false;

    end makeNeg;

    procedure insertBack(data: in integer; list: in out linkedListHead) is
    
    insertNode : linkAccess;
    tempNode : linkAccess;

    begin
        
        insertNode := new linkNode;


        if list.length = 0 then

            list.tail := insertNode;
            list.head := insertNode;

            insertNode.data := data;

        else

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

                    put(tempAnswer);

                end if;

                insertFront(tempAnswer,answer);

            end loop;       

            if carry > 0 then

                 while tempAnswer > 9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;
                    insertFront(tempAnswer,answer);

                 end loop;

                insertFront(carry,answer);

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
    loopLength : integer;

    begin

        if operandOne.isPositive = operandTwo.isPositive then

            answer.isPositive := operandOne.isPositive;

            if operandOne.length < operandTwo.length then

                flipSign(answer);

            end if;

            tempNode := operandOne.tail;
            tempTwo := operandTwo.tail;

            loopLength := operandOne.length;
   
            if operandOne.length < operandTwo.length then

                loopLength := operandTwo.length;        

            end if;

            carry := 0;

            for i in integer range 1..loopLength loop

                if tempTwo /= NULL and tempNode /= NULL then
            
                    tempAnswer := tempNode.data - (tempTwo.data + carry);
                    tempTwo := tempTwo.prev;
                    tempNode := tempNode.prev;

                    carry := 0;

                    while tempAnswer < 0 loop

                         tempAnswer := tempAnswer + 10;
                         carry := carry + 1;

                    end loop;

                elsif tempTwo /= NULL then
    
                    tempAnswer := tempTwo.data + carry;                
                    tempTwo := tempTwo.prev;

                    carry := 0;

                elsif tempNode /= NULL then

                    tempAnswer := tempNode.data - carry;
                    tempNode := tempNode.prev;

                    carry := 0;

                end if;         

                insertFront(tempAnswer,answer);

            end loop;

            if carry > 1 then
    
                makeNeg(answer);

                while tempAnswer > 9 loop

                    carry := tempAnswer / 10;
                    tempAnswer := tempAnswer mod 10;
    
                    insertFront(tempAnswer,answer);

                 end loop;

                 put(carry);

                 insertFront(tempAnswer,answer);
             
            end if; 

            if answer.head /= NULL then
    
                while answer.head.data = 0 and answer.length > 1 loop

                    removeFront(answer);

                end loop;

            end if;

        else 

            tempHead := operandTwo;
            flipSign(tempHead);
            addNums(operandOne,tempHead,answer);

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

    begin

       tempNode := operandOne.tail;
       tempTwo := operandTwo.tail;

       loopLengthOne := operandOne.length;
       loopLengthTwo := operandTwo.length;

       carry := 0;
       tempAnswer := 0;
        
       for i in integer range 1..loopLengthOne loop

               tempTwo := operandTwo.tail;
               clearList(tempListOne);

           for i in integer range 1..loopLengthTwo loop

               tempAnswer := (tempNode.data*tempTwo.data) + carry;
 
               if tempAnswer > 9 then

                   carry := tempAnswer / 10;
                   tempAnswer := tempAnswer mod 10;

               end if;

               insertFront(tempAnswer,tempListOne);

               tempTwo := tempTwo.prev;

           end loop;

           if carry > 0 then

               while carry > 9 loop

                   carry := tempAnswer / 10;
                   tempAnswer := tempAnswer mod 10;
                   insertFront(tempAnswer,tempListOne);

               end loop;

               insertFront(carry,tempListOne);

           end if;

           addNums(tempListOne,tempListTwo,answer);

           tempListTwo := answer;

           tempNode := tempNode.prev;

       end loop;

       if operandOne.isPositive = operandTwo.isPositive then

            makePos(answer);

       else
       
            makeNeg(answer);

       end if;
--comments
    end multiNums;
asdf
    procedure factorial(operandOne: in linkedListHead; operandTwo: in linkedListHead; answer: in out linkedListHead)is

    

    begin

    end

end integer_linkedlist ;