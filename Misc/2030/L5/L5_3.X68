*L5_3.x68 example of program with assemble-time expression

        ORG 	$8000

START	MOVE.B  $9001,D0	;numeric memory address
	    MOVE.B VAR1+1,D0    ;assemble-time expression
        MOVE.B 	 VAR2,D0    ;label
        TRAP  #14     
	
        
	
        ORG	$9000	
VAR1	DC.B	$01	
VAR2	DC.B	$02	
VAR3	DC.B	$03	
VAR4	DC.B	$04	
	
        END	START	



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
