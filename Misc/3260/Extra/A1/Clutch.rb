require_relative 'RandomizerCollection'

class Clutch < RandomizerCollection

    def initalize()


    end

    def next()

        if @collection_array.size == 0

            return nil

        end

            last_insert = @collection_array.pop

    end

    def empty()

        @collection_array = []
        @last_insert = nil

    end

end