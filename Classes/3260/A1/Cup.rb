require_relative 'RandomizerCollection'
require_relative "Throw"
require_relative "Clutch"

class Cup < RandomizerCollection

    def initialize()

         @collection_array = []   

    end

    def throw()

        for i in (0..@collection_array.size-1)

            if @collection_array[i].object_type == :coin

                @collection_array[i].flip

            elsif @collection_array[i].object_type == :die

                @collection_array[i].roll

            end      

        end

        thrown = Throw.new(@collection_array)

        self.empty

        return (thrown)       

    end

    def load(temp_clutch)

        temp_array = temp_clutch.clone_collection  

        for i in (0..temp_array.size-1)

           @collection_array.push(temp_array[i])

        end

    end

    def empty()

        temp_Clutch = Clutch.new

        if @collection_array.size > 0

            temp_Clutch.add(self)

        end

        @collection_array = []

        return temp_Clutch

    end

end