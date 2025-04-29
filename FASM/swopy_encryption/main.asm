format ELF64 executable
entry main

SYS_read	equ 0
SYS_write	equ 1
SYS_open	equ 2
SYS_close	equ 3
SYS_exit	equ 60

O_RDONLY	equ 0
O_WRONLY	equ 1
O_RDWR		equ 2
O_CREAT		equ 64
O_TRUNC		equ 512
O_APPEND	equ 1024

macro exit error_code {
	mov rax, SYS_exit
	mov rdi, error_code
	syscall
}

macro read fd, buf, count {
	mov rax, SYS_read
	mov rdi, fd
	mov rsi, buf
	mov rdx, count
	syscall
	test rax, rax
	js .error_read
}

macro write fd, buf, count {
	mov rax, SYS_write
	mov rdi, fd
	mov rsi, buf
	mov rdx, count
	syscall
	test rax, rax
	js .error_write
}

macro open filename, flags{
	mov rax, SYS_open
	mov rdi, filename
	mov rsi, flags
	mov rdx, 0644o
	syscall
	test rax, rax
	js .error_open
}

macro close fd {
	mov rax, SYS_close
	mov rdi, fd
	syscall
}

BUF_SIZE = 16384
FILENAME_SIZE = 256

segment readable executable
main:
	write 1, file_dialoge_msg, file_dialoge_len
	read 0, filename, FILENAME_SIZE
	mov byte [filename + rax - 1], 0
	open filename, O_RDONLY
	mov [fd], rax
	read [fd], buf, BUF_SIZE
	mov [bytes_read], rax
	mov r8, buf
	mov r9, BUF_SIZE
.loop:
	mov al, byte [r8]
	call swopy
	mov byte [r8], al
	inc r8
	dec r9
	jz .exit
	jmp .loop
.exit:
	close fd
	open filename, O_WRONLY or O_TRUNC
	mov [fd], rax
	write [fd], buf, [bytes_read]
	write 1, file_content_msg, file_content_len
	write 1, new_line, 1
	write 1, buf, [bytes_read]
	write 1, new_line, 2
	close fd
	write 1, done_msg, done_len
	exit 0
.error_open:
	write 2, error_open_msg, error_open_len
	jmp .exit_on_error
.error_write:
	write 2, error_write_msg, error_write_len
	jmp .exit_on_error
.error_read:
	write 2, error_read_msg, error_read_len
	jmp .exit_on_error
.exit_on_error:
	close fd
	exit 1

swopy:
	mov bl, al
	and al, 01010101b
	and bl, 10101010b
	shl al, 1
	shr bl, 1
	or  al, bl
	ret
segment readable writeable
filename:			rb FILENAME_SIZE
fd:					rq 1
buf:				rb BUF_SIZE
bytes_read			rq 1
error_open_msg:		db "ERROR : couldn't open", 10
error_open_len		=  $ - error_open_msg
error_write_msg:	db "ERROR : couldn't write", 10
error_write_len		=  $ - error_write_msg
error_read_msg:		db "ERROR : couldn't read", 10
error_read_len		=  $ - error_read_msg
file_dialoge_msg:	db "filename : "
file_dialoge_len	=  $ - file_dialoge_msg
done_msg:			db "Done!", 10
done_len			=  $ - done_msg
file_content_msg:	db "File contents :", 10
file_content_len	=  $ - file_content_msg
new_line:			db 10, 10
