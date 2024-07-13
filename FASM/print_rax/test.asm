format ELF64 executable

SYS_write = 1
SYS_exit = 60

STDOUT = 1
INT2ASCII = 48

macro write fd, buf, count
{
	mov rax, SYS_write
	mov rdi, fd
	mov rsi, buf
	mov rdx, count
	syscall
}

macro exit code
{
	mov rax, SYS_exit
	mov rdi, code
	syscall
}

segment readable executable
entry main
main:
	mov rbx, x
	mov rax, 42
	mov rcx, 10
	mov r8, 0
loop1:
	;; get each digit and push it to the stack
	div rcx
	add rdx, INT2ASCII
	push rdx
	mov rdx, 0
	mov rcx, 10
	inc r8 ;; get count of digits

	cmp rax, 0
	jnz loop1

	;; set r9 to count of digits + 1 for \n
	mov r9, r8
	inc r9
	
loop2:
	;; pop and mov digits to x
	pop rax
	mov [rbx], rax
	inc rbx

	dec r8
	cmp r8, 0
	jnz loop2

	mov word [rbx], 10 ;; add \n

	write STDOUT, x, r9
	exit 0

segment readable writeable
	x dw 0
