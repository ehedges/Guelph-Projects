require_relative 'Die'
require_relative 'Coin'
class RandomizerCollection

    def initialize()

        @rand_Hash = Hash.new
        @last_insert = nil

    end

    def store(rand_object)

        @last_insert = rand_object

        if rand_object = :die 
 rand_object.colour()
            hashValue = hashDie(rand_object)


        else
    
            hashValue = hashCoin(hashValue,rand_object)

        end

    end

    def hashDie(rand_object)

        string = "Die"
        tempString = rand_object.colour()
        string = string + tempstring       
        tempString = rand_object.sides()
        string = string + tempstring 

    end

    def hashCoin()

    end

    def add(rand_collection)


    end

    def add(*rand_object)


    end
    
    def empty()

        @rand_Hash = Hash.new
        @last_insert = nil

    end
end