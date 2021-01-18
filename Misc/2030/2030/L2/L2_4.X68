*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
PROGRAM MOVE.B #$77,D0
        ADD.B  #3,D0
        ADD.B  #9,D0
        SUB.B  #1,D0
        SUB.B  #4,D0
        TRAP   #14
        END    PROGRAM
