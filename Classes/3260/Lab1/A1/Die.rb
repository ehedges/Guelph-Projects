require_relative 'Randomizer'
class Die < Randomizer

    attr_reader :sides

    def initialize(sides_input,colour_input)
 
        @enum_colour = [:red,:green,:blue,:yellow,:black,:white]
        @colour = colour_input
        @item = :die 
        @side = sides_input
        @up = nil
        @randomizations = 0


    end
    
    def colour()

        return(@colour)

    end 

    def sides()

        return(@side)

    end 

    def roll()        

        randomize()

    end

    def side_up()

        result()

    end

end