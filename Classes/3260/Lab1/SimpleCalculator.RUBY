puts "Welcome to the Calculator enter a number:";
numberOne = gets.to_i;
puts "Enter a second number:";
numberTwo = gets.to_i;
puts "Choose an operation:";
operation = gets.chomp();

if operation == "+"

    puts (numberOne + numberTwo);

elsif operation == "-"

    puts (numberOne - numberTwo);

elsif operation == "*"

    puts (numberOne * numberTwo);

elsif operation == "/"

    puts (numberOne / numberTwo);

else 

    puts "Error";

end