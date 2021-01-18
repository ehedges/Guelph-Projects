*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
    
START:                  

    MOVEA.L #RowOne,A1
    MOVEA.L #RowTwo,A2
    MOVEA.L #RowThree,A3
    MOVEA.L #RowFour,A4
    MOVE.B #0,D0
    MOVE.B #0,D1
    
FOR    CMPI.B #2,D0
    BGT EXIT
    MOVE.B D0,D1
    ADD.B #1,D1
SECOND    CMPI.B #3,D1
    BGT FIRST    
    MOVE.B D0,D3
    MOVE.B D1,D4
    MULS #4,D3
    MULS #1,D4
    ADD.B D3,D4
    MOVE.B (A1,D4),D5
    MOVE.B D0,D6
    MULS #1,D6
    MOVE.B D1,D7
    MULS #4,D7
    ADD.B D6,D7
    MOVE.B (A1,D7),(A1,D4)
    MOVE.B D5,(A1,D7)
    ADD.B #1,D1
    BRA SECOND
FIRST ADD.B #1,D0
    BRA FOR 
EXIT    TRAP #14 
     
    ORG    $9000    
RowOne DC.B     1,2,3,4
RowTwo DC.B     5,6,7,8
RowThree DC.B   9,10,11,12
RowFour DC.B    13,14,15,16
    END    START
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
