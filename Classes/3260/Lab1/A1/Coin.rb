require_relative 'Randomizer'

class Coin < Randomizer

    def initialize()

        @enum_denomination = [:"0.05" ,:"0.1" ,:"0.25" ,:"1" ,:"2"]
        @enum_coin_side = [:H,:T]
        @denomination
    end

    def denomination()

        return(@denomination)

    end

    def flip()

        randomize()

    end

    def sideup()
    
        return(@up)

    end

end