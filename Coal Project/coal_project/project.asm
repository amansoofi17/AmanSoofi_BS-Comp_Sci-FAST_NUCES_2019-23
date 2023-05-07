INCLUDE Irvine32.inc
.data
input_length = 30
str_title byte  "                 *********************************MACHINE CODE GENERATOR***********************     ",0dh,0ah,0
str1 byte "   ENTER ASSEMBLY INSTRUCTION : ",0dh,0ah,0
result byte " MACHINE CODE IN HEXADECIMAL : ",0dh,0ah,0
assembly_instruction byte input_length dup(?)
length_string dword 0 
nemonic byte 5 dup(?)
n_length dword 0
s_operand byte 50 dup(0)
s_length dword 0
d_operand byte 50 dup(0)
d_length dword 0

data_sizes byte "byte,word,dwor",0
data_size_count byte 0 ;initially zero
displacement_value dword 0
temp_displacement_value byte 8 dup(?)
immidiate dword 0 
check_immidiate byte 0 ;initially zero means no immediate value 

register32 byte "eax,ecx,edx,ebx,esp,ebp,esi,edi",0
register16 byte "ax,cx,dx,bx,sp,bp,si,di",0
register_lower_8 byte "al,cl,dl,bl",0
register_higher_8 byte "ah,ch,dh,bh",0
register_values byte "000,001,010,011,100,101,110,111",0
check_al byte ? ;checking if operand is al 
check_ax byte ? ;checking if operand is ax
check_16bit byte 0

opcode_extension_nemonic byte "mov,add,sub,mul,div,inc,dec",0
opcode_extension byte "000,000,101,100,110,000,001",0
nemonic_count byte 0
nemonic_number byte 0


d_bit byte ?
w_bit byte ?
d_operand_check byte 0  ;set initially to zero if destination operand is register then it sets
s_operand_check byte 00 ;set initially to 00 (means there is immediate value present there)
                        ;if source operand is register then it sets
						;if source operand is memory then it clears
mod_bits byte ?
check_displacement byte 00 ; initially 00 means there is no displacement 
                           ; if check_displacement = 0 then 8bit displacement 
                           ; and for 16bit/32bit displacement  check_diplacement = 1
check_one_operand byte 0
register_bits byte 3 dup(?)
register_number byte ? ; this is used for storing the number of reigster for calculating the
                       ; register bits of the r/m byte
register_count  byte ? ; it is like a register count which is assigned to the register number
r_m_bits byte 3 dup(?)
r_m_number byte 0 ;initially zero it is set according to respective match and values 

prefix_byte byte ?
complete_r_mbyte byte 8 dup(?)

memory_format byte 0 ;initially zero 
;  memory_fomrat = 0 when there is direct address normal variable like var8,var32
;  memory_format = 1 if this type of format [esi] or [ebx+esi]
                     ; [esi+//displacement] [ebx+edi+//displacement]
hex_value_opcode byte 0
mov_opcode byte 1,0,0,0,1,0,2 dup(?)
add_opcode byte 0,0,0,0,0,0,2 dup(?)
sub_opcode byte 0,0,1,0,1,0,2 dup(?)
xchg_opcode byte 1,0,0,0,0,1,2 dup(?)

.code
main proc

call crlf
call crlf
;display str on console
mov edx,offset str_title
call writestring
call crlf
call crlf


;display str1 on console
mov edx,offset str1
call writestring

;take input of assembly instruction 
mov ecx,input_length
mov edx,offset assembly_instruction
call readstring
mov length_string,eax 

call crlf
call crlf


;seperating the nemonic,source operand and destination operand from assembly instruction
mov esi,offset assembly_instruction
mov cl,32
mov edi,offset nemonic

;seperating the nemonic
mov al,'m'
n_start:
cmp [esi],cl
je n_over
mov bl,[esi]
cmp bl,al
jz continue
mov [edi],bl
inc esi
inc edi
inc n_length
jmp n_start

continue:
mov esi,offset assembly_instruction
mov edi,offset nemonic
mov ecx,3
movzx_nemonic:
mov bl,[esi]
mov [edi],bl
inc esi
inc edi
inc n_length
loop movzx_nemonic

n_over:
inc esi
mov edi,offset d_operand
mov cl,44
mov dl,10
;seperating the destination 
d_start:
cmp [esi],cl
je d_over
cmp [esi],dl
je one_operand
mov bl,[esi]
mov [edi],bl
inc esi
inc edi
inc d_length
jmp d_start

d_over:
inc esi
mov edi,offset s_operand
mov cl,10

 ;seperating the source
s_start:
cmp [esi],cl
je s_over
mov bl,[esi]
mov [edi],bl
inc esi
inc edi
inc s_length
jmp s_start

s_over:
dec s_length

;firstly we have to check the values of source and destination operands and check if the immediate
;value occurs

call check_source_operand
call check_destination_operand
call store_immidiate_value
; after checking we have to calculate the opcode 

;firstly for the opcode if any operand from both is al/ax

call cal_opcode_if_accumlator
cmp hex_value_opcode,0   ;as i  initially assign zero to hex_value_opcode now after comparasion if it
                         ;is zero then no operand in the instruction is al/ax/eax
jnz calculate_r_m_byte 

; now we have to calculate the opcode if there is immediate operand in the source operand

;firstly we have to check whether there is immediate value exists

call store_immidiate_value

cmp check_immidiate,1 ;if it is 1 then immediate value exists in the instruction
jnz check_next
call cal_machine_code_if_mem_reg_immidiate

;here we know that there is immediate value in the source operand so if there is register
;in the destination we can find our machine code directly

cmp d_operand_check,1    ;checking destination operand is register or not  
jnz calculate_r_m_byte

call cal_one_register_one_immidaite_value
jmp final_result

check_next:  ;after checking above conditions now we have confirm that now we have register to register/
             ;register to memory or memory to register
call cal_opcode

calculate_r_m_byte:
; now we have to caluculate r/m byte 
cmp check_immidiate,1  ;if there is immediate data present in the source operand means that there is
                       ; one memory opernad to immediate data 
jnz check_next1

push offset d_operand
call cal_RMbyte
jmp final_result
check_next1:
; now firstly we have to find that memory is present at which operand push offset of that operand on
;stack

cmp s_operand_check,0
jnz check_next2
push offset s_operand
call cal_RMbyte
jmp final_result

check_next2:       ; if firstly condition fails it means memory operand is present at the destination
                       ; operand if destination operand is also the register then we further check
cmp d_operand_check,0
jnz check_next3
push offset d_operand
call cal_RMbyte
jmp final_result

check_next3:
;now it is confirmed that both operands are registers then

call cal_RMbyte_of_register_operand
jmp final_result


final_result:
call cal_final_result

again_call:
cmp check_displacement,00
jz check_imm 
mov eax,0
cmp check_displacement,0
jnz check_16
mov al,byte ptr displacement_value
ror eax,4
call writehex
mov al,' '
call writechar
jmp ex
check_16:
cmp check_16bit,1
jnz check_32
mov bx,word ptr displacement_value
mov ax,word ptr displacement_value+2
ror al,4
rol ah,4
mov word ptr displacement_value+2,ax
mov word ptr displacement_value,bx
mov eax,displacement_value
call writehex
mov al,' '
call writechar
jmp ex
check_32:
mov bx,word ptr displacement_value
ror bl,4
rol bh,4
mov ax,word ptr displacement_value+2
ror al,4
rol ah,4
mov word ptr displacement_value+2,ax
mov word ptr displacement_value,bx
mov eax,displacement_value
call writehex
mov al,' '
call writechar
jmp ex

check_imm:
; if immediate exist then prints in little endian
cmp s_operand_check,00
jnz ex
mov eax,0
mov bx,word ptr immidiate
ror bl,4
rol bh,4
mov ax,word ptr immidiate+2
ror al,4
rol ah,4
mov word ptr immidiate+2,ax
mov word ptr immidiate,bx
mov eax,immidiate
call writehex
mov al,' '
call writechar
jmp ex

one_operand:
mov check_one_operand,1
call check_destination_operand
push offset d_operand
call cal_one_operand_memory_register
call cal_final_result
;jmp again_call
ex:
call crlf
exit
main ENDP


cal_opcode_if_accumlator proc
push ebp
mov ebp,esp
mov s_operand_check,0 ;initially zero
mov d_operand_check,0 ;initially zero
mov nemonic_number,0  ;initially zero
 
call check_source_operand  ;checking the source operand
call check_destination_operand ;checking the destination operand  
call cal_nemonic_number

cmp s_operand_check,1
jnz check_dest
push offset s_operand
call check_operand_al ;checking whether source operand is al
push offset s_operand
call check_operand_ax ;checking whether source operand is ax
mov dl,nemonic_number
cmp dl,0
jnz xchg_condition
cmp d_operand_check,0
jnz xchg_condition
cmp check_al,1
jnz check_ax0
mov hex_value_opcode,0A0h
jmp ex
check_ax0:
cmp check_ax,1
jnz check_dest
mov hex_value_opcode,0A1h
jmp ex

xchg_condition:
mov al,'x' ; checking for xchg nemonic
mov edi,offset nemonic
cmp [edi],al
jnz check_dest
cmp check_ax,1
jnz check_dest
cmp d_operand_check,1
jnz check_dest
mov register_number,0 ;initially zero
push offset d_operand
call cal_register_number
mov hex_value_opcode,90h
mov al,register_number
add hex_value_opcode,al
jmp ex


;; checking destination operand 
check_dest:
cmp d_operand_check,1
jnz ex
cmp check_immidiate,1 ;if there is immediate value and destination operand should be register then further
                      ;checking is continued
jnz ex
push offset d_operand
call check_operand_al ;checking whether source operand is al
push offset d_operand
call check_operand_ax ;checking whether source operand is ax
mov dl,nemonic_number

cmp dl,0
jnz next_check
cmp check_al,1
jnz check_ax1
mov hex_value_opcode,0A0h
jmp ex
check_ax1:
cmp check_ax,1
jnz ex
mov hex_value_opcode,0A1h
jmp ex

next_check:
cmp dl,1
jnz next_check1
cmp check_al,1
jnz check_ax2
mov hex_value_opcode,4h
jmp ex
check_ax2:
cmp check_ax,1
jnz ex
mov hex_value_opcode,5h
jmp ex
next_check1:
cmp dl,2
jnz ex
jnz next_check1
cmp check_al,1
jnz check_ax3
mov hex_value_opcode,02Ch
jmp ex
check_ax3:
cmp check_ax,1
jnz check_dest
mov hex_value_opcode,02Dh
jmp ex

mov hex_value_opcode,0

ex:
pop ebp
ret 
cal_opcode_if_accumlator endp

cal_machine_code_if_mem_reg_immidiate proc
push ebp
mov ebp,esp

mov ax,word ptr immidiate
mov bx,word ptr immidiate+2
call cal_nemonic_number
mov dl,nemonic_number

cmp ah,0 ;means 8bit immediate value
jnz condition_16_32
cmp dl,0
jnz check_next
cmp d_operand_check,1
jnz ex
mov hex_value_opcode,0C6h
jmp opcode_calculated
check_next:
cmp dl,1
jnz check_next1
mov hex_value_opcode,80h
jmp opcode_calculated

check_next1:
cmp dl,2
jnz ex
mov hex_value_opcode,80h
jmp opcode_calculated

condition_16_32:
;; for 16/32 bit condition
cmp dl,0
jnz check_next2
cmp d_operand_check,1
jnz ex
mov hex_value_opcode,0C7h
jmp opcode_calculated

check_next2:
cmp dl,1
jnz check_next3
mov hex_value_opcode,81h
jmp opcode_calculated

check_next3:
cmp dl,2
jnz ex
mov hex_value_opcode,81h
jmp opcode_calculated

opcode_calculated:
push offset s_operand
call cal_RMbyte
ex:
pop ebp
ret
cal_machine_code_if_mem_reg_immidiate endp

check_operand_al proc
push ebp 
mov ebp,esp
mov esi,[ebp+8]
mov al,'a'
mov ecx,2
l1:
cmp [esi],al
jnz out_loop  
cmp ecx,1
jnz next_condition
mov check_al,1
jmp ex
next_condition:
inc esi
mov al,'l'
loop l1
out_loop:
mov check_al,0
ex:
pop ebp
ret 4
check_operand_al endp

check_operand_ax proc
push ebp 
mov ebp,esp
mov esi,[ebp+8]
mov al,'a'
mov ecx,2
l1:
cmp [esi],al
jnz out_loop  
cmp ecx,1
jnz next_condition
mov check_ax,1
jmp ex
next_condition:
inc esi
mov al,'x'
loop l1
out_loop:
mov check_ax,0
ex:
pop ebp
ret 4
check_operand_ax endp


cal_opcode proc USES esi edi ebx
push ebp
mov ebp,esp
call cal_nemonic_number   ; because we have to check the number of nemonic 
mov d_bit,0 ;initially zero
mov w_bit,0 ;initially zero
;;;;;;;;;;;;;;;;;;;;;;;; checking source register ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
call check_source_operand
;;;;;;;;;;;;;;;;;;;;;;;; checking destination register ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
call check_destination_operand
mov al,0

cmp nemonic_number,al
jnz check_next
mov esi,offset mov_opcode
add esi,6

;store d_bit 
mov bl,d_bit
mov [esi],bl

inc esi

;store w_bit 
mov bl,w_bit
mov [esi],bl

push offset mov_opcode
call convert_8emlemnts_array_into8bithexvalue
jmp opcode_found

check_next:
inc al

cmp nemonic_number,al
jnz check_next1
mov esi,offset add_opcode
add esi,6

;store d_bit 
mov bl,d_bit
mov [esi],bl
 
 
inc esi

;store w_bit 
mov bl,w_bit
mov [esi],bl

push offset add_opcode
call convert_8emlemnts_array_into8bithexvalue
jmp opcode_found


check_next1:
inc al

cmp nemonic_number,al
jnz check_next2
mov esi,offset sub_opcode
add esi,6


;store d_bit 
mov bl,d_bit
mov [esi],bl


inc esi
 
;store w_bit 
mov bl,w_bit
mov [esi],bl

push offset sub_opcode
call convert_8emlemnts_array_into8bithexvalue
jmp opcode_found

check_next2:

; for xchg condition
mov esi,offset xchg_opcode
add esi,6

;store d_bit 
mov bl,d_bit
mov [esi],bl
 
inc esi


;store w_bit 
mov bl,w_bit
mov [esi],bl

push offset xchg_opcode
call convert_8emlemnts_array_into8bithexvalue

opcode_found:
pop ebp
ret
cal_opcode endp

check_source_operand proc
push ebp
mov ebp,esp
;;;;; checking for the register;;;;;;;;;;;;;;;;
mov edi,offset s_operand
mov al,[edi]
mov ebx,offset register32 

;checking 32bit resgister
mov ecx,8
cmp al,[ebx]
jnz out_loop32
l32:
mov edx,ecx 
mov ecx,s_length
dec ecx
l2:
add ebx,type register32
add edi,type s_operand
mov al,[edi]
cmp al,[ebx]
jnz outerloop32
cmp ecx,1
jnz inner
mov d_bit,0  ;clear D bit if source is 32 bit register
mov w_bit,1  ;set W bit if source is 32bit/16bit register
mov s_operand_check,1
jmp source_operand_checked 
inner:
loop l2
outerloop32:
sub edi,type s_operand
add ebx,3
mov ecx,edx
loop l32
out_loop32:

;checking 16bit resgister
mov edi,offset s_operand
mov al,[edi]
mov ebx,offset register16
mov ecx,8
l16:
cmp al,[ebx]
jnz direct_check16
add ebx,type register16
add edi,type s_operand
mov al,[edi]
cmp al,[ebx]
jnz outerloop16
mov d_bit,0 ;clear D bit if source is 16 bit register
mov w_bit,1  ;set W bit if source is 32bit/16bit register
mov s_operand_check,1
mov check_16bit,1
jmp source_operand_checked 
outerloop16:
sub edi,type s_operand
add ebx,2
jmp direct_loop16

direct_check16:
add ebx,3

direct_loop16:
loop l16

;checking higher 8 bit register
mov edi,offset s_operand
mov al,[edi]
mov ebx,offset register_higher_8
mov ecx,4
l_higher8:
cmp al,[ebx]
jnz direct_check_higher8
add ebx,type register_higher_8
add edi,type s_operand
mov al,[edi]
cmp al,[ebx]
jnz outerloop_higher8
mov d_bit,0 ;clear D bit if source is higher 8bit register
mov w_bit,0  ;clear W bit if source is 8bit register
mov s_operand_check,1
jmp source_operand_checked 
outerloop_higher8:
sub edi,type s_operand
add ebx,2
jmp direct_loop_higher8

direct_check_higher8:
add ebx,3

direct_loop_higher8:
loop l_higher8

;checking lower 8 bit register
mov edi,offset s_operand
mov al,[edi]
mov ebx,offset register_lower_8
mov ecx,4
l_lower8:
cmp al,[ebx]
jnz direct_check_lower8
add ebx,type register_lower_8
add edi,type s_operand
mov al,[edi]
cmp al,[ebx]
jnz outerloop_lower8
mov d_bit,0 ;clear D bit if source is lower 8bit register
mov w_bit,0  ;clear W bit if source is 8bit register
mov s_operand_check,1
jmp source_operand_checked 
outerloop_lower8:
sub edi,type s_operand
add ebx,2
jmp direct_loop_lower8

direct_check_lower8:
add ebx,3

direct_loop_lower8:
loop l_lower8

mov d_bit,1 ;if source operand is not a register 

mov edi,offset s_operand
mov ebx, offset data_sizes
mov al,[edi]
mov ecx,3
l1:
cmp al,[ebx]
jz next1
add ebx,5
inc data_size_count
loop l1
jmp next2

next1:
mov s_operand_check,0
push offset s_operand
call store_displacement_value
jmp source_operand_checked

next2:
mov edi,offset s_operand
mov al,'['
cmp [edi],al
jnz next3 
jmp next1

next3:
mov edi,offset s_operand
mov al,0
mov ecx,10
check_immidiate1:
cmp[edi],al
jz jump1   ;1st character of s_operand array lie in between (0-9) then it is obvious that s_operand is immidiate value
jmp direct_jump
jump1:
mov s_operand_check,00
call store_immidiate_value
jmp source_operand_checked

direct_jump:
inc al
loop check_immidiate1

;; checking normal variable
mov s_operand_check,0
mov memory_format,0  ; is zero when there is direct adressing is used

source_operand_checked:
pop ebp
ret
check_source_operand endp

check_destination_operand proc
push ebp
mov ebp,esp

;;;;;;;;;;;;;; checking for the register;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
mov esi,offset d_operand
mov al,[esi]
mov ebx,offset register32 

;checking 32bit resgister
mov ecx,8
cmp al,[ebx]
jnz d_out_loop32
d_l32:
mov edx,ecx 
mov ecx,d_length
dec ecx
d_l2:
add ebx,type register32
add esi,type d_operand
mov al,[esi]
cmp al,[ebx]
jnz d_outerloop32
cmp ecx,1
jnz d_inner
mov w_bit,1  ;set W bit if source is 32bit/16bit register
mov d_operand_check,1 ; sets if destination operand is register
jmp ex 
d_inner:
loop d_l2
d_outerloop32:
sub esi,type d_operand
add ebx,3
mov ecx,edx
loop d_l32
d_out_loop32:

;checking 16bit resgister
mov esi,offset d_operand
mov al,[esi]
mov ebx,offset register16
mov ecx,8
d_l16:
cmp al,[ebx]
jnz d_direct_check16
add ebx,type register16
add esi,type d_operand
mov al,[esi]
cmp al,[ebx]
jnz d_outerloop16
mov w_bit,1  ;set W bit if source is 32bit/16bit register
mov d_operand_check,1 ; sets if destination operand is register
mov check_16bit,1
jmp ex 
d_outerloop16:
sub esi,type d_operand
add ebx,2
jmp d_direct_loop16

d_direct_check16:
add ebx,3

d_direct_loop16:
loop d_l16

;checking higher 8 bit register
mov esi,offset d_operand
mov al,[esi]
mov ebx,offset register_higher_8
mov ecx,4
d_l_higher8:
cmp al,[ebx]
jnz d_direct_check_higher8
add ebx,type register_higher_8
add esi,type d_operand
mov al,[esi]
cmp al,[ebx]
jnz d_outerloop_higher8
mov w_bit,0  ;clear W bit if source is 8bit register
mov d_operand_check,1 ; sets if destination operand is register
jmp ex 
d_outerloop_higher8:
sub esi,type d_operand
add ebx,2
jmp d_direct_loop_higher8

d_direct_check_higher8:
add ebx,3

d_direct_loop_higher8:
loop d_l_higher8

;checking lower 8 bit register
mov esi,offset d_operand
mov al,[esi]
mov ebx,offset register_lower_8
mov ecx,4
d_l_lower8:
cmp al,[ebx]
jnz d_direct_check_lower8
add ebx,type register_lower_8
add esi,type d_operand
mov al,[esi]
cmp al,[ebx]
jnz d_outerloop_lower8
mov w_bit,0  ;clear W bit if source is 8bit register
mov d_operand_check,1 ; sets if destination operand is register
jmp ex 
d_outerloop_lower8:
sub esi,type d_operand
add ebx,2
jmp d_direct_loop_lower8

d_direct_check_lower8:
add ebx,3

d_direct_loop_lower8:
loop d_l_lower8


;;; checking if destination operand is memory operand

;; byte/word/dword ptr[esi+11] checking this type of format
mov edi,offset d_operand
mov ebx, offset data_sizes
mov al,[edi]
mov ecx,3
l1:
cmp al,[ebx]
jz next1
add ebx,5
inc data_size_count
loop l1
jmp next2

next1:
mov d_operand_check,0
push offset d_operand
call store_displacement_value
jmp ex

;;;;[esi+11] checking this type of format

next2:
mov edi,offset d_operand
mov al,'['
cmp [edi],al
jnz next3 
jmp next1

;; checking normal variable
next3:
mov d_operand_check,0
mov memory_format,0  ; is zero when there is direct adressing is used

ex:
pop ebp
ret 
check_destination_operand endp


store_immidiate_value proc
push ebp
mov ebp,esp
mov immidiate,0
mov check_immidiate,0 ;initially zero
call check_source_operand
cmp s_operand_check,00
jnz ex
clc
mov edi,offset s_operand
mov ecx,s_length
l1:
mov edx,ecx
mov al,[edi]
mov ecx,4
loop_inner:
rcr al,1
rcr immidiate,1
loop loop_inner
add edi,1
mov ecx,edx
loop l1
mov check_immidiate,1
ex:
pop ebp
ret 
store_immidiate_value endp


store_displacement_value proc
push ebp
mov ebp,esp
mov edi,[ebp+8]
mov ebx, offset data_sizes
mov al,[edi]
mov displacement_value,0 ;initially zero
mov ecx,3
l1:
cmp al,[ebx]
jz operand_checked
add ebx,5
inc data_size_count
loop l1

operand_checked:
mov edi,[ebp+8]
mov al,'+'
mov dl,'e'
mov bl,']'
l2:
cmp [edi],al
jz check_offset_register
cmp [edi],bl
jz check_howmany_bitsof_displacement

add edi,1
jmp direct_loopl2
check_offset_register:
cmp [edi],dl  ;checking for [ebx+esi+123] this type of format
jz check_32
mov dl,'s'
cmp [edi],dl
jz check_16
mov dl,'d'
cmp [edi],dl
jz check_16
jmp memory_with_displacement
direct_loopl2:
jmp l2

check_32:
add edi,3
mov al,'+'
cmp [edi],al
jnz direct_addr
mov memory_format,1
jmp outerloop
check_16:
add edi,2
cmp [edi],al
jnz direct_addr
mov memory_format,1
jmp outerloop

memory_with_displacement:
mov memory_format,1 

outerloop:
inc edi  ;now edi points to starting point to the displacement value if exists
mov esi,offset displacement_value
clc 
l3:
cmp [edi],bl
jz check_howmany_bitsof_displacement
mov al,[edi]
mov ecx,4
loop_inner:
rcr al,1

rcr displacement_value,1
loop loop_inner
add edi,1
jmp l3

check_howmany_bitsof_displacement:

cmp displacement_value,0
jnz next1
direct_addr: ;if there is no displacement means direct addressig
mov memory_format,1 ;; if there is no displacement then there is direct addressing
mov check_displacement,00
jmp ex
next1:
mov eax,displacement_value
cmp ax,0
jnz next2
cmp ah,0
jnz eight_bit
mov check_displacement,1 ; displacement is 16 bit
jmp ex
eight_bit:
mov check_displacement,0 ; displacement is 8 bit 
jmp ex
next2:
mov check_displacement,1 ; displacement is 32 bit
ex:
pop ebp
ret 4
store_displacement_value endp



cal_one_operand_memory_register proc
push ebp
mov ebp,esp
mov esi,[ebp+8]

call cal_nemonic_number

cmp d_operand_check,0
jnz check_operand
mov al,'v'      ;because we give variable name in this format var8/var16/var32
cmp al,[esi] 
jnz check_operand_continue
add esi,3
mov al,8
cmp [esi],al
jnz bit16_32
mov w_bit,0
jmp check_operand
bit16_32:
mov w_bit,1
jmp check_operand

check_operand_continue:
mov esi,[ebp+8]
mov al,'['
l1:
cmp [esi],al
jnz jump_continue
mov w_bit,1
jmp check_operand

jump_continue:
inc esi
jmp l1


check_operand:
cmp nemonic_number,3
jnz check_next_nemonic
cmp w_bit,0
jnz next_register
mov hex_value_opcode,0F6h
jmp opcode_find
next_register:
mov hex_value_opcode,0F7h
jmp opcode_find

check_next_nemonic:
cmp nemonic_number,4
jnz check_next_nemonic1
cmp w_bit,0
jnz next_register1
mov hex_value_opcode,0F6h
jmp opcode_find
next_register1:
mov hex_value_opcode,0F7h
jmp opcode_find 

check_next_nemonic1:
cmp nemonic_number,5
jnz check_next_nemonic2
cmp w_bit,0
jnz next_register2
mov hex_value_opcode,0FEh
jmp opcode_find
next_register2:
cmp d_operand_check,0
jnz register_opcode_value_nemonic
mov hex_value_opcode,0FFh
jmp opcode_find 
register_opcode_value_nemonic:
mov hex_value_opcode,40h
jmp opcode_find 

check_next_nemonic2:
cmp w_bit,0
jnz next_register3
mov hex_value_opcode,0FEh
jmp opcode_find
next_register3:
cmp d_operand_check,0
jnz register_opcode_value_nemonic1
mov hex_value_opcode,0FFh
jmp opcode_find 
register_opcode_value_nemonic1:
mov hex_value_opcode,48h

opcode_find: 
mov esi,[ebp+8]
cmp d_operand_check,1
jnz memory_operand
push esi
call cal_register_number
mov ecx,8
mov al,0
set_code:
cmp register_number,al
jnz direct_loop
add hex_value_opcode,al
jmp code_found
direct_loop:
inc al
loop set_code

memory_operand:
mov esi,[ebp+8]
push esi
call store_displacement_value

cmp check_displacement,00 ;checking for displacement
jnz next_bits
mov mod_bits,00
mov memory_format,0
jmp further_processing

next_bits:
cmp check_displacement,0
jnz next_bits1
mov mod_bits,01
mov memory_format,1
jmp further_processing

next_bits1:
mov mod_bits,10
mov memory_format,1

further_processing:
mov esi,[ebp+8]
push esi ;pushing offset of partciular memory operand
call cal_register_bits

mov esi,[ebp+8] 
push esi ;pushing offset of partciular memory operand
call set_rm_number

mov edi,offset r_m_bits
mov esi,offset register_values
mov bl,0
mov ecx,7
l3: 
mov edx,ecx
cmp r_m_number,bl
jnz direct_loop1
mov ecx,3
l4:
mov al,[esi]
sub al,48
mov [edi],al
inc edi
inc esi
cmp ecx,1
jz ex
loop l4
direct_loop1:
inc bl
add esi,4
mov ecx,edx
loop l3
ex:
call store_compelete_r_mbyte

code_found:
pop ebp
ret 4
cal_one_operand_memory_register endp



cal_one_register_one_immidaite_value proc
push ebp
mov ebp,esp
call cal_one_operand_memory_register
call store_immidiate_value
pop ebp
ret 4
cal_one_register_one_immidaite_value endp

convert_8emlemnts_array_into8bithexvalue proc
push ebp
mov ebp,esp
mov esi,[ebp+8]
mov hex_value_opcode,0 ;initially zero
mov ecx,8
mov ebx,0
mov bl,0
clc 
l1:
mov al,[esi]
rcr al,1    ;from this we get the lsb (one bit) of the that particular element in the cf 

rcl bl,1   ;here i store the particular bit of cf from the lsb bit of bl 
inc esi 
loop l1
mov hex_value_opcode,bl
pop ebp
ret 4
convert_8emlemnts_array_into8bithexvalue endp

cal_modbits proc USES esi edi ebx
push ebp
mov ebp,esp
call check_source_operand
call check_destination_operand
    ;;;;;;;;;;;;calculating mod bits;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 1st check
; checking for mod = 11
cmp d_bit,0  ;looking for source operand as a register
jnz second_check
cmp d_operand_check,1 ;looking for destination operand as a register
jnz second_check
mov mod_bits,11
jmp mod_bits_found

second_check:
; checking for mod = 00
cmp d_bit,1       ;looking for source operand as a memroy
jz mod_value_00
cmp d_operand_check,0 ;looking for destination operand as a memory
jnz third_check
mod_value_00:
cmp check_displacement,00 ;checking for displacement
jnz third_check
mov mod_bits,00
jmp mod_bits_found

third_check:
; checking for mod = 01
cmp check_displacement,0
jnz fourth_check
mov mod_bits,01
jmp mod_bits_found

fourth_check:
; checking for mod = 10
; if above three  conditions of mod_bits fails so it means displacement is 16/32 bits
; so mod_bits = 10
mov mod_bits,10

mod_bits_found:
pop ebp
ret
cal_modbits endp

cal_register_bits proc USES esi edi ebx
push ebp
mov ebp,esp
mov ebx,[ebp+8]
mov register_number,0 ;initially we set it to the zero and we use a count variable
                      ; it is like a count which is added to register number according to number
;;;;;;;;; condition where both are registers;;;;;;;;;;;;;;;;;;;;
;for register bits i have used numbering for each register like 
;eax/ax/al = 0 and ecx/cx/cl = 1 edx/dx/dl = 2 and ebx/bx/bl = 3
;esp/sp/ah = 4  ebp/bp/ch = 5   esi/si/dh = 6  edi/di/bh = 7 

;1st_condition
cmp mod_bits,11
jnz second_condition
push offset s_operand 
call cal_register_number
jmp store_register_bits

source_condition:
mov ebx,[ebp+8]
push ebx
call cal_register_number
jmp store_register_bits


second_condition:
cmp s_operand_check,1
jnz check_destination

jmp source_condition

check_destination:
cmp d_operand_check,1
jnz other_condition
push offset d_operand
call cal_register_number
jmp store_register_bits


store_register_bits:
;;;; storing register bits
mov ecx,8
mov esi,offset register_bits
mov edi,offset register_values
mov register_count,0
mov dl,register_count
l1:
cmp register_number,dl
jnz direct_l
mov ecx,3
inner_l:
mov al,[edi]
sub al,48 ;because it firstly stores ascii value
mov [esi],al
add edi,type register_values
add esi,type register_bits
cmp ecx,1
jnz inner_loop
jmp register_bits_find
inner_loop:
loop inner_l
direct_l:
add edi,4
inc dl
loop l1

other_condition:
;;if there is one memory operand and immidiate value
cmp s_operand_check,00 ;means if there is immediate value at source operand
jnz ex
cmp d_operand_check,0
jnz ex
;;;;;; conditions for opcode extension;;;;;;;;;;;;;
call cal_nemonic_number
;; storing register bits if there is one memory operand and immidiate value
mov ecx,7
mov esi,offset register_bits
mov edi,offset opcode_extension
mov nemonic_count,0
mov dl,nemonic_count
loop2:
cmp nemonic_number,dl
jnz direct_l2
mov ecx,3
inner_l2:
mov al,[edi]
sub al,48 ;because it firstly stores ascii value
mov [esi],al
add edi,type opcode_extension
add esi,type register_bits
cmp ecx,1
jnz inner_loop2
jmp register_bits_find
inner_loop2:
loop inner_l2
direct_l2:
add edi,4
inc dl
loop loop2

register_bits_find:
ex:
pop ebp
ret 4
cal_register_bits endp

cal_RMbyte_of_register_operand proc
push ebp
mov ebp,esp

mov mod_bits,11

;now calculating the register bits
push offset s_operand
call cal_register_bits

; now calculating the r/m bits
push offset d_operand
call cal_register_number


mov edi,offset r_m_bits
mov esi,offset register_values
mov bl,0
mov ecx,8
l1: 
mov edx,ecx
cmp register_number,bl
jnz direct_loop
mov ecx,3
l2:
mov al,[esi]
sub al,48
mov [edi],al
inc edi
inc esi
cmp ecx,1
jz ex
loop l2
direct_loop:
inc bl
add esi,4
mov ecx,edx
loop l1
ex:
call store_compelete_r_mbyte
pop ebp
ret
cal_RMbyte_of_register_operand endp

cal_RMbyte proc
push ebp
mov ebp,esp
mov esi,[ebp+8]
push esi ;pushing offset of partciular memory operand
call store_displacement_value

call cal_modbits

mov esi,[ebp+8]
push esi ;pushing offset of partciular memory operand
call cal_register_bits

mov esi,[ebp+8] 
push esi ;pushing offset of partciular memory operand
call set_rm_number

mov edi,offset r_m_bits
mov esi,offset register_values
mov bl,0
mov ecx,7
l3: 
mov edx,ecx
cmp r_m_number,bl
jnz direct_loop1
mov ecx,3
l4:
mov al,[esi]
sub al,48
mov [edi],al
inc edi
inc esi
cmp ecx,1
jz ex
loop l4
direct_loop1:
inc bl
add esi,4
mov ecx,edx
loop l3
ex:
call store_compelete_r_mbyte
pop ebp
ret 4
cal_RMbyte endp

set_rm_number proc
push ebp
mov ebp,esp
mov esi,[ebp+8]

cmp memory_format,0
jnz inner_check
mov r_m_number,6
jmp r_m_bits_calculated
inner_check:
cmp memory_format,1
jnz ex
mov al,[esi]
mov bl,'e'
inc esi ;because this condition is true when there is format like [esi] so that's why i am 
        ;increamenting by which it can move to the e
cmp [esi],bl
jnz check_next
inc esi
mov bl,'s'
cmp [esi],bl
jnz inner_check_next1
mov r_m_number,4
jmp r_m_bits_calculated
inner_check_next1:
mov bl,'d'
cmp[esi],bl
jnz inner_check_next2
mov r_m_number,5
jmp r_m_bits_calculated
inner_check_next2:
mov bl,'b'
cmp[esi],bl
jnz check_next
mov bl,'x'
inc esi
cmp [esi],bl
jnz final_check
mov r_m_number,7
jmp r_m_bits_calculated
final_check:
mov r_m_number,6
jmp r_m_bits_calculated

check_next:
mov esi,[ebp+8]
inc esi
mov bl,'s'
cmp [esi],bl
jnz inner_check_next3
mov r_m_number,4
jmp r_m_bits_calculated
inner_check_next3:
mov bl,'d'
cmp[esi],bl
jnz inner_check_next4
mov r_m_number,5
jmp r_m_bits_calculated
inner_check_next4:
mov bl,'b'
cmp [esi],bl
jnz check_next1
mov bl,'x'
inc esi
cmp [esi],bl
jnz final_check1
mov r_m_number,7
jmp r_m_bits_calculated
final_check1:
mov r_m_number,6
jmp r_m_bits_calculated


check_next1:
mov esi,[ebp+8]
inc esi
mov bl,'e'
cmp [esi],bl
jnz check_next2
inc esi
mov bl,'b'
cmp [esi],bl
jnz ex
inc esi
mov bl,'x'
cmp [esi],bl
jnz inner_check_next5
add esi,2 ;because plus sign come because format is [ebx+esi]
jmp inner_check_next6
inner_check_next5:
mov bl,'p'
cmp [esi],bl
jnz ex
add esi,2 ;because plus sign come because format is [ebp+esi]
inner_check_next6: ;now esi pointer the value after (+)
mov bl,'e'
cmp [esi],bl
jnz ex
mov bl,'s'
inc esi
cmp[esi],bl
jnz inner_check_next7

sub esi,3      ; i have subtracted three form esi because i have to check whether p or x 
               ; is present before the + sign because i have to set the value accordingly
mov bl,'x'
cmp[esi],bl
jnz inner_check_next8
mov r_m_number,0
jmp r_m_bits_calculated

inner_check_next8:

mov r_m_number,2
jmp r_m_bits_calculated

inner_check_next7:
mov bl,'d'
cmp[esi],bl
jnz ex 
sub esi,3      ; i have subtracted three form esi because i have to check whether p or x 
               ; is present before the + sign because i have to set the value accordingly
mov bl,'x'
cmp[esi],bl
jnz inner_check_next9
mov r_m_number,0
jmp r_m_bits_calculated

inner_check_next9:

mov r_m_number,2
jmp r_m_bits_calculated

check_next2:
mov esi,[ebp+8]
inc esi
mov bl,'b'
cmp [esi],bl
jnz ex
inc esi
mov bl,'x'
cmp [esi],bl
jnz inner_check_next10
add esi,2 ;because plus sign come because format is [bx+si]
jmp inner_check_next11
inner_check_next10:
mov bl,'p'
cmp [esi],bl
jnz ex
add esi,2 ;because plus sign come because format is [bp+si]
inner_check_next11: ;now esi pointer the value after (+)
mov bl,'s'
cmp[esi],bl
jnz inner_check_next12

sub esi,2     ; i have subtracted three form esi because i have to check whether p or x 
               ; is present before the + sign because i have to set the value accordingly
mov bl,'x'
cmp[esi],bl
jnz inner_check_next13
mov r_m_number,0
jmp r_m_bits_calculated

inner_check_next13:

mov r_m_number,2
jmp r_m_bits_calculated

inner_check_next12:
mov bl,'d'
cmp[esi],bl
jnz ex 
sub esi,3      ; i have subtracted three form esi because i have to check whether p or x 
               ; is present before the + sign because i have to set the value accordingly
mov bl,'x'
cmp[esi],bl
jnz inner_check_next14
mov r_m_number,0
jmp r_m_bits_calculated

inner_check_next14:

mov r_m_number,2
r_m_bits_calculated:
ex:
pop ebp
ret 4
set_rm_number endp


store_compelete_r_mbyte proc
push ebp
mov ebp,esp
mov esi,offset complete_r_mbyte
mov edi,offset register_bits

;firstly storing mod bits

mov al,mod_bits

cmp al,11
jnz check_next
mov bl,1
mov [esi],bl
inc esi
mov bl,1
mov [esi],bl
jmp mod_bits_stored

check_next:
cmp al,00
jnz check_next1
mov bl,0
mov [esi],bl
inc esi
mov bl,0
mov [esi],bl
jmp mod_bits_stored

check_next1:
cmp al,01
jnz check_next2
mov bl,0
mov [esi],bl
inc esi
mov bl,1
mov [esi],bl
jmp mod_bits_stored

check_next2:
mov bl,1
mov [esi],bl
inc esi
mov bl,0
mov [esi],bl

mod_bits_stored:

; storing regsiter bits

mov al,[edi]
mov ecx,3
l1:
inc esi
mov [esi],al
inc edi
mov al,[edi]
loop l1

;storing r/m bits

mov ebx,offset r_m_bits
mov al,[ebx]
mov ecx,3
l2:
inc esi
mov [esi],al
inc ebx
mov al,[ebx]
loop l2

;;;;;complete r/m byte stored

pop ebp
ret
store_compelete_r_mbyte endp


cal_register_number proc 
push ebp
mov ebp,esp
mov esi,[ebp+8]
mov register_count,0 ;initially it also set to the zero
mov register_number,0
mov edi,esi
mov ebx,offset register32
mov al,[edi]
mov ecx,8
cmp al,[ebx]
jnz out_loop32
l32:
mov edx,ecx 
mov ecx,3
dec ecx
l2:
add ebx,type register32
add edi,1
mov al,[edi]
cmp al,[ebx]
jnz outerloop32
cmp ecx,1
jnz inner
mov al,register_count
mov register_number,al
jmp ex 
inner:
loop l2
outerloop32:
sub edi,1
add ebx,3
inc register_count
mov ecx,edx
loop l32
out_loop32:

mov register_count,0 ;again initialize with zero

;checking 16bit resgister
mov edi,esi
mov al,[edi]
mov ebx,offset register16
mov ecx,8
l16:
cmp al,[ebx]
jnz direct_check16
add ebx,type register16
add edi,1
mov al,[edi]
cmp al,[ebx]
jnz outerloop16
mov al,register_count
mov register_number,al
jmp ex 
outerloop16:
sub edi,1
add ebx,2
jmp direct_loop16

direct_check16:
add ebx,3

direct_loop16:
inc register_count
loop l16

mov register_count,4 

;checking higher 8 bit register
mov edi,esi
mov al,[edi]
mov ebx,offset register_higher_8
mov ecx,4
l_higher8:
cmp al,[ebx]
jnz direct_check_higher8
add ebx,type register_higher_8
add edi,1
mov al,[edi]
cmp al,[ebx]
jnz outerloop_higher8
mov al,register_count
mov register_number,al
jmp ex 
outerloop_higher8:
sub edi,1
add ebx,2
jmp direct_loop_higher8

direct_check_higher8:
add ebx,3

direct_loop_higher8:
inc register_count
loop l_higher8

mov register_count,0

;checking lower 8 bit register
mov edi,esi
mov al,[edi]
mov ebx,offset register_lower_8
mov ecx,4
l_lower8:
cmp al,[ebx]
jnz direct_check_lower8
add ebx,type register_lower_8
add edi,1
mov al,[edi]
cmp al,[ebx]
jnz outerloop_lower8
mov al,register_count
mov register_number,al
jmp ex 
outerloop_lower8:
sub edi,1
add ebx,2
jmp direct_loop_lower8

direct_check_lower8:
add ebx,3

direct_loop_lower8:
inc register_count
loop l_lower8

ex:
pop ebp
ret 4
cal_register_number endp

cal_nemonic_number proc
push ebp
mov ebp,esp
mov edi,offset nemonic
mov ebx,offset opcode_extension_nemonic
mov nemonic_count,0
mov nemonic_number,0
mov al,[edi]
mov ecx,7
l32:
mov edx,ecx 
cmp al,[ebx]
jnz direct_check
mov ecx,2
l2:
add ebx,type register32
add edi,type s_operand
mov al,[edi]
cmp al,[ebx]
jnz outerloop
cmp ecx,1
jnz inner
mov al,nemonic_count
mov nemonic_number,al
jmp out_loop 
inner:
loop l2
outerloop:
sub edi,type nemonic
add ebx,3
direct_check:
add ebx,4
direct_loop:
inc nemonic_count
mov ecx,edx
loop l32
out_loop:
pop ebp
ret 
cal_nemonic_number endp

cal_final_result proc
push ebp
mov ebp,esp
mov edx,offset result
call writestring


mov eax,0
cmp d_operand_check,1
jz found
cmp s_operand_check,1
jnz next_process
found:
cmp check_16bit,1 ;if there is 16_bit_operand then we have to appened prefix byte to final
                  ;output because we have to differentiate that machine code from 32 bit.
jnz next_process
mov prefix_byte,66h
mov al,prefix_byte
call writehex
mov al,' '
call writechar

next_process:
mov al,hex_value_opcode
call writehex
mov al,' '
call writechar

cmp check_one_operand,1
jnz next_check1
cmp d_operand_check,1
jz ex
push offset complete_r_mbyte
call convert_8emlemnts_array_into8bithexvalue
mov al,hex_value_opcode
call writehex
mov al,' '
call writechar
jmp next_process2




next_check1:
cmp mod_bits,11
jnz next_check
push offset complete_r_mbyte
call convert_8emlemnts_array_into8bithexvalue
mov al,hex_value_opcode
call writehex
mov al,' '
call writechar
jmp next_process2


next_check:

cmp d_operand_check,0
jnz next_process1
push offset complete_r_mbyte
call convert_8emlemnts_array_into8bithexvalue
mov al,hex_value_opcode
call writehex
mov al,' '
call writechar
jmp next_process2

next_process1:
cmp s_operand_check,0
jnz next_process2
push offset complete_r_mbyte
call convert_8emlemnts_array_into8bithexvalue
mov al,hex_value_opcode
call writehex
mov al,' '
call writechar
next_process2:
ex:
pop ebp
ret 
cal_final_result endp
END main

 


