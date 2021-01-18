with Ada.Unchecked_Deallocation;

package integer_linkedlist is

    type linkNode;
    type linkAccess is access linkNode;
    type linkNode is record
    
        data : Integer;
        
        next : linkAccess := NULL;
        prev : linkAccess := NULL;

    end record;

    type linkedListHead is record

        length : Integer := 0;
        isPositive : Boolean := true;
        
        head : linkAccess := NULL;
        tail : linkAccess := NULL;

    end record;
   
    procedure free is new Ada.Unchecked_Deallocation(linkNode, linkAccess);
    procedure insertBack(data: in integer; list: in out linkedListHead);
    procedure insertFront(data: in integer; list: in out linkedListHead);
    procedure removeFront(list: in out linkedListHead);
    procedure displayList(list: in out linkedListHead);
    procedure clearList(list: in out linkedListHead);
    function isPositive(list: in linkedListHead)return Boolean;
    function getLength(list: in linkedListHead)return integer;
    procedure makePos(list: in out linkedListHead);
    procedure makeNeg(list: in out linkedListHead);
    procedure flipSign(list: in out linkedListHead);
    procedure addNums(operandOne: in linkedListHead;operandTwo: in linkedListHead;answer: in out linkedListHead);
    procedure subNums(operandOne: in linkedListHead;operandTwo: in linkedListHead;answer: in out linkedListHead);
    procedure multiNums(operandOne: in linkedListHead;operandTwo: in linkedListHead;answer: in out linkedListHead);
    procedure factorialNum(operandOne: in linkedListHead;answer: in out linkedListHead);
    procedure copyList(newCopy: in out linkedListHead; oldCopy: in linkedListHead);
end integer_linkedlist;