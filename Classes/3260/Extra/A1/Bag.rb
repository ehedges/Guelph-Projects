require_relative "RandomizerCollection"
require_relative "Die"
require_relative "Coin"

class Bag < RandomizerCollection

    def initalize()


    end

    def select(description,amount)

        temp_Clutch = Clutch.new

        temp_description = description

        temp_description.downcase       

        if temp_description.include?("item") == false

            return nil

        end

        temp_description.sub!("{","")
        temp_description.sub!("}","")

        description_array = temp_description.split(',') 

        temp_item = nil
        temp_sides = nil
        temp_colour = nil
        temp_up = nil
        temp_denomination = nil

        for i in (0..description_array.size-1)
           
            description_tuple = description_array[i].split(':')
            field_name = description_tuple[0].strip
            field_value = description_tuple[description_tuple.size-1].strip 

            description_tuple[description_tuple.size-1].strip
 
            if field_name == "item"

                value_symbol = field_value.to_sym

                if value_symbol == :die

                   temp_item = :die

                elsif value_symbol == :coin

                   temp_item = :coin

                else

                    return (nil)

                end
                
            elsif field_name == "sides"

               temp_sides = field_value.to_i

            elsif field_name == "colour"

                temp_colour = field_value.to_sym

            elsif field_name == "up"
               
                if temp_item == :die

                    temp_up = field_value.to_i

                else

                    temp_up = field_value.to_sym

                end                             
             
            elsif field_name == "denomination"
             
               temp_denomination = field_value.to_sym

            else
            
                return (nil)
 
            end

        end

        temp_length = self.collection_length        

        found_amount = 0

        for i in (0..(temp_length-1))

            valid_entry = true

            if temp_item == @collection_array[i].object_type

                if temp_item == :coin

                    if temp_denomination != nil

                        if temp_denomination != @collection_array[i].denomination

                            valid_entry = false

                        end 

                    end

                    if temp_up != nil

                        if temp_up != @collection_array[i].sideup

                            valid_entry = false

                        end 

                    end 

                else 

                    if temp_sides != nil

                        if temp_sides != @collection_array[i].sides

                            valid_entry = false

                        end

                    end

                    if temp_colour != nil

                        if temp_colour != @collection_array[i].colour

                            valid_entry = false

                        end

                    end

                    if temp_up != nil

                        if temp_up != @collection_array[i].side_up

                            valid_entry = false

                        end

                    end

                end

                if valid_entry == true

                    if amount != :all

                        if found_amount < amount

                            found_amount = found_amount+1

                            temp_Clutch.store(@collection_array[i])

                        end

                    else 

                        temp_Clutch.store(@collection_array[i])

                    end
                end

            end           

        end

        return (temp_Clutch)

    end

    def empty()

        temp_Clutch = Clutch.new

        temp_Clutch.add(self)

        @collection_array = []

        return temp_Clutch

    end

end