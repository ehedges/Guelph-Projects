import os
import sys


class BinaryString:
    # an array of binary strings
    # will be used to hold all the binary strings if length 'n'
    binaryStrings = []

    # a particular binary string of length 'n'
    binaryString = []

    # function to generate all binary strings  of lnegth 'n' and print the ones with
    # 'k' 1s in it.
    def genAllBinStrings(self, n: int, k: int, count: int):

        # if the count equals
        # 'n' then append binaryString to binaryStrings
        # and print binaryString if it has 'k' 1's in it
        if(count == n):
            
            self.binaryStrings.append(self.binaryString.copy())

            count = self.countOnes(self.binaryString)

            if count == k:

                print(self.binaryString.copy())

            return

        # else add '0' to the binaryString
        self.binaryString.append('0')

        # incremenet count by '1'
        count += 1

        # recursive call with 
        self.genAllBinStrings(n, k, count)

        self.binaryString.pop()

        self.binaryString.append('1')

        self.genAllBinStrings(n, k, count)

        self.binaryString.pop()

    # function to genearte all substrings of parameter sting
    # function will call genAllBinStrings with 'n' being the length of string.
    # The function should print only substrings of length 'k' where 'k' is a parameter
    #passed into the function
    def genAllSubStrings(self, k: int, string: str):

        # genearte all binaryStrings of length = len(string)
        self.genAllBinStrings(len(string), k, 0)
        
        # for each binary string in the list binaryStrings
        for i in range(0, len(self.binaryStrings)):

            ##Get the current binary string in binaryStrings
            binString = self.binaryStrings[i]

            ##the current substring to be generated from binString
            substring = ""

            count = self.countOnes(binString)

            if count == k:

            ##for the len of binString which equals the len of
            ##the parameter string, append to substring string[j]
                for j in range(0, len(binString)):

                    if binString[j] == '1':

                        substring += string[j]
          
                print(substring)


    ##count the number of ones in binString
    def countOnes(self, binString:list):
        
        count = 0
        ##for the length of binString
        for i in range(0, len(binString)):
            ##if binString[i] is a '1'
            ##then count++
            if binString[i] == '1':
                count += 1
        #return count
        return count
