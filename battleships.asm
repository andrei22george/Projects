.386
.model flat, stdcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;includem biblioteci, si declaram ce functii vrem sa importam
includelib msvcrt.lib
extern exit: proc
extern malloc: proc
extern memset: proc
extern printf: proc
extern scanf: proc

includelib canvas.lib
extern BeginDrawing: proc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;declaram simbolul start ca public - de acolo incepe executia
public start
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;sectiunile programului, date, respectiv cod
.data
;aici declaram date	
window_title DB "Vaporase (Battleships)", 0
area_width EQU 640 ; dimensiunile ferestrei.
area_height EQU 500
area DD 0

counterReset DD 0 ; numara evenimentele de tip timer
counterOk DD 0 ; numara de cand s-a afisat ok
seconds_counter DD 0 ; numara secundele

arg1 EQU 8
arg2 EQU 12
arg3 EQU 16
arg4 EQU 20

n DD 0 ; numarul de patratele per inaltime
m DD 0 ; numarul de patratele per lungime

dist_x DD 0
dist_y DD 0

grid_x EQU 20
grid_y EQU 50

cord_x DD 0
cord_y DD 0

square_x DD 0
square_y DD 0

square_size_n DD 0
square_size_m DD 0

grid_size EQU 400

matrice DD 0

ok DD 0

descoperite DD 0
nedescoperite DD 0
ratari DD 0
total DD 20

vapor_1_x_1 DD 20
vapor_1_x_2  DD 60
vapor_1_x_3 DD 100
vapor_1_y DD 50

vapor_2_x DD 180
vapor_2_y_1 DD 50
vapor_2_y_2 DD 90
vapor_2_y_3 DD 130
vapor_2_y_4 DD 170

vapor_3_x DD 300
vapor_3_y_1 DD 130
vapor_3_y_2 DD 170
vapor_3_y_3 DD 210
vapor_3_y_4 DD 250

vapor_4_x_1 DD 20
vapor_4_x_2 DD 60
vapor_4_y DD 170

vapor_5_x_1 DD 100
vapor_5_x_2 DD 140
vapor_5_x_3 DD 180
vapor_5_y DD 250

vapor_6_x_1 DD 100
vapor_6_x_2 DD 140
vapor_6_x_3 DD 180
vapor_6_x_4 DD 220
vapor_6_y DD 330

symbol_width EQU 10
symbol_height EQU 20
include digits.inc
include letters.inc

format DB "%d %d", 0
mesaj DB "Introuceti n si m: ", 0

.code

make_text proc
	push ebp
	mov ebp, esp
	pusha

	mov eax, [ebp+arg1] ; citim simbolul de afisat
	cmp eax, 'A'
	jl make_digit
	cmp eax, 'Z'
	jg make_digit
	sub eax, 'A'
	lea esi, letters
	jmp draw_text
make_digit:
	cmp eax, '0'
	jl make_space
	cmp eax, '9'
	jg make_space
	sub eax, '0'
	lea esi, digits
	jmp draw_text
make_space:
	mov eax, 26 ; de la 0 pana la 25 sunt litere, 26 e space
	lea esi, letters

draw_text:
	mov ebx, symbol_width
	mul ebx
	mov ebx, symbol_height
	mul ebx
	add esi, eax
	mov ecx, symbol_height
bucla_simbol_linii:
	mov edi, [ebp+arg2] ; pointer la matricea de pixeli
	mov eax, [ebp+arg4] ; pointer la coord y
	add eax, symbol_height
	sub eax, ecx
	mov ebx, area_width
	mul ebx
	add eax, [ebp+arg3] ; pointer la coord x
	shl eax, 2 ; inmultim cu 4, avem un DWORD per pixel
	add edi, eax
	push ecx
	mov ecx, symbol_width
bucla_simbol_coloane:
	cmp byte ptr [esi], 1
	je simbol_pixel_alb
	cmp byte ptr [esi], 0
	je simbol_pixel_negru
	cmp byte ptr [esi], 2
	je simbol_pixel_kaki
	cmp byte ptr [esi], 3
	je simbol_pixel_rosu
	mov dword ptr [edi], 0
	jmp simbol_pixel_next
simbol_pixel_alb:
	mov dword ptr [edi], 0FFFFFFh
	jmp simbol_pixel_next
simbol_pixel_negru:
	mov dword ptr [edi], 0
	jmp simbol_pixel_next
simbol_pixel_kaki:
	mov dword ptr [edi], 426122h
	jmp simbol_pixel_next 
simbol_pixel_rosu:
	mov dword ptr [edi], 0E51C1Ch
	jmp simbol_pixel_next
simbol_pixel_next:
	inc esi
	add edi, 4
	loop bucla_simbol_coloane
	pop ecx
	loop bucla_simbol_linii
	popa
	mov esp, ebp
	pop ebp
	ret
make_text endp

; un macro ca sa apelam mai usor desenarea simbolului
make_text_macro macro symbol, drawArea, x, y
	push y
	push x
	push drawArea
	push symbol
	call make_text
	add esp, 16
endm

draw_rectangle macro square_x, square_y, square_height, square_length, color
local loop_line, et
	mov eax, square_y
	mov ebx, area_width
	mul ebx
	add eax, square_x
	shl eax, 2
	add eax, area
	mov ebx, square_height
et:
	mov ecx, square_length
loop_line:
	mov dword ptr[eax], color
	add eax, 4
	loop loop_line
	add eax, 4 * area_width
	mov esi, square_length
	shl esi, 2
	sub eax, esi
	dec ebx
	cmp ebx,0
	jne et
endm

line_horizontal macro x, y, len, color
local bucla_line
	mov eax, y ; EAX = y
	mov ebx, area_width
	mul ebx ; EAX = y * area_width
	add eax, x ; EAX = y * area_width + x
	shl eax, 2 ; EAX = (y * area_width + x) * 4
	add eax, area ; pointer la vectorul area, a fost alocat cu malloc.
	mov ecx, len
bucla_line:
	mov dword ptr[eax], color
	add eax, 4
	loop bucla_line
endm

line_vertical macro x, y, len, color
local bucla_line
	mov eax, y
	mov ebx, area_width
	mul ebx
	add eax, x
	shl eax, 2 
	add eax, area
	mov ecx, len
bucla_line:
	mov dword ptr[eax], color
	add eax, 4*area_width
	loop bucla_line
endm

grid_col macro n
local eticheta
	mov ecx, n
	mov eax, grid_size
	div ecx
	mov square_size_n, eax
	mov dist_x, eax
	mov edi, grid_x
	add edi, dist_x
eticheta:
	push ecx
	line_vertical edi, grid_y, grid_size, 802025h
	add edi, dist_x
	pop ecx
	loop eticheta
endm

grid_lin macro m
local eticheta
	mov ecx, m
	mov eax, grid_size
	div ecx
	mov square_size_m, eax
	mov dist_y, eax
	mov edi, grid_y
	add edi, dist_y
eticheta:
	push ecx
	line_horizontal grid_x, edi, grid_size, 802025h
	add edi, dist_y
	pop ecx
	loop eticheta
endm

modify macro initial, replace
	mov edx, replace
	mov initial, edx
endm

; initializarea unui vector ce consta din 0 si 1 pentru identificarea partatelor unde este vapor si unde nu, care nu a mers

; init macro   
; local eticheta
	; mov eax,n
	; mul m
	; mov ecx,eax
	; mov nedescoperite, eax
	; mov esi, 0
; eticheta:
	; mov eax, [matrice]
	; mov dword ptr[eax+esi*4], 0
	; inc esi
	; loop eticheta
	; mov eax, [matrice]
	; mov dword ptr[eax+2*4], 1
	; mov dword ptr[eax+4*4], 1
; endm

identificare macro x, y 
local exit, ratare
	
	mov eax, grid_x
	cmp dword ptr x, eax
	jl exit
	add eax, grid_size
	cmp dword ptr x, eax
	jg exit
	mov eax, grid_y
	cmp dword ptr y, eax
	jl exit
	add eax, grid_size
	cmp dword ptr y, eax
	jg exit
	
	mov eax, x
	sub eax, grid_x
	mov edx, 0
	div dist_x
	mov square_x, eax
	
	mov eax, dist_x
	mul square_x
	add eax, grid_x
	mov x, eax
	
	mov eax, y
	sub eax, grid_y
	mov edx, 0 ; overflow daca nu pun 0 in edx!
	div dist_y
	mov square_y, eax
	
	mov eax, dist_y
	mul square_y
	add eax, grid_y
	mov y, eax
	
ratare:
	draw_rectangle x, y, dist_y, dist_x, 0611F1Ah
	inc ratari
	dec nedescoperite ; cate casute au ramas de incercat
exit:
endm

; functia de desenare - se apeleaza la fiecare click
; sau la fiecare interval de 200ms in care nu s-a dat click
; arg1 - evt (0 - initializare, 1 - click, 2 - s-a scurs intervalul fara click)
; arg2 - x
; arg3 - y

draw proc
	push ebp
	mov ebp, esp
	pusha

	mov eax, [ebp+arg1]
	cmp eax, 1
	jz evt_click
	cmp eax, 2
	jz evt_timer 
	;mai jos e codul care intializeaza fereastra cu pixeli albi
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	push 0 ; aici se initializeaza prima culoare a fundalului(255 = alb).
	push area
	call memset
	add esp, 12
reset:
	mov descoperite, 0
	mov ratari, 0
	draw_rectangle grid_x, grid_y, 400, 400, 2E76A3h
	grid_col n
	grid_lin m
	draw_rectangle grid_x, grid_y, grid_size, 5, 802025h ; stanga
	draw_rectangle grid_x, grid_y + grid_size, 5, grid_size, 802025h ; jos
	draw_rectangle grid_x + grid_size, grid_y, grid_size + 5, 5, 802025h ; dreapta
	draw_rectangle grid_x, grid_y, 5, grid_size, 802025h ; sus
	
	jmp afisare_litere

evt_click:
	; sa nu se dea click de doua ori pe aceeasi
	mov eax,[ebp+arg3] 
    mov ebx,area_width
    mul ebx 
    add eax,[ebp+arg2]
    shl eax,2 
    add eax,area
	cmp dword ptr[eax], 2E76A3h     
	jne evt_timer

	modify ok, 0
	
	vapor_1_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_1_x_1
	jl vapor_1_1_fail
	sub eax, square_size_n
	cmp eax, vapor_1_x_1
	jg vapor_1_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_1_y
	jl vapor_1_1_fail
	sub eax, square_size_m
	cmp eax, vapor_1_y
	jg vapor_1_1_fail
	draw_rectangle vapor_1_x_1, vapor_1_y, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_1_1_fail:
	; draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	; identificare [ebp+arg2], [ebp+arg3]
	; mov counterOk, 0
	
vapor_1_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_1_x_2
	jl vapor_1_2_fail
	sub eax, square_size_n
	cmp eax, vapor_1_x_2
	jg vapor_1_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_1_y
	jl vapor_1_2_fail
	sub eax, square_size_m
	cmp eax, vapor_1_y
	jg vapor_1_2_fail
	draw_rectangle vapor_1_x_2, vapor_1_y, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_1_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_1_3_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_1_x_3
	jl vapor_1_3_fail
	sub eax, square_size_n
	cmp eax, vapor_1_x_3
	jg vapor_1_3_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_1_y
	jl vapor_1_3_fail
	sub eax, square_size_m
	cmp eax, vapor_1_y
	jg vapor_1_3_fail
	draw_rectangle vapor_1_x_3, vapor_1_y, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_1_3_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_2_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_2_x
	jl vapor_2_1_fail
	sub eax, square_size_n
	cmp eax, vapor_2_x
	jg vapor_2_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_2_y_1
	jl vapor_2_1_fail
	sub eax, square_size_m
	cmp eax, vapor_2_y_1
	jg vapor_2_1_fail
	draw_rectangle vapor_2_x, vapor_2_y_1, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite
	
vapor_2_1_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_2_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_2_x
	jl vapor_2_2_fail
	sub eax, square_size_n
	cmp eax, vapor_2_x
	jg vapor_2_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_2_y_2
	jl vapor_2_2_fail
	sub eax, square_size_m
	cmp eax, vapor_2_y_2
	jg vapor_2_2_fail
	draw_rectangle vapor_2_x, vapor_2_y_2, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite
		
vapor_2_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_2_3_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_2_x
	jl vapor_2_3_fail
	sub eax, square_size_n
	cmp eax, vapor_2_x
	jg vapor_2_3_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_2_y_3
	jl vapor_2_3_fail
	sub eax, square_size_m
	cmp eax, vapor_2_y_3
	jg vapor_2_3_fail
	draw_rectangle vapor_2_x, vapor_2_y_3, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_2_3_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_2_4_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_2_x
	jl vapor_2_4_fail
	sub eax, square_size_n
	cmp eax, vapor_2_x
	jg vapor_2_4_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_2_y_4
	jl vapor_2_4_fail
	sub eax, square_size_m
	cmp eax, vapor_2_y_4 
	jg vapor_2_4_fail
	draw_rectangle vapor_2_x, vapor_2_y_4, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_2_4_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_3_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_3_x
	jl vapor_3_1_fail
	sub eax, square_size_n
	cmp eax, vapor_3_x
	jg vapor_3_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_3_y_1
	jl vapor_3_1_fail
	sub eax, square_size_m
	cmp eax, vapor_3_y_1
	jg vapor_3_1_fail
	draw_rectangle vapor_3_x, vapor_3_y_1, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_3_1_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_3_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_3_x
	jl vapor_3_2_fail
	sub eax, square_size_n
	cmp eax, vapor_3_x
	jg vapor_3_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_3_y_2
	jl vapor_3_2_fail
	sub eax, square_size_m
	cmp eax, vapor_3_y_2
	jg vapor_3_2_fail
	draw_rectangle vapor_3_x, vapor_3_y_2, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_3_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_3_3_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_3_x
	jl vapor_3_3_fail
	sub eax, square_size_n
	cmp eax, vapor_3_x
	jg vapor_3_3_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_3_y_3
	jl vapor_3_3_fail
	sub eax, square_size_m
	cmp eax, vapor_3_y_3
	jg vapor_3_3_fail
	draw_rectangle vapor_3_x, vapor_3_y_3, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_3_3_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_3_4_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_3_x
	jl vapor_3_4_fail
	sub eax, square_size_n
	cmp eax, vapor_3_x
	jg vapor_3_4_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_3_y_4
	jl vapor_3_4_fail
	sub eax, square_size_m
	cmp eax, vapor_3_y_4
	jg vapor_3_4_fail
	draw_rectangle vapor_3_x, vapor_3_y_4, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_3_4_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_4_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_4_x_1
	jl vapor_4_1_fail
	sub eax, square_size_n
	cmp eax, vapor_4_x_1
	jg vapor_4_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_4_y
	jl vapor_4_1_fail
	sub eax, square_size_m
	cmp eax, vapor_4_y
	jg vapor_4_1_fail
	draw_rectangle vapor_4_x_1, vapor_4_y, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_4_1_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_4_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_4_x_2
	jl vapor_4_2_fail
	sub eax, square_size_n
	cmp eax, vapor_4_x_2
	jg vapor_4_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_4_y
	jl vapor_4_2_fail
	sub eax, square_size_m
	cmp eax, vapor_4_y
	jg vapor_4_2_fail
	draw_rectangle vapor_4_x_2, vapor_4_y, square_size_m, square_size_n, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_4_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_5_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_5_x_1
	jl vapor_5_1_fail
	sub eax, square_size_n
	cmp eax, vapor_5_x_1
	jg vapor_5_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_5_y
	jl vapor_5_1_fail
	sub eax, square_size_m
	cmp eax, vapor_5_y
	jg vapor_5_1_fail
	draw_rectangle vapor_5_x_1, vapor_5_y, square_size_m, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_5_1_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0

vapor_5_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_5_x_2
	jl vapor_5_2_fail
	sub eax, square_size_n
	cmp eax, vapor_5_x_2
	jg vapor_5_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_5_y
	jl vapor_5_2_fail
	sub eax, square_size_m
	cmp eax, vapor_5_y
	jg vapor_5_2_fail
	draw_rectangle vapor_5_x_2, vapor_5_y, square_size_m, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_5_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_5_3_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_5_x_3
	jl vapor_5_3_fail
	sub eax, square_size_n
	cmp eax, vapor_5_x_3
	jg vapor_5_3_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_5_y
	jl vapor_5_3_fail
	sub eax, square_size_m
	cmp eax, vapor_5_y
	jg vapor_5_3_fail
	draw_rectangle vapor_5_x_3, vapor_5_y, square_size_m, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_5_3_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_6_1_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_6_x_1
	jl vapor_6_1_fail
	sub eax, square_size_n
	cmp eax, vapor_6_x_1
	jg vapor_6_1_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_6_y
	jl vapor_6_1_fail
	sub eax, square_size_m
	cmp eax, vapor_6_y
	jg vapor_6_1_fail
	draw_rectangle vapor_6_x_1, vapor_6_y, square_size_n, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_6_1_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_6_2_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_6_x_2
	jl vapor_6_2_fail
	sub eax, square_size_n
	cmp eax, vapor_6_x_2
	jg vapor_6_2_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_6_y
	jl vapor_6_2_fail
	sub eax, square_size_m
	cmp eax, vapor_6_y
	jg vapor_6_2_fail
	draw_rectangle vapor_6_x_2, vapor_6_y, square_size_n, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_6_2_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_6_3_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_6_x_3
	jl vapor_6_3_fail
	sub eax, square_size_n
	cmp eax, vapor_6_x_3
	jg vapor_6_3_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_6_y
	jl vapor_6_3_fail
	sub eax, square_size_m
	cmp eax, vapor_6_y
	jg vapor_6_3_fail
	draw_rectangle vapor_6_x_3, vapor_6_y, square_size_n, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_6_3_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
vapor_6_4_click:
	mov eax, [ebp+arg2]
	cmp eax, vapor_6_x_4
	jl vapor_6_4_fail
	sub eax, square_size_n
	cmp eax, vapor_6_x_4
	jg vapor_6_4_fail
	mov eax, [ebp+arg3]
	cmp eax, vapor_6_y
	jl vapor_6_4_fail
	sub eax, square_size_m
	cmp eax, vapor_6_y
	jg vapor_6_4_fail
	draw_rectangle vapor_6_x_4, vapor_6_y, square_size_n, square_size_m, 325AB3h
	modify ok, 1
	inc descoperite
	dec nedescoperite

vapor_6_4_fail:
	;draw_rectangle [ebp+arg2], [ebp+arg3], 40, 40, 481409h
	mov counterOk, 0
	
cmp ok, 1
je evt_timer
identificare [ebp+arg2], [ebp+arg3]
	
evt_timer:
	mov esi, total
	cmp descoperite, esi
	jne afisare_litere
	inc counterReset
	cmp counterReset, 20
	je reset
	
	
afisare_litere:
	; aici se verifica daca s-au descoperit toate vaporasele, iar in caz afirmativ,
	; se afiseaza mesajul de WIN si se reseteaza tabla dupa 3 secunde.
	
	mov esi, total
	cmp descoperite, esi
	jne continuare
	draw_rectangle 100, 170, 160, 240, 0
	
	make_text_macro 'W', area, 210, 210
	make_text_macro 'I', area, 220, 210
	make_text_macro 'N', area, 230, 210

	make_text_macro 'A', area, 120, 240
	make_text_macro 'S', area, 130, 240
	make_text_macro 'T', area, 140, 240
	make_text_macro 'E', area, 150, 240
	make_text_macro 'P', area, 160, 240
	make_text_macro 'T', area, 170, 240
	make_text_macro 'A', area, 180, 240
	make_text_macro 'T', area, 190, 240
	make_text_macro 'I', area, 200, 240
	make_text_macro ' ', area, 210, 240
	make_text_macro '3', area, 220, 240
	make_text_macro ' ', area, 230, 240
	make_text_macro 'S', area, 240, 240
	make_text_macro 'E', area, 250, 240
	make_text_macro 'C', area, 260, 240
	make_text_macro 'U', area, 270, 240
	make_text_macro 'N', area, 280, 240
	make_text_macro 'D', area, 290, 240
	make_text_macro 'E', area, 300, 240
	
	make_text_macro 'P', area, 160, 260
	make_text_macro 'E', area, 170, 260
	make_text_macro 'N', area, 180, 260
	make_text_macro 'T', area, 190, 260
	make_text_macro 'R', area, 200, 260
	make_text_macro 'U', area, 210, 260
	make_text_macro ' ', area, 220, 260
	make_text_macro 'R', area, 230, 260
	make_text_macro 'E', area, 240, 260
	make_text_macro 'S', area, 250, 260
	make_text_macro 'E', area, 260, 260
	make_text_macro 'T', area, 270, 260
	
continuare:
	mov ebx, 10
	mov eax, descoperite
	;cifra unitatilor initial la 30, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 505, 56
	;cifra zecilor initial la 20, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 495, 56
	;cifra sutelor initial la 10, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 485, 56
	
	;afisam valoarea counter-ului curent (sute, zeci si unitati)
	mov ebx, 10
	mov eax, ratari
	;cifra unitatilor initial la 30, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 505, 76
	;cifra zecilor initial la 20, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 495, 76
	;cifra sutelor initial la 10, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 485, 76
	
	;afisam valoarea counter-ului curent (sute, zeci si unitati)
	mov ebx, 10
	mov eax, nedescoperite
	;cifra unitatilor initial la 30, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 505, 96
	;cifra zecilor initial la 20, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 495, 96
	;cifra sutelor initial la 10, 10
	mov edx, 0
	div ebx
	add edx, '0'
	make_text_macro edx, area, 485, 96
	
	

	;scriem un mesaj
	
	make_text_macro 'V', area, 280, 20
	make_text_macro 'A', area, 290, 20
	make_text_macro 'P', area, 300, 20
	make_text_macro 'O', area, 310, 20
	make_text_macro 'R', area, 320, 20
	make_text_macro 'A', area, 330, 20
	make_text_macro 'S', area, 340, 20
	make_text_macro 'E', area, 350, 20
	make_text_macro 'Z', area, 360, 15
	
	make_text_macro 'H', area, 435, 56
	make_text_macro 'I', area, 445, 56
	make_text_macro 'T', area, 455, 56
	make_text_macro ' ', area, 475, 56
	
	make_text_macro 'M', area, 435, 76
	make_text_macro 'I', area, 445, 76
	make_text_macro 'S', area, 455, 76
	make_text_macro 'S', area, 465, 76
	make_text_macro ' ', area, 475, 76
	
	make_text_macro 'L', area, 435, 96
	make_text_macro 'E', area, 445, 96
	make_text_macro 'F', area, 455, 96
	make_text_macro 'T', area, 465, 96
	make_text_macro ' ', area, 475, 96
	
	make_text_macro 'V', area, 435, 160
	make_text_macro 'A', area, 445, 160
	make_text_macro 'P', area, 455, 160
	make_text_macro 'O', area, 465, 160
	make_text_macro 'R', area, 475, 160
	make_text_macro 'A', area, 485, 160
	make_text_macro 'S', area, 495, 160
	make_text_macro 'E', area, 505, 160
	make_text_macro ' ', area, 515, 160
	make_text_macro 'D', area, 525, 160
	make_text_macro 'I', area, 535, 160
	make_text_macro 'S', area, 545, 160
	make_text_macro 'P', area, 555, 160
	make_text_macro 'O', area, 565, 160
	make_text_macro 'N', area, 575, 160
	make_text_macro 'I', area, 585, 160
	make_text_macro 'B', area, 595, 160
	make_text_macro 'I', area, 605, 160
	make_text_macro 'L', area, 615, 160
	make_text_macro 'E', area, 625, 160
	make_text_macro 'X', area, 635, 160
	
	; desenare vaporase disponibile
	
	draw_rectangle 435, 196, 40, 40, 426122h
	draw_rectangle 478, 196, 40, 40, 426122h
	draw_rectangle 435, 256, 40, 40, 426122h
	draw_rectangle 478, 256, 40, 40, 426122h
	draw_rectangle 521, 256, 40, 40, 426122h
	draw_rectangle 435, 316, 40, 40, 426122h
	draw_rectangle 478, 316, 40, 40, 426122h
	draw_rectangle 521, 316, 40, 40, 426122h
	draw_rectangle 564, 316, 40, 40, 426122h
	
final_draw:
	popa
	mov esp, ebp
	pop ebp
	ret
draw endp

start:
	push offset mesaj
	call printf
	push offset n
	push offset m
	push offset format
	call scanf
	
	mov eax, m
	mov ebx, n
	
	cmp eax, 8
	jne continue

; daca tabla este de 8 pe 8 se modifica pozitiile vaporaselor, astfel incat sa corespuna fiecare coordonata
; acest lucru se face folosind macro-ul modify care modifica valoarea fiecarei coodronate
; altfel, ramane initializarea pentru 10 pe 10
; astfel se pot defini coordonate pentru initializarea oricarei dimensiuni

initialize_8:
	
	modify vapor_1_x_2, 70
	modify vapor_1_x_3, 120

	modify vapor_2_x, 220
	modify vapor_2_y_2, 100
	modify vapor_2_y_3, 150
	modify vapor_2_y_4, 200

	modify vapor_3_x, 370
	modify vapor_3_y_1, 150
	modify vapor_3_y_2, 200
	modify vapor_3_y_3, 250
	modify vapor_3_y_4, 300

	modify vapor_4_x_2, 70
	modify vapor_4_y, 200

	modify vapor_5_x_1, 120
	modify vapor_5_x_2, 170
	modify vapor_5_x_3, 220
	modify vapor_5_y, 300

	modify vapor_6_x_1, 120
	modify vapor_6_x_2, 170
	modify vapor_6_x_3, 220
	modify vapor_6_x_4, 270
	modify vapor_6_y, 400
		
continue:
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov matrice, eax
	;alocam memorie pentru zona de desenat
	mov eax, area_width
	mov ebx, area_height
	mul ebx
	shl eax, 2
	push eax
	call malloc
	add esp, 4
	mov area, eax
	
	;apelam functia de desenare a ferestrei
	; typedef void (*DrawFunc)(int evt, int x, int y);
	; void __cdecl BeginDrawing(const char *title, int width, int height, unsigned int *area, DrawFunc draw);
	
	push offset draw
	push area
	push area_height
	push area_width
	push offset window_title
	call BeginDrawing
	add esp, 20

	;terminarea programului
	push 0
	call exit
end start
