require_relative "Clutch"

class Throw

    def initialize(object_array)

        @last_report = nil	
        @throw_array = object_array
        @tally_report = Hash.new
        @sum_report = Hash.new
        
    end

    def return()

        return_clutch = Clutch.new

        for i in (0..@throw_array.size-1)
        
            return_clutch.store(@throw_array[i])

        end
 
        return return_clutch

    end

    def tally (input_hash)

        temp_tally = 0

        temp_clutch = throw_hash(input_hash)

        temp_tally = temp_clutch.collection_length

        @last_report = temp_tally

    end

    def sum(input_hash)

        temp_sum = 0

        temp_clutch = throw_hash(input_hash)     

        for i in (0..temp_clutch.collection_length-1)

            temp_object = temp_clutch.next

            if temp_object != nil

                temp_up = temp_object.result

                if temp_up == :H

                    temp_sum = temp_sum + 1

                elsif temp_up == :T

                    temp_sum = temp_sum + 0

                elsif

                    temp_sum = temp_sum + temp_up

                end

            end

        end

        @last_report = temp_sum

    end

    def report()

        return (@last_report)

    end

    def throw_hash (description)

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

        temp_length = @throw_array.size     

        for i in (0..(temp_length-1))

            valid_entry = true

            if temp_item == @throw_array[i].object_type

                if temp_item == :coin

                    if temp_denomination != nil

                        if temp_denomination != @throw_array[i].denomination

                            valid_entry = false

                        end 

                    end

                    if temp_up != nil

                        if temp_up != @throw_array[i].sideup

                            valid_entry = false

                        end 

                    end 

                else 

                    if temp_sides != nil

                        if temp_sides != @throw_array[i].sides

                            valid_entry = false

                        end

                    end

                    if temp_colour != nil

                        if temp_colour != @throw_array[i].colour

                            valid_entry = false

                        end

                    end

                    if temp_up != nil

                        if temp_up != @throw_array[i].side_up

                            valid_entry = false

                        end

                    end

                end

                if valid_entry == true

                    temp_Clutch.store(@throw_array[i])

                end

            end           

        end

        return (temp_Clutch)

    end


end