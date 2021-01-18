with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with char_stack; use char_stack;

procedure ackermann is

    numN, numM,answer : integer;
    tempChar : character;

    ackStack: stack;

    procedure ackStatement (st : in out stack; m: in out integer; n: in out integer; total: in out integer ) is

    topStack : integer;

    begin
            loop

                if(m = 0) then

                    total := n+1;

                    exit;

                elsif (n = 0) then

                   push(m,ackStack);
                   m := m - 1;
                   n := 1;

                else 

                   push(m,st);
                   n := n-1;

                end if;

        end loop;

    end ackStatement;

    procedure calcAckermann (total: in out integer; intN: in integer; intM: in integer) is

    top: integer;
    
    n,m :integer;

    begin

        total := 0;
        n := intN;
        m := intM; 
        ackStatement(ackStack,m,n,total);
        put_line("Succesful");

        loop

            top := stack_top(ackStack);
             
            if(top = -9999999) then

                exit;

            end if;

            pop(top,ackStack);

            ackStatement(ackStack,top,n,total);

        end loop;

    put(total);

    end calcAckermann;

begin

    put_line("Enter M");
    get(numM);
    put_line("Enter N");
    get(numN);

    answer := 0;

    calcAckermann(answer,numN,numM);

    --get(tempChar);

    --while (tempChar /= 'q') loop

        --push(tempChar,tempStack);
        --get(tempChar);

   -- end loop;

   -- loop
    
       -- tempchar := stack_top(tempStack);

        --exit when (tempChar = ' ');   

        --put(tempChar);
       -- pop(tempChar,tempStack); 

   -- end loop;

end ackermann;
