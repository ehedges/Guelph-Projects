package stack is 

    procedure push(x : in character);
    procedure pop( x : out character);
    function stack_is_empty return Boolean;
    function stack_top return character;
    procedure reset_stack;

end stack;