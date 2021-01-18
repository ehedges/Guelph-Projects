class randomizer

    def initialize()

        @sides
        @item
        @up

    end 

    def randomize()

        self.up = rand(1..self.sides)

    end

    def result()

        return(self.up)

    end

    def reset()

        self.up = NIL

    end

end
