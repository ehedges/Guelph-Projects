require_relative "Clutch"
require_relative "Cup"
require_relative "Bag"
class Player

    def initialize(name)

        @name = name
    	@player_bag = Bag.new
   	@player_cup = Cup.new
        @throw_array = []
        @last_report = nil

    end

    def name()

        return @name

    end

    def store(object)

        @player_bag.store(object)

    end

    def add(collection)

        @player_bag.add(collection)

    end

    def load(hash)

        temp_value = @player_bag.select(hash,:all)
        @player_cup.load(temp_value)
 
    end

    def throw(temp_throw)

        temp_throw = @player_cup.throw
        @throw_array.push(temp_throw)
        temp_clutch = @player_cup.empty
        
        return(temp_throw)

    end

    def clear()

        @throw_hash = Hash.new
        @last_throw = nil
        @last_report = nil
	
    end

    def tally(input_hash)

        value = []

        for i in (0..@throw_array.size-1)

            value[i] = @throw_array[i].tally(input_hash)

        end      

        @last_report = value

    end 

    def sum(input_hash)

        value = []
        for i in (0..@throw_array.size-1)
            value[i] = @throw_array[i].sum(input_hash)

        end   

        @last_report = value

    end

    def report()

        return (@last_report)

    end 

end