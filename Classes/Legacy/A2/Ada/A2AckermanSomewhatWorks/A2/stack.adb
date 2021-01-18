package char_stack is

        type values is array(1..100) of character;
        type stack is

        record
            item : values;
            top : natural := 0;
        end record;

        procedure push(x : character; st : in out stack);
        procedure pop(x : out character; st : in out stack);

    end char_stack;

    package body char_stack is
    procedure push(x : in character; st : in out stack) is
    begin
        if st.top < 100 then

           st.top := st.top + 1;
           st.item(st.top) := x;

        end if;

    end push;

    procedure pop (x : out character; st : in out stack) is
    begin

        if st.top > 0 then

            x := st.item(st.top);
            st.top := st.top - 1;
     put(st.top);
         end if;

    end pop;

end char_stack;