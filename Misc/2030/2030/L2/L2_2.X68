*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
PROGRAM MOVE.L	#$56781234,D0
        MOVE.B	D0,D1
        MOVE.W	D0,D2
        MOVE.L	D0,D3
        MOVE	D0,D4
        TRAP	#14
        END PROGRAM
