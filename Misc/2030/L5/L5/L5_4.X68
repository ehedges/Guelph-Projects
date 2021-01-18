*-----------------------------------------------------------
* Title      :Lab 5 program
* Written by :Evan Hedges
* Date       :October 20th
* Description:Lab assignment
*-----------------------------------------------------------
    ORG $8000    
START

    MOVE.B X,D0
    MOVE.B Y,D1
    MULU #3,D1
    MULU #2,D0
    ADD.B D1,D0
    MOVE.B D0,Z            

    TRAP #14
    
    ORG    $9000
X   DC.B 1
Y   DC.B 1
Z   DS.B 1
    END    START       



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
