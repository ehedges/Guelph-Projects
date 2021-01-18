*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
START:                  ; first instruction of program

* Put program code here

        MOVE.L #30,D0
        MOVE.L #25,D1
        MOVE.L #0,D3
        
LOOP    BTST #0,D1
        BNE ADDING
        
        
RETURN  CMPI.L #1,D1
        BEQ EXIT  
   
        ASL #1,D0
        ASR #1,D1
        
        BRA LOOP
        
ADDING
        ADD.L D0,D3
        BRA RETURN
        
EXIT        TRAP #14
    
    

* Put variables and constants here

    END    START        ; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
