;-------------------DefineOled------------------
#define oledMode4b; default mode8b

#ifdef oledMode4b
	;#define dataLow; default dataHigh
#endif

#ifndef useOled
	#define useOled
#endif

#ifndef useDly
    #define useDly
#endif

 messg "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
#ifdef oledMode4b
	#ifdef dataLow
		messg "Mode4b selected & dataLow."
	#else
		messg "Mode4b selected & dataHigh."
	#endif
#else
	 messg "Mode8b selected"
#endif

 messg "Warning **See pin's Oled**"
 messg "It's  needed to define oledPORTData , oledTrisData"
 messg "It's  needed to define oledPORTCde <xxx>, oledTrisCde"
 messg "It's  needed to define oledAlim <x>"
 messg "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"

global oledTmp 
psect dataOvr,space=1,ovrld,class=COMRAM;psect udata_ovr,ovrld,class=COMRAM,space=SPACE_DATA,noexec,lowdata
 org 0
oledTmp:		ds  1
oledCptChar:	ds  1
oledCptZSup:	ds  1
oledCptByte:	ds  1
oledCptDigit:	ds  1
oledCptBusy:	ds  1
oledFlag:		ds  1

#define oledTrisCde TRISC
#define oledPortCde PORTC
oledPinAlim equ 0; commande low
oledPinRS equ 1
oledPinRW equ 2
oledPinE equ 3
#define oledTrisData TRISC
#define oledPortData PORTC
#define oledAlim oledPortCde,oledPinAlim,a
#define oledRS oledPortCde,oledPinRS,a	;RS 1=Data,0=Cde
#define oledRW oledPortCde,oledPinRW,a	;1=Read,0=Write
#define oledE oledPortCde,oledPinE,a	;Enable transfer 0 to 1
#define oledOn bcf oledAlim; PMOSFet
#define oledOff bsf oledAlim

#define fOledPower oledFlag,0,a
;-----------------------------
 
olednChar equ 20; (d20)
olednLine equ 1 ; 0 to 1

Line0 equ 0
Line1 equ 0x40
Line2 set olednChar
Line3 set Line1+olednChar

;-----------------Clr display-------1.53 ms
ClrDisp	equ		0b1	
;-----------------Return home-------1.53ms
RetHome	equ		0b10	
;-----------------Mode Set-----------39 µs
ModeSet	 equ		0b100	
IncDDRam	 equ		0b10
DecDDRam   equ		0b00
ShiftEntire equ		0b1
NoShift	 equ		0b0
;-----------Disp OnOff Ctrl----------
DispCtrl	equ		0b1000
DispOn	equ		0b100
DispOff	equ		0b000
CursorOn	equ		0b10
CursorOff	equ		0b00
BlinkOn	equ		0b1
BlinkOff	equ		0b0
;----------Shift cursor--------------
ShiftCursor		equ		0b10000
ShiftCurLeft	equ		0b0000
ShiftCurRight	equ		0b1000
ShiftEntireL	equ		0b000
ShiftEntireR	equ		0b100
;---------ModeDisp-----------------
ModeDisp		equ		0b10011
GraphicMode	equ		0b1000
CharMode		equ		0b0000
PwrOn		equ		0b100
PwrOff		equ		0b000
;------Function set----------------
FunctionSet	equ		0b100000
Data8b		equ		0b10000
Data4b		equ		0b00000
TwoLine		equ		0b1000
OneLine		equ		0b0000
Font5x8		equ		0b000
Font5x10		equ		0b100
FontUKJap		equ		0b00
FontWestEU1	equ		0b01; not use in 4bMode
FontUKRuss		equ		0b10
FontWestEU2	equ		0b11; not use in 4bMode
;-------------------------------
SetCGRam		equ		0b01000000; + address 6 bits
;----------------------------
SetDDRam		equ		0b10000000; + address 7 bits
;------------------------------------

#include "oledMac.inc"
