with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with char_stack; use char_stack;

procedure ackermann is

    numN, numM: integer;

    mStack: stack;
    -- used https://stackoverflow.com/questions/10742322/how-to-rewrite-ackermann-function-in-non-recursive-style as guidance
    procedure calcAckermann (intN: in integer; intM: in integer) is
    
    n,m:integer;

    emptyBool : Boolean;

    begin

        n := intN;
        m := intM;

        push(intM,mStack);
       --https://stackoverflow.com/questions/10742322/how-to-rewrite-ackermann-function-in-non-recursive-style used as guidance
        loop

             emptyBool := stack_is_empty(mStack);
             if(emptyBool = false) then

                 pop(m,mStack);

                 if (m = 0 ) and (n >= 0) then

                     n := n+1;

                 elsif (m > 0) and (n = 0) then 

                     m := m-1;

                     push(m,mStack);

                     n:=1;

                elsif (m > 0) and (n > 0) then
                     
                     push(m-1,mStack);
                     push(m,mStack);
                     n := n-1;

                 end if;

             else

                 exit;

             end if;

        end loop;
        put_line("Ackermann calculation is:");
        put(n);
    end calcAckermann;

begin

    put_line("Enter M");
    get(numM);
    put_line("Enter N");
    get(numN);

    calcAckermann(numN,numM);


end ackermann;
