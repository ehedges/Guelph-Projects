package char_stack is

        type values is array(1..100) of character;
        type stack is

        record
            item : values;
            top : natural := 0;
        end record;

        procedure push(x : character; st : in out stack);
        procedure pop(x : out character; st : in out stack);
        function stack_is_empty return Boolean;
        function stack_top return character;
        procedure reset_stack(st : in out stack);

end char_stack;
