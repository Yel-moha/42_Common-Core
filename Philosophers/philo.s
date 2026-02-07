	.text
	.file	"philo.c"
	.globl	routine                         # -- Begin function routine
	.p2align	4, 0x90
	.type	routine,@function
routine:                                # @routine
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -12(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$10000, -12(%rbp)               # imm = 0x2710
	jge	.LBB0_4
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movabsq	$mutex, %rdi
	callq	pthread_mutex_lock
	movl	mails, %eax
	addl	$1, %eax
	movl	%eax, mails
	movabsq	$mutex, %rdi
	callq	pthread_mutex_unlock
# %bb.3:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	routine, .Lfunc_end0-routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rdi
	callq	atoi
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
                                        # kill: def $rax killed $eax
	movq	%rsp, %rcx
	movq	%rcx, -32(%rbp)
	leaq	15(,%rax,8), %rdx
	andq	$-16, %rdx
	movq	%rsp, %rcx
	subq	%rdx, %rcx
	movq	%rcx, -56(%rbp)                 # 8-byte Spill
	movq	%rcx, %rsp
	movq	%rax, -40(%rbp)
	movabsq	$mutex, %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_mutex_init
	movl	$0, -44(%rbp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	-44(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	.LBB1_6
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movq	-56(%rbp), %rdi                 # 8-byte Reload
	movslq	-44(%rbp), %rax
	shlq	$3, %rax
	addq	%rax, %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	movabsq	$routine, %rdx
	movq	%rcx, %rsi
	callq	pthread_create
	cmpl	$0, %eax
	je	.LBB1_4
# %bb.3:
	movabsq	$.L.str, %rdi
	callq	perror
	movl	$1, -4(%rbp)
	movl	$1, -48(%rbp)
	jmp	.LBB1_13
.LBB1_4:                                #   in Loop: Header=BB1_1 Depth=1
	movl	-44(%rbp), %esi
	movabsq	$.L.str.1, %rdi
	movb	$0, %al
	callq	printf
# %bb.5:                                #   in Loop: Header=BB1_1 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	.LBB1_1
.LBB1_6:
	movl	$0, -44(%rbp)
.LBB1_7:                                # =>This Inner Loop Header: Depth=1
	movl	-44(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	.LBB1_12
# %bb.8:                                #   in Loop: Header=BB1_7 Depth=1
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movslq	-44(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	cmpl	$0, %eax
	je	.LBB1_10
# %bb.9:
	movl	$2, -4(%rbp)
	movl	$1, -48(%rbp)
	jmp	.LBB1_13
.LBB1_10:                               #   in Loop: Header=BB1_7 Depth=1
	movl	-44(%rbp), %esi
	movabsq	$.L.str.2, %rdi
	movb	$0, %al
	callq	printf
# %bb.11:                               #   in Loop: Header=BB1_7 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	.LBB1_7
.LBB1_12:
	movabsq	$mutex, %rdi
	callq	pthread_mutex_destroy
	movl	mails, %esi
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf
	movl	$0, -4(%rbp)
	movl	$1, -48(%rbp)
.LBB1_13:
	movq	-32(%rbp), %rax
	movq	%rax, %rsp
	movl	-4(%rbp), %eax
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	mails,@object                   # @mails
	.bss
	.globl	mails
	.p2align	2
mails:
	.long	0                               # 0x0
	.size	mails, 4

	.type	mutex,@object                   # @mutex
	.globl	mutex
	.p2align	3
mutex:
	.zero	40
	.size	mutex, 40

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Failed create thread\n"
	.size	.L.str, 22

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"Thread %d is started: \n"
	.size	.L.str.1, 24

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"Thread %d has finished execution\n"
	.size	.L.str.2, 34

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"il numero di mail e' %d\n"
	.size	.L.str.3, 25

	.ident	"Ubuntu clang version 12.0.1-19ubuntu3"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym routine
	.addrsig_sym pthread_mutex_lock
	.addrsig_sym pthread_mutex_unlock
	.addrsig_sym atoi
	.addrsig_sym pthread_mutex_init
	.addrsig_sym pthread_create
	.addrsig_sym perror
	.addrsig_sym printf
	.addrsig_sym pthread_join
	.addrsig_sym pthread_mutex_destroy
	.addrsig_sym mails
	.addrsig_sym mutex
