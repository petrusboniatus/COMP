	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC3:
	.string	"resultado= %e\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	eax, 0
	lea	rdx, res[rip]
	movsd	xmm1, QWORD PTR .LC0[rip]
.L2:
	pxor	xmm0, xmm0
	cvtsi2sd	xmm0, eax
	mulsd	xmm0, xmm1
	movsd	QWORD PTR [rdx+rax*8], xmm0
	add	rax, 1
	cmp	rax, 10000
	jne	.L2
	lea	rax, res[rip]
	lea	rcx, res[rip+80000]
	movsd	xmm3, QWORD PTR .LC1[rip]
	movsd	xmm5, QWORD PTR .LC2[rip]
	movsd	xmm4, QWORD PTR .LC0[rip]
	jmp	.L6
.L10:
	movapd	xmm0, xmm2
	subsd	xmm0, xmm5
.L5:
	addsd	xmm0, xmm2
	movsd	QWORD PTR [rdx], xmm0
	add	rax, 8
	cmp	rax, rcx
	je	.L12
.L6:
	mov	rdx, rax
	movsd	xmm2, QWORD PTR [rax]
	ucomisd	xmm3, xmm2
	jbe	.L10
	movapd	xmm1, xmm2
	mulsd	xmm1, xmm2
	addsd	xmm1, xmm4
	movapd	xmm0, xmm1
	jmp	.L5
.L12:
	movsd	xmm0, QWORD PTR res[rip+79992]
	lea	rdi, .LC3[rip]
	mov	eax, 1
	call	printf@PLT
	mov	eax, 0
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.comm	res,80000,32
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	3539053052
	.long	1061184077
	.align 8
.LC1:
	.long	0
	.long	1097011920
	.align 8
.LC2:
	.long	0
	.long	1083129856
	.ident	"GCC: (Debian 6.3.0-18) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
