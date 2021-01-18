* L5_1.x68: Program given in class

	ORG	$8000	;program starts at $8000
START	MOVE.B	VALUE1,D0	;load first byte from $9000
	    MOVE.B	VALUE2,D1	;load second byte from $9001
	    ADD.B	D0,D1	;sum bytes
	    MOVE.B	D1,RESULT	;store sum at $9002
	    TRAP	#14	;return to MON68K

	ORG	$9000	;data starts at	$9000	
VALUE1	DC.B	11	;initialize RAM	with	11
VALUE2	DC.B	22	;initialize RAM	with	22
RESULT	DS.B	1	;reserve one byte of	RAM
	    END	START		

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
