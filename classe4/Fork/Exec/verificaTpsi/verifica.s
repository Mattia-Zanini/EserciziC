	.file	"verifica.c"
	.text
	.section	.rodata
.LC0:
	.string	"Numero argomenti sbagliato"
.LC2:
	.string	"cat"
.LC3:
	.string	"/bin/cat"
.LC4:
	.string	"{print $3}"
.LC5:
	.string	"awk"
.LC6:
	.string	"/usr/bin/awk"
	.align 8
.LC7:
	.string	"ricevuto importo dalla pipe p2p0: %s"
	.align 8
.LC8:
	.string	"\nIl totale delle fatture \303\250: %.2lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movl	%edi, -164(%rbp)
	movq	%rsi, -176(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$2, -164(%rbp)
	je	.L2
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -144(%rbp)
	leaq	-132(%rbp), %rax
	movq	%rax, %rdi
	call	pipe@PLT
	call	fork@PLT
	movl	%eax, -156(%rbp)
	cmpl	$0, -156(%rbp)
	jne	.L3
	movl	$1, %edi
	call	close@PLT
	movl	-128(%rbp), %eax
	movl	%eax, %edi
	call	dup@PLT
	movl	-128(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-132(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movq	-176(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %ecx
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	execl@PLT
	movl	$-1, %eax
	jmp	.L8
.L3:
	leaq	-124(%rbp), %rax
	movq	%rax, %rdi
	call	pipe@PLT
	call	fork@PLT
	movl	%eax, -156(%rbp)
	cmpl	$0, -156(%rbp)
	jne	.L5
	movl	$0, %edi
	call	close@PLT
	movl	-132(%rbp), %eax
	movl	%eax, %edi
	call	dup@PLT
	movl	-128(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-132(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$1, %edi
	call	close@PLT
	movl	-120(%rbp), %eax
	movl	%eax, %edi
	call	dup@PLT
	movl	-120(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-124(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %ecx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC5(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	execl@PLT
	movl	$-1, %eax
	jmp	.L8
.L5:
	movl	-128(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-132(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-120(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	jmp	.L6
.L7:
	leaq	-113(%rbp), %rcx
	leaq	-112(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncat@PLT
	movzbl	-113(%rbp), %eax
	cmpb	$10, %al
	jne	.L6
	leaq	-112(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-152(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strtod@PLT
	movsd	-144(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -144(%rbp)
	movb	$0, -112(%rbp)
.L6:
	movl	-124(%rbp), %eax
	leaq	-113(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	testq	%rax, %rax
	jg	.L7
	movl	-124(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movq	-144(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
.L8:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
