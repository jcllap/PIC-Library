;**********************macro's LCD****************
_oledWriteNibble macro nibble
	_loada oledTmp, nibble
	bcf oledRS	;Write cmd
	call oledWriteNibble
	endm
;-----------------------

_oledInit macro
	_dly100k 5
	call oledPortSet
	#ifdef oledMode4b
		_oledWriteNibble 0
		_oledWriteNibble 0
		_oledWriteNibble 0
		_oledWriteNibble 0
		_oledWriteNibble 0; *5 for reset
		_oledWriteNibble 2
		_oledWriteNibble 2
		_oledWriteNibble TwoLine
		;_dly100k 5
	#else
		_oledWriteCmd (FunctionSet+Data8b+TwoLine);+Font5x10)
	#endif
		_oledWriteCmd 0x08; DispCtrl + DispOff + CursorOff + BlinkOff
		_oledWriteCmd 0x06;Inc, no shift
		_oledWriteCmd 0x13; Char mode, Power off
		_oledWriteCmd 0x01; Clr disp
		_oledWriteCmd 0x02; Return home
		_oledWriteCmd 0x0c; Disp on
		;_oledWriteCmd (ModeDisp+PwrOn)
	endm
;_____________

_oledWriteCmd macro cmd
	call oledCheckBusy
	movlw cmd
	call oledWriteCmd
	endm
;-----------------------

_oledWriteChar macro char
	call oledCheckBusy
	movlw char
	call oledWriteChar
	endm
;-----------------

_oledLocate macro  yLine,xCur ;0 to 3, 0 to 20 or other
	_oledWriteCmd (SetDDRam + yLine+ xCur)
	endm
;---------------------

_oledClrLine macro yLine
	_oledWriteCmd (SetDDRam + yLine)
	call oledClrLine
	_oledLocate yLine,0
	endm
;--------------

_oledClrDisp macro
	_oledWriteCmd ClrDisp  
	endm
;---------------------

_oledChar macro char
	movlw char
	call oledWriteChar
	endm
;------------------------

_oledSpace macro nbr; disp nbr space
	_loada oledCptChar,nbr
	call oledSpace
	endm
;---------------------

_oledStrFlashZ macro pFlash
 #ifndef useLcdStrFlashZ
	#define  useLcdStrFlashZ
#endif
	_loada24 TBLPTR, pFlash
	call oledStrFlashZ
 endm
;------------------------

_oledStrRamZ macro pRam
 #ifndef useLcdStrRamZ
	#define  useLcdStrRamZ
#endif
	_loada16 FSR2, pRam
	call oledStrRamZ
 endm
;-----------------

_oledLoadCGRam macro pNewChar, addChar
#ifndef useLoadCGRam;0>=AddChar<=7
 	#define useLoadCGRam
#endif
	_loada16 TBLPTRL,pNewChar
 	_oledWriteCmd SetCGRam+8*addChar
	call oledLoadCGRam
	endm
;-------------------------------

_oledPrintBCD macro HReg,nDigit,nZSup,bSkFirst;OK
;Enter: Reg high for display left to right
;Display char <0...9>
;Skip first digit if bSkFirst is set 
;Clr digit no disp and set NbZSup
#ifndef useOledBCD
	#define useOledBCD
#endif
	lfsr 0, HReg
	_loada oledFlag, bSkFirst
	_loada oledCptDigit,nDigit
	_loada oledCptZSup,nZSup
	call oledPrintBCD
 endm




