;Mode 4b dataMSB
			
oledPortSet:
 banksel oledTrisData
	movlw 0x0f
	andwf oledTrisData,b; 0000tttt, out
	bcf oledTrisCde,oledPinAlim,b; out
	bcf oledTrisCde,oledPinRS,b; out
	bcf oledTrisCde,oledPinRW,b; out
	bcf oledTrisCde,oledPinE,b; out
	return

oledCheckBusy: ;OledBusy-->BF=1 else 0
	bcf oledRS; Cmd
 banksel oledTrisData; mode 4b data High
	movlw 0xf0
	iorwf oledTrisData,f,b; 1111tttt, in
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
	btfsc oledTmp,7,a
		bra oledBusy
	bcf oledRW
 banksel oledTrisData
	movlw 0x0f
	andwf oledTrisData,f,b
	retlw 0

oledWriteCmd:; mode 4b data High
	bcf oledRS;Write cmd
	rcall oledWrite
	return
oledWriteChar:
	bsf oledRS; Write Char
	rcall oledWrite
	return
oledWrite:
	movwf oledTmp,a
	swapf oledTmp,f,a; char(lsb:msb)
	rcall oledWriteNibble
	swapf oledTmp,f,a; char(msb:lsb)
	rcall oledWriteNibble
	return
oledWriteNibble:
	bcf oledRW
	movlw 0x0f
	andwf oledPortData,f,a; 0000pppp
	swapf oledTmp,w,a
	andlw 0xf0; dddd0000--> w
	iorwf oledPortData,f,a; ddddpppp
	bsf oledE
	_dly3 3
	bcf oledE
	return



