*-----------------------------------------------------------
* Title      :Lab 5 program
* Written by :Evan Hedges
* Date       :October 20th
* Description:Lab assignment
*-----------------------------------------------------------
    ORG    $1000
     
START: ORG $8000

    MOVE.B X,D0
    MOVE.B Y,D1
    MULU #3,D1
    MULU #2,D0
    ADD.B D1,D0
    MOVE.b D0,Z
* Put program code here

    SIMHALT             ; halt simulator

* Put variables and constants here
    TRAP #14
    
    ORG    $9000
X   DC.B 1
Y   DC.B 1
Z   DS.B 1
    END    START        ; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
