;*******Subs for oleds**********

#ifdef useOled
	#ifdef oledMode4b
		#ifdef dataLow; ****
			#include "oledMode4bLSB.inc"
		#else; mode 4b data High******
			#include "oledMode4bMSB.inc"
		#endif
	#else; mode 8b ******
		#include "oledMode8b.inc"
	#endif
;---------------

oledSpace:
	movlw " "
	call oledWriteChar
	decfsz oledCptChar,f,a
		bra oledSpace
	return
;----------------

oledClrLine:
	_loada oledCptChar,olednChar
againClrLine:
	movlw " "
	call oledWriteChar
	decfsz oledCptChar,f,a
		bra againClrLine
	return
;------------------

	#ifdef useLcdStrFlashZ
oledStrFlashZ:
	tblrd*+
	movf TABLAT,w,a
	btfsc ZERO
		return
	call oledWriteChar
	bra oledStrFlashZ
	#endif

	#ifdef useLcdStrRamZ
oledStrRamZ:
	movf POSTINC2,w,a
	btfsc ZERO
		return
	call oledWriteChar
	bra oledStrRamZ
	#endif

	#ifdef useLoadCGRam
oledLoadCGRam:
	_loada oledCptByte,8
againOledCGRam:
 	tblrd*+
 	movf TABLAT,w,a
 	call oledWriteChar
 	decfsz oledCptByte,f,a
	 	bra againOledCGRam
	movlw SetDDRam
	call oledWriteCmd

	;_oledWriteCmd SetDDRam ;Line0, char0
	return
dbeAcute:	db 0b00100,0b01000,0b01110,0b10001,0b11111,0b10000,0b01110,0
dbeGrave:	db 0b00100,0b00010,0b01110,0b10001,0b11111,0b10000,0b01110,0
dbeCircum:	db 0b00100,0b01010,0b01110,0b10001,0b11111,0b10000,0b01110,0
dbOmega:	db 0b00000,0b01110,0b10001,0b10001,0b10001,0b01010,0b11011,0
dbMu:	db 0b10001,0b10001,0b10001,0b01110,0b10000,0b10000,0b10000,0
	#endif
;---------------
 
	#ifdef useOledBCD
oledPrintBCD:
  tstfsz oledFlag,a 
        bra skFirstDig
newLcdBCD:
    swapf INDF0,w,a
    rcall dispBCD
        bnz $+4
    return
skFirstDig:            
    movf POSTDEC0,w,a
    rcall dispBCD
        bnz newLcdBCD
endLcdBCD:            
        return
dispBCD:
    andlw 0xf
    tstfsz WREG,a; =0
        bra dispBCDChar; <>0
    tstfsz oledCptZSup,a; =0
        bra noDispBCDChar
dispBCDChar:
    clrf oledCptZSup,a
    addlw "0"
    call oledWriteChar
    decf oledCptDigit,f,a
    return
noDispBCDChar:
    decf oledCptZSup,f,a
    decf oledCptDigit,f,a
    return
	#endif
#endif
;--------------------------------------

