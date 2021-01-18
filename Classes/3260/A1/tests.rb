require_relative "Randomizer"
require_relative "Die"
require_relative "RandomizerFactory"
require_relative "RandomizerCollection"
require_relative "Coin"
require_relative "Clutch"
require_relative "Bag"
require_relative "Throw"
require_relative "Cup"
require_relative "Player"

if __FILE__ == $0

    puts "Test Suite 1: Die"
    puts "Test 1: Creating a die with 3 sides"
    test_Factory = RandomizerFactory.new
    three_Die = test_Factory.createDie(3,:green)
    if three_Die != nil

        puts "Test Passed, die created."

    end 
    puts "Test 2: Return details about the unrolled die(Sides then colour then rolled)"

    puts "Sides:"    
    puts three_Die.sides
    puts "Colour:"
    puts three_Die.colour
    puts "Sideup:"   
    puts three_Die.side_up

    puts "Test 3: Randomizing the Die, display all data to ensure integrity"

    puts "Sides:"
    puts three_Die.sides
    puts "Colour:"
    puts three_Die.colour
    puts "Randomizations:"
    puts three_Die.roll
    puts "Sideup:"
    puts three_Die.side_up

    puts "Test 4: Randomizing the same Die again(Sides then colour then rolled)"

    puts "Sides:"
    puts three_Die.sides
    puts "Colour:"
    puts three_Die.colour
    puts "Randomizations:"
    puts three_Die.roll
    puts "Sideup:"
    puts three_Die.side_up
    puts "Test 5: Reset Die"
    three_Die.reset
    puts three_Die.side_up
    puts "Rolling once:"
    puts three_Die.roll

    puts "Test Suite 2: Coin"

    puts "Test 1: Creating a coin"

    test_Coin = test_Factory.createCoin(:"1")

    puts "Test 2: Flip a coin"

    puts test_Coin.flip
    puts test_Coin.sideup
    puts test_Coin.denomination

    puts "Test Suite 3: Randomizer_Collection"

    puts "Test 1: Create Collection"

    test_Collection = RandomizerCollection.new

    puts "Test 2: Store a coin to an empty Collection"

    puts "Collection Length:"
    puts test_Collection.collection_length
    test_Collection.store(test_Coin)
    puts "Collection Length:"
    puts test_Collection.collection_length

    puts "Test 3: Store a die to an empty Collection"

    test_Collection_second = RandomizerCollection.new
    puts "Collection Length:"
    puts test_Collection_second.collection_length
    test_Collection_second.store(three_Die)
    puts "Collection Length:"
    puts test_Collection_second.collection_length

    puts "Test 4: Add multiple objects (4) to Collection (1)"

    puts "Collection Length:"
    puts test_Collection_second.collection_length
    test_Collection_second.add(three_Die,three_Die,test_Coin,test_Coin)
    puts "Collection Length:"
    puts test_Collection_second.collection_length

    puts "Test 5: Add collection (5) to Collection (1)"

    puts "Collection Length:"
    puts test_Collection.collection_length
    test_Collection.add(test_Collection_second)
    puts "Collection Length:"
    puts test_Collection.collection_length

    puts "Test 6: (5) Empty"

    puts "Collection Length:"
    puts test_Collection_second.collection_length
    test_Collection_second.empty
    puts "Collection Length:"
    puts test_Collection_second.collection_length

    puts "Test Suite 4: Clutch"

    puts "Test 1: Create Clutch"

    test_clutch = Clutch.new

    puts "Test 2: Next Clutch (Storing 2 copies of die from Test 1)"

    test_clutch.store(three_Die)
    test_clutch.store(three_Die)
    puts "Clutch Length:"
    puts test_clutch.collection_length
    
    next_die = test_clutch.next

    puts "Clutch Length:"
    puts test_clutch.collection_length

    puts "Die"
    puts "Sides:"
    puts three_Die.sides
    puts "Colour:"
    puts three_Die.colour
    puts "Randomizations:"
    puts three_Die.roll
    puts "Sideup:"
    puts three_Die.side_up

    puts "Test 3: Empty "
    puts test_clutch.collection_length
    puts test_clutch.empty
    puts test_clutch.collection_length
    puts "Test 4: Next on an empty Clutch"
    next_die = test_clutch.next

    puts "Test Suite 5: Bag"
    puts "Test 1: Create Bag"

    test_bag = Bag.new

    puts "Storing a quarter, dime, toonie, a red 6 sided die, two yellow 4 sided die."

    quarter = test_Factory.createCoin(:"0.25")
    quarter.flip
    dime = test_Factory.createCoin(:"0.10")
    dime.flip
    toonie = test_Factory.createCoin(:"2")
    toonie.flip
    red_die = test_Factory.createDie(6,:red)
    red_die.roll
    yellow_die_one = test_Factory.createDie(4,:yellow)
    yellow_die_one.roll 
    yellow_die_two = test_Factory.createDie(4,:yellow)
    yellow_die_two.roll 
    test_bag.add(quarter,dime,toonie,red_die,yellow_die_one,yellow_die_two)
 
    puts "Test 2: Select all die from Bag {item: :die}"

    test_clutch = test_bag.select("{item: :die}",:all)
    puts "Number of die"
    puts test_clutch.collection_length

    puts "Test 3: Select all coin Bag {item: :coin}"

    test_clutch = test_bag.select("{item: :coin}",:all)
    puts "Number of coin"     
    puts test_clutch.collection_length

    puts "Test 4: Select all coin with heads from Bag"

    test_clutch = test_bag.select("{item: :coin, up: :H}",:all)
    puts "Number of coin" 
    puts test_clutch.collection_length

    puts "Test 5: Select all quarter from Bag"

    test_clutch = test_bag.select("{item: :coin, denomination: :0.25}",:all)
    puts "Number of coin" 
    puts test_clutch.collection_length

    puts "Test 7: select 6 sided die Bag"

    test_clutch = test_bag.select("{item: :die, sides: 6}",:all)   
    puts "Number of die"
    puts test_clutch.collection_length

    puts "Test 8: select red die Bag"

    test_clutch = test_bag.select("{item: :die, colour: :red}",:all)
    puts "Number of die"
    puts test_clutch.collection_length

    puts "Test 9: select 4 sided yellow die with 4 up Bag"

    test_clutch = test_bag.select("{item: :die, colour: :yellow, sides: 4, up:4}",:all)
    puts "Number of die" 
    puts test_clutch.collection_length

    puts "Test 10: select via number"

    test_clutch = test_bag.select("{item: :die}",2)
    puts "Number of die"
    puts test_clutch.collection_length

    puts "Test 11: select more than there is in array (10)"

    test_clutch = test_bag.select("{item: :coin}",10)
    puts "Number of coin" 
    puts test_clutch.collection_length

    puts "Test 12: select negative"

    test_clutch = test_bag.select("{item: :coin}",-10)
    puts "Number of coin" 
    puts test_clutch.collection_length

    puts "Test 13: select zero"

    test_clutch = test_bag.select("{item: :coin}",0)
    puts "Number of coin" 
    puts test_clutch.collection_length

    puts "Test 14: Empty Bag"
    test_bag.empty

    puts "Test Suite 6: Throw"

    puts "Test 1: Create Throw"

    input_throw = []
    input_throw.push(quarter)
    input_throw.push(dime)
    input_throw.push(toonie)
    input_throw.push(red_die)
    input_throw.push(yellow_die_one)
    input_throw.push(yellow_die_two)
    test_throw = Throw.new(input_throw)

    puts "Test 2: Create Tally"

    puts test_throw.tally("{item: :coin}")

    puts "Test 3: Create sum"

    puts test_throw.sum("{item: :coin}")

    puts "Test 4: Report"

    puts test_throw.report()

    puts "Test 5: Tally with empty thorw"

    empty_throw = []

    test_throw = Throw.new(empty_throw)

    puts test_throw.tally("{item: :coin}")

    puts "Test 6: Sum with empty throw"

    puts test_throw.sum("{item: :coin}")

    puts "Test 7: Report with empty throw"

    puts test_throw.report()


    puts "Test Suite 7: Cup"

    puts "Test 1: Create Cup"
 
    test_cup = Cup.new()
    puts "Test 2: Load Cup that is empty"
    test_clutch = Clutch.new
    test_clutch.store(three_Die)
    test_clutch.store(yellow_die_two)
    test_clutch.store(quarter)
    test_clutch.store(dime)
    test_clutch.store(toonie)
    test_cup.load(test_clutch)

    puts "Test 3: Load Cup that is not empty"

    test_cup.load(test_clutch)

    puts "Test 4: Throw Cup, tally then sum"

    test_throw = test_cup.throw
    puts test_throw.tally("{item: :coin}")
    puts test_throw.sum("{item: :coin}")

    puts "Test 5: Empty Cup, value is clutch length"
    test_cup.load(test_clutch)
    test_cup.load(test_clutch)
    cup_clutch = test_cup.empty
     
    puts test_clutch.collection_length

    puts "Test 6: Empty Cup and Throw (Displays tally of coin and die)"
   
    test_throw = test_cup.throw

    puts test_throw.tally("{item: :coin}")
    puts test_throw.tally("{item: :die}")

    puts "Test 7: Empty Cup and empty"

    cup_clutch = test_cup.empty

    puts cup_clutch.collection_length

    puts test_throw.tally("{item: :coin}")
    puts test_throw.tally("{item: :die}")

    puts "Test Suite 8: Player"

    test_cup = Cup.new()

    puts "Test 1: Create Player"  
    test_player = Player.new("Bob")
    puts "Test 2: Name Player" 
    puts test_player.name 
    puts "Test 3: Store Player"
    test_player.store(three_Die)
    puts "Test 4: Add Player"  
    test_player.store(quarter)
    puts "Test 5: Load Player"
    test_player.load("{item: :coin, denomination: :0.25}")
    puts "Test 6: Throw Player" 
    test_throw = test_player.throw(test_throw) 
    puts "Test 7: clear Player"
    test_player.clear
    puts "Test 8: Sum Player"
    puts test_player.sum("{item: :coin, denomination: :0.25}") 
    puts "Test 9: Tally Player"
    puts test_player.tally("{item: :coin, denomination: :0.25}")   
    puts "Test 10: Report Player"
    puts test_player.report 

    test_player = Player.new("Bob")
    puts "Test 11: Load empty Player"
    test_player.load("{item: :coin, denomination: :0.25}")
    puts "Test 12: Throw  emptyPlayer" 
    test_throw = test_player.throw(test_throw) 
    puts "Test 13: clear empty Player"
    test_player.clear
    puts "Test 14: Sum empty Player"
    puts test_player.sum("{item: :coin, denomination: :0.25}") 
    puts "Test 15: Tally empty Player"
    puts test_player.tally("{item: :coin, denomination: :0.25}")   
    puts "Test 16: Report empty Player"
    puts test_player.report 



end