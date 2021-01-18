with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with char_stack; use char_stack;

procedure ackermann is

    numN, numM,answer : integer;
    tempChar : character;

    mStack: stack;
    nStack: stack;
    labelStack: stack;

    procedure calcAckermann (total: in out integer; intN: in integer; intM: in integer) is

    top: integer;
    
    n,m, label :integer;

    emptyBool : Boolean;

    begin

        total := 0;
        push(intM,mStack);
        push(intN,nStack);
        push(1,labelStack);

        loop

             emptyBool := stack_is_empty(labelStack);

             if(emptyBool = false) then
             
                 pop(label,labelStack);
                 pop(n,nStack);
                 pop(m,mStack);

                 if(label = 1) then
                 
                    loop

                         if (m = 0) then

                             total := n+1;
                             exit;

                         elsif (n = 0) then 
  
                             push(m,mStack);
                             push(n,nStack);
                             push(2,labelStack);
                             m := m-1;
                             n:=1;

                         else

                             push(m,mStack);
                             push(n,nStack);
                             push(3,labelStack);
                             n := n-1;

                         end if;

                     end loop;

                   elsif (label = 3) then 

                         push(m,mStack);
                         push(n,nStack);
                         push(4,labelStack);
                         m:= m-1;
                         n:= total;

                     loop

                         if (m = 0) then
                             total := n+1;
                             exit;

                         elsif (n = 0) then 

                             push(m,mStack);
                             push(n,nStack);
                             push(2,labelStack);
                             m := m-1;
                             n:=1;

                         else

                             push(m,mStack);
                             push(n,nStack);
                             push(3,labelStack);
                             n := n-1;

                     end if;

                     end loop;

                 end if;

             else

                 exit;

             end if;

        end loop;
        put_line("Ackermann calculation is:");
        put(total);
    end calcAckermann;

begin

    put_line("Enter M");
    get(numM);
    put_line("Enter N");
    get(numN);

    answer := 0;

    calcAckermann(answer,numN,numM);


end ackermann;
