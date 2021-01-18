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

        create_coin = Coin.new(denomination)

    end

end
