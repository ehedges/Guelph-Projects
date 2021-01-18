*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $8000
PROGRAM MOVE.W	#9,D2
        MOVE.B	#-2,D3
        MULS	D2,D2
        EXT.W	D3
        DIVS	D3,D2
        CLR.L	D1
        MOVE.W	D2,D1
        MOVE.L	D2,D0
        CLR.W	D0
        SWAP	D0
        TRAP	#14
        END PROGRAM

