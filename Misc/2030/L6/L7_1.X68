*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
    
START:                  

    MOVEA.L #StringOne,A1
    MOVEA.L #StringTwo,A2
    MOVE.B #$FF,D3
DO  MOVE.B (A1)+,D1
    MOVE.B (A2)+,D2
    CMP.B D1,D2
    BEQ While
    MOVE.B $00,D3
While
    CMPI.B #$0D,D1
    BEQ EXIT
    CMPI.B #$FF,D3
    BEQ DO
EXIT    TRAP #14 
     
    ORG    $9000    
StringOne DC.B  'A','B','C','D',$0D
    ORG    $9020
StringTwo DC.B 'A','B','C','d',$0D
    END    START
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
