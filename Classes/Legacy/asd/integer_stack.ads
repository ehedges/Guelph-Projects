package integer_stack is

        type values is array(1..1000000) of integer;
        type stack is

        record
            item : values;
            top : natural := 0;
        end record;

        procedure push(x : integer; st : in out stack);
        procedure pop(x : out integer; st : in out stack);
        function stack_is_empty (st :stack) return Boolean;
        function stack_top (st :stack) return integer;
        procedure reset_stack(st : in out stack);

end integer_stack;
