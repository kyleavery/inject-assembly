GLOBAL	GetIp
GLOBAL	Leave
GLOBAL	Table

[SEGMENT .text$C]

Table:
	dq	0
	dq	0
	dq	0

[SEGMENT .text$F]

GetIp:
	call	get_ret_ptr

	get_ret_ptr:
	pop	rax
	sub	rax, 5
	ret


Leave:
	db 'E', 'N', 'D', 'O', 'F', 'C', 'O', 'D', 'E'