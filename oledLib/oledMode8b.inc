;Mode 8b

oledPortSet:
 banksel oledTrisData
	clrf oledTrisData,b; 0, out
	bcf oledTrisCde,oledPinAlim,b; out
	bcf oledTrisCde,oledPinRS,b; out
	bcf oledTrisCde,oledPinRW,b; out
	bcf oledTrisCde,oledPinE,b; out
	return

oledCheckBusy: ;LCDBusy-->BF=1 else 0
	bcf oledRS; Cmd
 banksel oledTrisData; mode 8b
	setf oledTrisData,b; 11111111, in
	bsf oledRW; read
oledBusy:
	bsf oledE
	_dly3 1
	btfsc oledPortData,7,a
		bra oledBusy
	bcf oledE
	_dly3 3
 banksel oledTrisData
	clrf oledTrisData,b; all out
	bcf oledRW; write
	retlw 0

oledWriteChar:
	bsf oledRS
	rcall oledWrite
	return
oledWriteCmd:
	bcf oledRS
	rcall oledWrite
	return
oledWrite:
	bcf oledRW
	movwf oledPortData,a; ppppdddd
	bsf oledE
	_dly3 3
	bcf  oledE
	return



