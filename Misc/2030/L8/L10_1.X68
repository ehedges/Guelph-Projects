*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
START:

    LEA $9000,SP
    CLR.L   D2
    MOVE.L  #1234,D2
    MOVE.L  D2,-(SP) 
    JSR     REC
    BRA EXIT

REC
    LINK A6,#-4
    CLR.L   D1
    MOVE.W 10(A6),D1
    CMPI #0,D1
    BEQ RETURN

    DIVU.W #10,D1
    MOVE.W D1,-2(A6)
    SWAP D1
    MOVE.W D1,-4(A6) 
    JSR REC
    
RETURN 
    MOVE.W 8(A6),D1
    MOVE.W #3,D0
    CMPI #0,D1
    BEQ  EXIT
    TRAP #15
    UNLK A6    
    RTS
    
EXIT   
        UNLK A6 
        TRAP    #14
        END     START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
