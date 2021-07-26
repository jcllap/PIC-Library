;Mode 4b dataLSB

oledPortSet:
 banksel oledTrisData
	movlw 0xf0
	andwf oledTrisData,f,b; tttt0000, out
	bcf oledTrisCde,oledPinAlim,b; out
	bcf oledTrisCde,oledPinRS,b; out
	bcf oledTrisCde,oledPinRW,b; out
	bcf oledTrisCde,oledPinE,b; out
	return

oledCheckBusy: ;LCDBusy-->BF=1 else 0
	bcf oledRS; Cmd
	movlw 0x0f
 banksel oledTrisData;Mode 4b dataLow
	iorwf oledTrisData,f,b; tttt1111, in
 	bsf oledRW; read
oledBusy:
	bsf oledE
	_dly3 1
	movff oledPortData,oledTmp
	bcf oledE
	_dly3 1
	bsf oledE
	_dly3 1
	bcf oledE
	_dly3 1
	btfsc oledTmp,3,a
		bra oledBusy
	bcf oledRW
 banksel oledTrisData
	movlw 0xf0
	andwf oledTrisData,f,b; tttt0000, out
	retlw 0

oledWriteCmd:;Mode 4b dataLow
	bcf oledRS;Write cmd
	rcall oledWrite
	return
oledWriteChar:
	bsf oledRS; Write Char
	rcall oledWrite
	return
oledWrite:
	movwf oledTmp,a
	swapf oledTmp,f,a
	rcall oledWriteNibble; char( lsb:msb)
	swapf oledTmp,f,a; char( msb:lsb)
	rcall oledWriteNibble; 
	return
oledWriteNibble:
	movlw 0xf0
	andwf oledPortData,f,a; pppp0000
	movf oledTmp,w,a
	andlw 0x0f; 0000dddd--> w
	iorwf oledPortData,f,a; ppppdddd
	bsf oledE
	_dly3 3
	bcf oledE
	return



