import os
import sys 
from BinaryStrings import BinaryString


if __name__ == '__main__':

    ##create a BinaryString object that
    ##will generate all the substrings
    generator = BinaryString()

    ##generate all substrings of length two from the string "abc"
    generator.genAllSubStrings(2, "abc")
    ##clear the array of binary strings in generator
    generator.binaryStrings.clear()

    ##genearte all substrings of length two from the string "Mary"
    generator.genAllSubStrings(2, "Mary")
    generator.binaryStrings.clear()

    ##generate all substrings of lenth three from the string "Alien"
    generator.genAllSubStrings(3, "Alien")
    generator.binaryStrings.clear()