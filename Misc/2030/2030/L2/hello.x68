*hello.x68 displays the message “Hello world!” on the SunRay console

        ORG $8000
PROGRAM	LEA MESSAGE,A1
		TRAP #2
		TRAP #14

MESSAGE	DC.B 'Hello World!'
		DC.B $0D,$0A,0
		END PROGRAM