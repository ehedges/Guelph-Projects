PROGRAM LOGS

IMPLICIT NONE

CHARACTER :: quit

REAL :: diaSmall, diaLarge, length, boardFeet, volume

INTEGER :: KERF

boardFeet = 0
volume = 0

!Loops through until the user quits, main menu

DO

    WRITE (*,*) "Welcome to volume boardfeet/calculator, press q to exit, otherwise enter a character"
    READ (*,*) quit 

    IF(quit == 'q') THEN
        EXIT
    END IF

    call getLOGdata(diaSmall, diaLarge, length, KERF)
    call calcLOGjclark(diaSmall,diaLarge,length,KERF,boardFeet)
    call calcLOGvolume(diaSmall,diaLarge,length,volume)

    WRITE (*,*) "The Board feet is: "
    WRITE (*,'(f20.2)') boardFeet
    WRITE (*,*) "The volume is: "
    WRITE (*,'(f20.2)') volume

END DO

END

!Gets user input

SUBROUTINE getLOGdata(diaSmall, diaLarge, length, KERF)

IMPLICIT NONE

REAL :: diaSmall, diaLarge, length

INTEGER :: KERF

!Read in smaller diameter

DO

    WRITE (*,*) "Enter the diameter inside bark at the log’s small end in inches numbers only"

    READ (*,*) diaSmall

    IF(diaSmall > 0) THEN
        EXIT
    END IF

    WRITE (*,*) "Error with input"

END DO

!Read in large diameter

DO

    WRITE (*,*) "Enter the diameter inside bark at the log's large end in inches numbers only"
    READ (*,*) diaLarge

    IF(diaLarge >= 0) THEN
        EXIT
    END IF
    
    WRITE (*,*) "Error with input"

END DO

!Read in length

DO

    WRITE (*,*) "Enter the log's length"
    READ (*,*) length

    IF(length > 0) THEN
        EXIT
    END IF
    
    WRITE (*,*) "Error with input"
    
END DO

!Read in kerf

DO

    WRITE (*,*) "Enter a 1 for KERF, 0 for no KERF"
    READ (*,*) KERF

    IF(KERF == 0) THEN
        EXIT
    END IF

    IF(KERF == 1) THEN
        EXIT
    END IF
    
    WRITE (*,*) "Error with input"
    
END DO

END SUBROUTINE getLOGdata

SUBROUTINE calcLOGjclark(diaSmall,diaLarge,totalLength,KERF,volume)

! *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
! THIS SUBROUTINE WAS WRITTEN BY J.E.BRICKELL OF THE U.S.FOREST SERVICE
! TO CALCULATE BOARD FOOT VOLUME OF SAWLOGS BY THE INTERNATIONAL RULE.
! VARIABLES IN THE CALLING SEQUENCE ARE:
! diaSmall = LOG’S SCALING DIAMETER (INCHES)
! diaLarge = DIB AT LOG’S LARGE END (INCHES) (0.0 IF 1/2 INCH TAPER)
! totalLength = TOTAL LOG LENGTH (FEET)
! KERF >0 IF KERF ASSUMPTION IS 1/4 INCH
! KERF <0, OR = 0, IF KERF ASSUMPTION IS 1/8 INCH
! volume = LOG VOLUME RETURNED TO THE CALLING PROGRAM
! *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

IMPLICIT NONE

REAL :: diaSmall, diaLarge, totalLength, volume

REAL :: taper, vadd, sectionLarge, diameterScale, diameterExtra, diamaterCalc, counterLarge, extraLengths

INTEGER :: KERF, footSegements
INTEGER :: I

volume = 0.0

! IF TOTAL LOG LENGTH IS LESS THAN FOUR FEET NO BOARD FOOT VOLUME WILL BE
! COMPUTED.

IF((totalLength-4.0) < 0) THEN
    RETURN
END IF

! IF THE LOG’S LARGE END DIAMETER IS FURNISHED TO JCLARK A TAPER RATE
! WILL BE COMPUTED. IF DL=0 THE STANDARD ASSUMPTION OF 1/2 INCH PER 4
! FEET OF LOG LENGTH WILL BE USED.

IF(diaLarge > 0) THEN
    taper=4.0*(diaLarge-diaSmall)/totalLength
ELSE
    taper=0.5
END IF

! THE FOLLOWING LOOP (THROUGH STATEMENT 5) FINDS OUT HOW MANY FULL 4
! FOOT SEGMENTS THE LOG CONTAINS.
! This is modulo 

DO I=1,20

    IF((totalLength-FLOAT(4*I)) < 0) THEN
        EXIT
    END IF

END DO

footSegements=I-1

sectionLarge=FLOAT(4*footSegements)

! THE FOLLOWING STATEMENT MOVES THE SCALING DIAMETER DOWN TO THE END OF
! THE 4 FOOT SEGMENTS AND INCREASES IT ACCORDING TO TAPER.

diameterScale=diaSmall+(taper/4.0)*(totalLength-sectionLarge)

! THE FOLLOWING LOOP (THROUGH STATEMENT 7) FINDS OUT HOW MANY FULL FEET
! OF LENGTH ARE IN THE SEGMENT LESS THAN 4 FEET LONG.
! This is mod

DO I=1,4

    counterLarge=FLOAT(I)

    IF((sectionLarge-totalLength+counterLarge) > 0) THEN
         EXIT
    END IF

END DO

! THE NEXT THREE STATEMENTS CALCULATE LOG VOLUME IN THE 1, 2, OR 3 FOOT
! SEGMENT AT THE SMALL END OF THE LOG.

extraLengths=counterLarge-1.0
diameterExtra=diaSmall+(taper/4.0)*(totalLength-sectionLarge-extraLengths)
VADD=0.055*extraLengths*(diameterExtra**2)-0.1775*extraLengths*diameterExtra

! THE FOLLOWING LOOP (THROUGH 9) CALCULATES VOLUME IN THE PORTION OF
! THE LOG CONTAINING WHOLE 4 FOOT SEGMENTS.

DO I=1,footSegements

    diamaterCalc=diameterScale+taper*FLOAT(I-1)
    volume =volume +0.22*(diamaterCalc**2)-0.71*diamaterCalc

END DO

volume = volume+VADD

! IF ‘KERF’ IS GREATER THAN ZERO, INTERNATIONAL 1/8 INCH VOLUME AS
! COMPUTED ABOVE WILL BE CONVERTED TO INTERNATIONAL 1/4 INCH VOLUME.

IF (KERF > 0) THEN

    volume = 0.905*volume

END IF

RETURN
END

!Calculates the volume of a log
SUBROUTINE calcLOGvolume(diaSmall,diaLarge,length,volume)

IMPLICIT NONE

REAL :: pi

REAL :: diaSmall,diaLarge,length,volume

REAL :: radSmallM, radLargeM, meterLength, areaSmall, areaLarge, sectionLarge, counterLarge, extraLengths

INTEGER :: footSegements, I

pi = 3.1415927

!Concerts the diameter inches into meters radius, 39.37 is the concersion, divide 2 converts diameter to radius

IF(diaLarge == 0) THEN
 
! THE FOLLOWING LOOP (THROUGH STATEMENT 5) FINDS OUT HOW MANY FULL 4
! FOOT SEGMENTS THE LOG CONTAINS.

    DO I=1,20
        IF((length-FLOAT(4*I)) < 0) THEN
            EXIT
        END IF
    END DO

    footSegements=I-1

    sectionLarge=FLOAT(4*footSegements)

! THE FOLLOWING STATEMENT MOVES THE SCALING DIAMETER DOWN TO THE END OF
! THE 4 FOOT SEGMENTS AND INCREASES IT ACCORDING TO TAPER.

! THE FOLLOWING LOOP (THROUGH STATEMENT 7) FINDS OUT HOW MANY FULL FEET
! OF LENGTH ARE IN THE SEGMENT LESS THAN 4 FEET LONG.

    DO I=1,4

        counterLarge=FLOAT(I)

        IF((sectionLarge-length+counterLarge) > 0) THEN
             EXIT
        END IF

     END DO

    extraLengths=counterLarge-1.0
    diaLarge = diaSmall + ((extraLengths+footSegements)*0.5)

END IF

!Converts diameter largeinto radius, thendivides by 2 into radius
radLargeM = (diaLarge / 39.37) / 2.0
radSmallM = (diaSmall / 39.37) / 2.0

!Converts the length into meters
meterLength = length
meterLength = meterLength / 3.2808

!Areas calculation
areaSmall = pi* (radSmallM**2)
areaLarge = pi* (radLargeM**2)

!Volume calculations
volume = ((areaSmall+areaLarge)/2)*meterLength

RETURN
END SUBROUTINE