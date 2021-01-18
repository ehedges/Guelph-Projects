require_relative 'Randomizer'
require_relative 'Die'

class RandomizerFactory

    def createDie(sides,colour)

        if sides == nil

            return NULL

        elsif sides < 1

            return NULL

        end

        create_die = Die.new(sides,colour)

    end

    def createCoin(denomination)

        self.sides = 2
        self.item = coin
        self.up = NIL

        self.denomination = denomination

    end

end
