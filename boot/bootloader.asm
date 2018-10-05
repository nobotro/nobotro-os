[org 0x7c00]
 
jmp load

 				; jump over OEM block

;*************************************************;
;	OEM Parameter block
;*************************************************;

start:

times 0Bh-$+start DB 0

bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 	    DB 2
bpbRootEntries: 	    DW 224
bpbTotalSectors: 	    DW 2880
bpbMedia: 	            DB 0xF0
bpbSectorsPerFAT: 	    DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors: 	    DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 	            DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "nobotro os"
bsFileSystem: 	        DB "FAT12"


load:

MOV EBP, 0x9000                       ; Set stack base at top of free space
MOV ESP, EBP
 mov ah,00
int 13h





;load kernel to memory
read_sector:
pusha
mov ax, 0x0
mov es, ax      ; ES = 0
mov bx, 0x1000  ; BX = 0x1000. ES:BX=0x0:0x1000 
                ; ES:BX = starting address to read sector(s) into
mov ah, 02      ; Int 13h/AH=2 = Read Sectors From Drive
mov al, 15   ; Sectors to read = 15
mov ch, 00      ; CH=Cylinder. Second sector of disk
                ; is at Cylinder 0 not 1
mov cl, 02      ; Sector to read = 2
mov dh, 00      ; Head to read = 0
                ; DL hasn't been destroyed by our bootloader code and still
                ;     contains boot drive # passed to our bootloader by the BIOS
int 13h
popa

cli


 

xor ax,ax
mov ds, ax 
  
lgdt [gdt_descriptor]

 
  
 mov eax , cr0
or eax , 0x1

mov cr0 , eax



jmp gdt_codeSeg:init_pm



[bits 32]

 
init_pm:
 
MOV AX, gdt_dataSeg                     ; Update segments for protected mode as defined in GDT
MOV DS, AX
MOV SS, AX
MOV ES, AX
; MOV FS, AX
; MOV GS, AX

MOV EBP, 0x9000                       ; Set stack base at top of free space
MOV ESP, EBP 



call 0x1000;jump to kernel head
 
jmp $






 








 ; Global descriptor table for 32-bit protected mode
gdt_start:                              ; Start of global descriptor table
    gdt_null:                           ; Null descriptor chunk
        dd 0x00
        dd 0x00
    gdt_code:                           ; Code descriptor chunk
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xCF
        db 0x00
    gdt_data:                           ; Data descriptor chunk
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xCF
        db 0x00
    gdt_end:                            ; Bottom of table
gdt_descriptor:                         ; Table descriptor
    dw gdt_end - gdt_start - 1          ; Size of table
    dd gdt_start                        ; Start point of table
    
gdt_codeSeg equ gdt_code - gdt_start    ; Offset of code segment from start
gdt_dataSeg equ gdt_data - gdt_start    ; Offset of data segment from start

; Tail

times 510 -( $ - $$ ) db 0 
dw 0xaa55
