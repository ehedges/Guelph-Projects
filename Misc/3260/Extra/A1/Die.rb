require_relative 'Randomizer'
class Die < Randomizer

    attr_reader :sides

    def initialize(sides_input,colour_input)
 
        @enum_colour = [:red,:green,:blue,:yellow,:black,:white]

        if sides_input < 3

           return nil

        end

        colour_flag = false

        for i in (0..@enum_colour.size-1)

            if colour_input == @enum_colour[i]

                colour_flag = true

            end

        end

        if colour_flag == false 

            return nil

        end

        @colour = colour_input
        @item = :die 
        @sides = sides_input
        @up = nil
        @randomizations = 0

    end
    
    def colour()

        return(@colour)

    end 

    def sides()

        return(@sides)

    end 

    def roll()        

        randomize()

    end

    def side_up()

        result()

    end

end