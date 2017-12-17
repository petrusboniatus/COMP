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
	movsd	xmm0, QWORD PTR .LC0[rip]
.L2:
	pxor	xmm1, xmm1
	cvtsi2sd	xmm1, eax
	mulsd	xmm1, xmm0
	movsd	QWORD PTR [rdx+rax*8], xmm1
	add	rax, 1
	pxor	xmm2, xmm2
	cvtsi2sd	xmm2, eax
	mulsd	xmm2, xmm0
	movsd	QWORD PTR [rdx+rax*8], xmm2
	lea	rsi, 1[rax]
	pxor	xmm3, xmm3
	cvtsi2sd	xmm3, esi
	mulsd	xmm3, xmm0
	movsd	QWORD PTR [rdx+rsi*8], xmm3
	lea	rdi, 2[rax]
	pxor	xmm4, xmm4
	cvtsi2sd	xmm4, edi
	mulsd	xmm4, xmm0
	movsd	QWORD PTR [rdx+rdi*8], xmm4
	lea	r8, 3[rax]
	pxor	xmm5, xmm5
	cvtsi2sd	xmm5, r8d
	mulsd	xmm5, xmm0
	movsd	QWORD PTR [rdx+r8*8], xmm5
	lea	r9, 4[rax]
	pxor	xmm6, xmm6
	cvtsi2sd	xmm6, r9d
	mulsd	xmm6, xmm0
	movsd	QWORD PTR [rdx+r9*8], xmm6
	lea	r10, 5[rax]
	pxor	xmm7, xmm7
	cvtsi2sd	xmm7, r10d
	mulsd	xmm7, xmm0
	movsd	QWORD PTR [rdx+r10*8], xmm7
	lea	r11, 6[rax]
	pxor	xmm8, xmm8
	cvtsi2sd	xmm8, r11d
	mulsd	xmm8, xmm0
	movsd	QWORD PTR [rdx+r11*8], xmm8
	add	rax, 7
	cmp	rax, 10000
	jne	.L2
	lea	rdx, res[rip]
	lea	rcx, res[rip+80000]
	movsd	xmm9, QWORD PTR .LC1[rip]
	movsd	xmm10, QWORD PTR .LC2[rip]
	movsd	xmm11, QWORD PTR .LC0[rip]
	jmp	.L6
.L31:
	movapd	xmm13, xmm12
	subsd	xmm13, xmm10
	jmp	.L5
.L42:
	movsd	xmm0, QWORD PTR res[rip+79992]
	lea	rdi, .LC3[rip]
	mov	eax, 1
	call	printf@PLT
	mov	eax, 0
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L10:
	.cfi_restore_state
	movapd	xmm15, xmm14
	mulsd	xmm15, xmm14
	addsd	xmm15, xmm11
	jmp	.L33
.L12:
	movapd	xmm1, xmm0
	mulsd	xmm1, xmm0
	addsd	xmm1, xmm11
	jmp	.L34
.L14:
	movapd	xmm3, xmm2
	mulsd	xmm3, xmm2
	addsd	xmm3, xmm11
	jmp	.L35
.L16:
	movapd	xmm5, xmm4
	mulsd	xmm5, xmm4
	addsd	xmm5, xmm11
	jmp	.L36
.L18:
	movapd	xmm7, xmm6
	mulsd	xmm7, xmm6
	addsd	xmm7, xmm11
	jmp	.L37
.L20:
	movapd	xmm12, xmm8
	mulsd	xmm12, xmm8
	addsd	xmm12, xmm11
	jmp	.L38
.L22:
	movapd	xmm14, xmm13
	mulsd	xmm14, xmm13
	addsd	xmm14, xmm11
.L39:
	addsd	xmm14, xmm13
	movsd	QWORD PTR 48[rsi], xmm14
	lea	rdx, 56[rsi]
	cmp	rdx, rcx
	je	.L42
.L6:
	mov	rax, rdx
	movsd	xmm12, QWORD PTR [rdx]
	ucomisd	xmm9, xmm12
	jbe	.L31
	movapd	xmm13, xmm12
	mulsd	xmm13, xmm12
	addsd	xmm13, xmm11
.L5:
	addsd	xmm13, xmm12
	movsd	QWORD PTR [rax], xmm13
	lea	rsi, 8[rdx]
	movsd	xmm14, QWORD PTR 8[rdx]
	ucomisd	xmm9, xmm14
	ja	.L10
	movapd	xmm15, xmm14
	subsd	xmm15, xmm10
.L33:
	addsd	xmm15, xmm14
	movsd	QWORD PTR [rsi], xmm15
	movsd	xmm0, QWORD PTR 8[rsi]
	ucomisd	xmm9, xmm0
	ja	.L12
	movapd	xmm1, xmm0
	subsd	xmm1, xmm10
.L34:
	addsd	xmm1, xmm0
	movsd	QWORD PTR 8[rsi], xmm1
	movsd	xmm2, QWORD PTR 16[rsi]
	ucomisd	xmm9, xmm2
	ja	.L14
	movapd	xmm3, xmm2
	subsd	xmm3, xmm10
.L35:
	addsd	xmm3, xmm2
	movsd	QWORD PTR 16[rsi], xmm3
	movsd	xmm4, QWORD PTR 24[rsi]
	ucomisd	xmm9, xmm4
	ja	.L16
	movapd	xmm5, xmm4
	subsd	xmm5, xmm10
.L36:
	addsd	xmm5, xmm4
	movsd	QWORD PTR 24[rsi], xmm5
	movsd	xmm6, QWORD PTR 32[rsi]
	ucomisd	xmm9, xmm6
	ja	.L18
	movapd	xmm7, xmm6
	subsd	xmm7, xmm10
.L37:
	addsd	xmm7, xmm6
	movsd	QWORD PTR 32[rsi], xmm7
	movsd	xmm8, QWORD PTR 40[rsi]
	ucomisd	xmm9, xmm8
	ja	.L20
	movapd	xmm12, xmm8
	subsd	xmm12, xmm10
.L38:
	addsd	xmm12, xmm8
	movsd	QWORD PTR 40[rsi], xmm12
	movsd	xmm13, QWORD PTR 48[rsi]
	ucomisd	xmm9, xmm13
	ja	.L22
	movapd	xmm14, xmm13
	subsd	xmm14, xmm10
	jmp	.L39
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
