with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with integer_stack; use integer_stack;
with Ada.Calendar; use Ada.Calendar;

procedure ackermann is

    quitChar : Character;

    numN, numM: integer;

    startTime, endTime : Time;
    milliS : Duration;

    procedure calcAckermann (intN: in integer; intM: in integer) is
    
    mStack: stack;

    n,m:integer;

    emptyBool : Boolean;

    begin

        n := intN;
        m := intM;
       --By pushing on to the stack at the beginning, we can skip the need for ackerman outside opf the loop
        push(intM,mStack);

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
        put_line("Ackermann calculation is:"& integer'Image(n));
    
    end calcAckermann;

begin


    loop
        put_line("Enter M");
        get(numM);
        put_line("Enter N");
        get(numN);
    
        startTime := Clock;
        calcAckermann(numN,numM);
        endTime := Clock;

        milliS := (endTime - startTime) * 1000;

        put_line("Runtime = " & Duration'Image(milliS) & " milliseconds.");

        put_line("Press q to quit, otherwise enter another character to continue.");

        get(quitChar);

        if(quitChar = 'q') then

            exit;

        end if;

    end loop;

end ackermann;
