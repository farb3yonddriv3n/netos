[bits 16]
[org 0x7c00]

start:

code:
  mov eax, 0xBAADC0D3

   ; Copy the rest of the image at the specified address.

  mov bx, 0x2000 ; \ Target
  mov es, bx     ; / Segment.
  xor bx, bx
  mov di, bx     ; Target Offset.

  mov ds, bx        ; Source Segment.
  mov si, stage1end ; Source Offset.

  mov cx, ax     ; Number of bytes to be copied.

  rep movsb      ; Copying.

   ; Go to the second stage boot loader.
  jmp word 0x2000:0x0000

stage1end:
