require_relative 'Randomizer'

class Coin < Randomizer

    def initialize(denomination)

        @enum_denomination = [:"0.05" ,:"0.1" ,:"0.25" ,:"1" ,:"2"]
        @enum_coin_side = [:H,:T]
        @sides = 2
        @item = :coin
        @up = nil
        @randomizations = 0
        @denomination = denomination

        
    end

    def denomination()

        return(@denomination)

    end

    def flip()

        randomize()
        convert_enum()
        return (@randomizations)

    end

    def sideup()
    
        result()

    end

    def convert_enum()

        if @up == 1

            @up = :H

        elsif @up == 2

            @up = :T

        end 

    end

end