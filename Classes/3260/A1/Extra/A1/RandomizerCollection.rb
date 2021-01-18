require_relative 'Die'
require_relative 'Coin'

class RandomizerCollection

    def initialize()

        @enum_type = [:coin,:die,:collection]
        @collection_array = []
        @item = :collection

    end

    def store(rand_object)

        if rand_object == nil

            return

        end

        @collection_array.push(rand_object)

    end

    def add(*rand_object)

        for i in (0..rand_object.size-1)

            if rand_object[i].object_type == :collection

                temp_collection = rand_object[i].clone_collection                

                for j in (0.. temp_collection.size-1)

                    self.store(temp_collection[j])

                end

            else

                self.store(rand_object[i])

            end

        end


    end

    def empty()

        @collection_array = []
        @last_insert = nil

    end

    def object_type()

        return (@item)

    end 

    def clone_collection()

        temp_collection = @collection_array.clone

    end

    def collection_length()

        return  (@collection_array.size)

    end    

end