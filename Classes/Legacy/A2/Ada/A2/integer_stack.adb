package body integer_stack is

    procedure push(x : in integer; st : in out stack) is
    begin
        if st.top < 1000000 then

           st.top := st.top + 1;
           st.item(st.top) := x;

        end if;

    end push;

    procedure pop (x : out integer; st : in out stack) is
    begin

        if st.top > 0 then

            x := st.item(st.top);
            st.top := st.top - 1;
         
        end if;

    end pop;

    function stack_is_empty (st :stack) return Boolean is
    begin

        return st.top = 0;

    end stack_is_empty;

    function stack_top (st :stack) return integer is
    begin

        if st.top = 0 then

            return -9999999;

        else

            return st.item(st.top);
    
        end if;

    end stack_top;

    procedure reset_stack(st : in out stack) is
    begin

        st.top := 0;

    end reset_stack;

end integer_stack;