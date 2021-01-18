!     game of hangman by dave ahl, digital
!      based on a basic program written by ken aupperle
!            half hallow hills h.s. dix hills ny
!      converted to fortran 77 by m.wirth, april 2012
!       
       program hangman 
       character :: person(12,12)
       character :: d(20), usedLetters(26), a*20, guess, b*20, ans 
       integer :: dictLength(50)
       integer :: wordIndex, lose, words, tries, right, length 

!      Loop booleans
       integer :: i, j

       real :: rnd 

       character(len = 20), dimension(50) :: dict = [character(len = 20) :: & 
                'gum','sin','for','cry','lug','bye','fly','ugly', &
                'each','from','work','talk','with','self', &
                'pizza','thing','feign','fiend','elbow','fault', &
                'dirty','budget','spirit','quaint','maiden', &
                'escort','pickax','example','tension','quinine', &
                'kidney','replica','sleeper','triangle', &
                'kangaroo','mahogany','sergeant','sequence', &
                'moustache','dangerous','scientist','different', &
                'quiescent','magistrate','erroneously', &
                'loudspeaker','phytotoxic','matrimonial', &
                'parasympathomimetic','thigmotropism']
       write (*,*) "The Game of Hangman"
10     do while (i <= 12)
           j = 1;
           do while (j <= 12)
               person(i,j) = " "
               j = j+1
           end do
          i = i+1
       end do

       i = 1
       do while (i <= 20)
           d(i) = "-"
           i = i+1
       end do

       i = 1
       do while (i  <= 26)
           usedLetters(i) = " "
           i = i+1
       end do
        
       i = 1
       do while (i <= 50)
           dictLength(i) = 0
           i = i+1
       end do

       i = 1
       do while (i <= 12)
           person(i,1) = "X"
           i = i+1
       end do

       j = 1
       do while (j <= 7)
           person(1,j) = "X"
           j = j+1
       end do

       person(2,7) = "X"
       c=1
       words=50
       lose=0 
       if (c < words) go to 100
       write (*,*) "You did all the words"; go to 999
100    rnd=rand()
       wordIndex=ceiling(rnd*50)
       if (dictLength(wordIndex) == 1) then
           go to 100
       else
           dictLength(wordIndex) = 1; c=c+1; tries=0
       end if
       a = dict(wordIndex)
       length  = len_trim(a) 
       write (*,*) d(1:length )
170    write (*,*) "Here are the letters you used: "
       
       i = 1
       do while (i <= 26)
           if (usedLetters(i) == ' ') go to 200
           write (*,'(AA$)') usedLetters(i),","
           i = i+1
       end do

200    write (*,*) " "
       write (*,*) "What is your guess? "; right=0
       read (*,*) guess 
       i = 1
       do while (i <= 26)
           if (usedLetters(i) == " ") go to 250 
           if (usedLetters(i) == guess) then
               write (*,*) "You guessed that letter before"; 
               go to 170
           end if
           i = i+1
       end do
       write (*,*) "Invalid character"; go to 170
250    usedLetters(i)=guess; tries=tries+1

       i = 1
       do while (i <= length )
           if (a(i:i) == guess) then
               d(i) = guess; right=right+1
           end if
           i = i+1
       end do
       if (right == 0) then
           go to 290
       else 
           go to 300
       end if
290    lose=lose+1; go to 400       
300    i = 1
       do while (i <= length )
           if (d(i) == "-") go to 320
           i = i+1
       end do
       go to 390
320    write (*,*) d(1:length )
       write (*,*) "what is your guess for the word? "
       read (*,*) b
       if (a == b) go to 360
       write (*,*) "Wrong. Try another letter"; go to 170
360    write (*,*) "Right! It took you ",tries," guesses"
370    write (*,*) "Do you want another word? (y/n) "
       read (*,*) ans
       if (ans == "y") go to 10
       write (*,*) "It's been fun! bye for now."; go to 999
390    write (*,*) "You found the word."; go to 370
400    write (*,*) "Sorry, that letter isn't in the word."
       go to (415,420,425,430,435,440,445,450,455,460), lose
415    write (*,*) "First we draw a head."; go to 470
420    write (*,*) "Now we draw a body."; go to 470
425    write (*,*) "Next we draw an arm."; go to 470
430    write (*,*) "This time it's the other arm."; go to 470
435    write (*,*) "Now, let's draw the right leg."; go to 470
440    write (*,*) "This time we draw the left leg."; go to 470
445    write (*,*) "Now we put up a hand."; go to 470
450    write (*,*) "Next the other hand."; go to 470
455    write (*,*) "Now we draw one foot."; go to 470
460    write (*,*) "Here's the other foot -- you're hung!!." 
470    go to (480,490,500,510,520,530,540,550,560,570), lose

!      Draw Head
480    person(3,6) = "-"; person(3,7) = "-"; person(3,8) = "-"; person(4,5) = "("; 
       person(4,6) = "."; 
       person(4,8) = "."; person(4,9) = ")"; person(5,6) = "-"; person(5,7) = "-"; 
       person(5,8) = "-"; go to 580

!      Draw body 

490   i = 6
      do while (i<= 9)
           person(i,7) = "X"
           i = i+1 
      end do

       go to 580

!      Draw left arm
500       i = 4
       do while (i <= 7)
           person(i,i-1) = "\"
           i = i+1
       end do

       go to 580

!      Draw Right arm
510    person(4,11) = "/"; person(5,10) = "/"; person(6,9) = "/"; person(7,8) = "/"; 
       go to 580

!      Draw Right leg
520    person(10,6) = "/"; person(11,5) = "/"; go to 580 

!      Draw Left leg
530    person(10,8) = "\"; person(11,9) = "\"; go to 580 
540    person(3,11) = "\"; go to 580 
550    person(3,3) = "/"; go to 580 

!      Draw Right foot
560    person(12,10) = "\"; person(12,11) = "-"; go to 580 

!      Draw Left foot       
570    person(12,3) = "-"; person(12,4) = "/" 

580    i = 1
       do while (i <= 12)
           write (*,*) (person(i,j),j=1,12)
           i = i+1
       end do   
       if (lose == 10) then
           go to 600
       else
           go to 170
       end if
600    write (*,*) "Sorry, you loose. The word was ", a
       write (*,*) "You missed that one."; go to 370 

999    write (*,*) "Ending..." 
       end
