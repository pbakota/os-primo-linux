; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%macro IN_C 1
  %ifnidn %1,al
	SaveAL
  %endif
	call	_ByteIn
	inc	al
	dec	al
        ror     ah,1
	lahf
  %ifnidn %1,al
	mov	%1,al
	LoadAL
  %endif
	Fetch
%endmacro

%macro OUT_C 1
  %ifnidn %1,al
	SaveAL
	mov	al,%1
  %endif
	call	_ByteOut
  %ifnidn %1,al
	LoadAL
  %endif
	Fetch
%endmacro

%macro LDMEMR16 1
	NextW	di
	WriteW	edi,%1
	Fetch
%endmacro

%macro LDR16MEM 1
	NextW	di
	mov	%1,word [edi+ebp]
	Fetch
%endmacro

%macro	ADCHL 1
        sahf
        adc    ZHL,%1
        lahf
        jo     short %%adchl_l0
        and    ah,0f9h
        Fetch
%%adchl_l0:
        and    ah,0f9h
        or     ah,4
        Fetch
%endmacro

%macro	SBCHL 1
        sahf
        sbb    ZHL,%1
        lahf
        jo     short %%sbchl_l0
        and    ah,0f3h
        Fetch
%%sbchl_l0:
        or     ah,4
        Fetch
%endmacro

%macro	ENDBLK	0
	and    	ah,0F1h
        dec    	ZBC
        jz    	short %%bl_end
        or    	ah,4
%%bl_end:      
%endmacro
