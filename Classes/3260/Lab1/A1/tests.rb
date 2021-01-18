require_relative "Randomizer"
require_relative "Die"
require_relative "RandomizerFactory"
require_relative "RandomizerCollection"
if __FILE__ == $0

    puts "Test 1: Creating A die 5 sided"
    tempFactory = RandomizerFactory.new
    tempDie = tempFactory.createDie(5,:green)
    puts tempDie.sides()
    puts tempDie.colour()
    puts tempDie.side_up()
    puts "Test 2: Randomizing the Die"
    puts tempDie.sides()
    puts tempDie.colour()
    puts tempDie.roll() 
    puts tempDie.side_up()
    puts "Test 3: Randomizing the same Die again"
    puts tempDie.sides()
    puts tempDie.colour()
    puts tempDie.roll() 
    puts tempDie.side_up()
    puts "Test 4: Reset Die"
    tempDie.reset()
    puts tempDie.side_up()
    puts "test 5: Making a collection"
    tempCollection = RandomizerCollection.new
    puts "test 6: Store 1 object"
    tempCollection.store(tempDie)
end