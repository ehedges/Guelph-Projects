class Randomizer

    @enum_type = [:coin,:die,:collection]
    @sides
    @item
    @up

    def initialize()

    end 

    def randomize()

        if @sides == nil

            return nil

        end

        @up = rand(1..@sides)

        @randomizations = @randomizations+1

    end

    def result()

        return(@up)

    end

    def reset()

        @randomizations = 0

        @up = nil

    end

    def object_type()

        return (@item)

    end 

end
