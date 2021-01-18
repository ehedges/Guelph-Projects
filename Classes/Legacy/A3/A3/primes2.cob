identification division.

program-id. primesTwo.

environment division.

input-output section.

file-control.

select inputFile assign to "primes.dat"
    organization is line sequential.

select outputFile assign to "primes2Sol.dat"
    organization is line sequential.

data division.

file section.

fd outputFile.

01 outWriteLine.
    05 primeLine pic X(100).

working-storage section.

77  eofSwitch    pic 9 value 1.
77  numPrimeCalc  pic S9(9).
77  multipleOne  pic S9(9) usage is computational.
77  multipleTwo  pic S9(9) usage is computational.

01  inCard.
    02 numInput pic 9(9).
    02 filler pic X(71).

01  titleLine.
    02 filler pic X(6) value SPACES.
    02 filler pic X(20) value 'PRIME NUMBER RESULTS'.

01  underScores.
    02 filler pic X(32) value
       ' -------------------------------'.

01  notPrimeMsg.
    02 filler pic X value SPACE.
    02 notPrimeNum pic Z(8)9.
    02 filler pic X(15) value ' IS NOT A PRIME'.

01  isPrimeMsg.
    02 filler pic X value SPACE.
    02 isPrimeNum pic Z(8)9.
    02 filler pic X(11) value ' IS A PRIME'.

01  errorMsg.
    02 filler pic X value SPACE.
    02 errorNum pic Z(8)9.
    02 filler pic X(14) value ' ILLEGAL INPUT'.

procedure division.

*> Start by opening the files

    open input inputFile, output outputFile.

    write outWriteLine from titleLine after advancing 0 lines.
    write outWriteLine from underScores after advancing 1 line.

*> Initialize the boolean switch

    move 0 to eofSwitch.

*> Get input for first run.

    read inputFile into inCard at end move 1 to eofSwitch.
    move numInput to numPrimeCalc.

*>  Loop here

    perform primeCalc until eofSwitch = 1.

    finish.
    close inputFile, outputFile.

stop run.

primeCalc.


    display numPrimeCalc.

*> Primes cannot be negative. 1 Is not a a prime number. Chheck fior that here

    if numPrimeCalc > 1 then

*>2 and 3 are prime numbers, check for that.
        if numPrimeCalc < 4 then

            move numInput to isPrimeNum
            write outWriteLine from isPrimeMsg after advancing 1 line

        else
 
*> Number is greater than 4 calculate. We try and find a multiple here.

            move 2 to multipleOne

*> if the mutiple is equal, it must be prime.

            perform until multipleTwo = numPrimeCalc

*> Prime calculations here

                divide multipleOne into numPrimeCalc giving multipleTwo
                multiply multipleOne BY multipleTwo
            
                add 1 to multipleOne

                if multipleOne > numPrimeCalc then 

                    move numInput to isPrimeNum        
                    write outWriteLine from isPrimeMsg after advancing 1 line

                end-if

            end-perform

            if multipleOne not > numPrimeCalc

                move numInput to notPrimeNum
                write outWriteLine from notPrimeMsg after advancing 1 line

            end-if

        end-if

    else 

*> Indicates some other error.

        move numInput to errorNum
        write outWriteLine from errorMsg after advancing 1 line

    end-if.

*>get more data if there is some, if it is at the end flip the switch

    read inputFile into inCard at end move 1 to eofSwitch.
    move numInput to numPrimeCalc.

stop run.