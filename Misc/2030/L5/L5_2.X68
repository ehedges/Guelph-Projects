*L5_2 sample program

CODE	EQU	$8000
DATA	EQU	$9000
	
        ORG	CODE
START	MOVE.W	$9000,D0
	    MULU	#7,D0
	    DIVU	#3,D0
	    ADD.W	$9004,D0
	    MOVE.W	D0,$9002
	    TRAP	#14
	    END CODE
	
ORG	DATA
	DC.W	$10
	DS.W	1
	DC.W 	10
	END DATA
START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
