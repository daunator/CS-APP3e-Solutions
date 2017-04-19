.section .text
.globl store_prod

store_prod:
	movq	%rdx, %rax    # y_l -> %rax
	cqto                # y_h -> %rdx
	movq	%rsi, %rcx    # x -> %rcx
	sarq	$63, %rcx     # x_h -> %rcx
	imulq	%rax, %rcx    # y_l * x_h -> %rcx
	imulq	%rsi, %rdx    # x_l * y_h -> %rdx
	addq	%rdx, %rcx    # x_l*y_h + y_l*x_h -> %rcx
	mulq	%rsi          # x_l * y_l -> %rdx:%rax
	addq	%rcx, %rdx    # (x_l*y_h + y_l*x_h)*2^64 + x_l*y_l -> %rdx:%rax
	movq	%rax, (%rdi)
	movq	%rdx, 8(%rdi)
	ret

