	.file	"rfsb.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"%.2X"
	.text
	.p2align 4,,15
	.type	crypto_hashblocks.constprop.0, @function
crypto_hashblocks.constprop.0:
.LFB507:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%edx, %ebp
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$2140, %esp
	.cfi_def_cfa_offset 2160
	movl	%eax, 104(%esp)
	movdqu	(%eax), %xmm0
	movdqu	16(%eax), %xmm1
	movdqa	%xmm1, 2080(%esp)
	movl	2080(%esp), %eax
	movdqa	%xmm0, 2064(%esp)
	movl	2084(%esp), %edx
	movl	2064(%esp), %ecx
	movl	2068(%esp), %ebx
	movl	%eax, 24(%esp)
	movl	104(%esp), %eax
	movl	%edx, 28(%esp)
	movl	%ecx, %esi
	movl	24(%esp), %ecx
	movl	%ebx, %edi
	movl	28(%esp), %ebx
	movdqu	32(%eax), %xmm0
	movdqa	%xmm0, 2096(%esp)
	movl	2096(%esp), %eax
	movl	2100(%esp), %edx
	movl	%eax, 32(%esp)
	movl	104(%esp), %eax
	movl	%edx, 36(%esp)
	movdqu	48(%eax), %xmm0
	movdqa	%xmm0, 2112(%esp)
	movl	2112(%esp), %eax
	movl	2116(%esp), %edx
	movl	%eax, 40(%esp)
	movl	0(%ebp), %eax
	movl	%edx, 44(%esp)
	movl	4(%ebp), %edx
	movl	%eax, 48(%esp)
	movl	8(%ebp), %eax
	movl	%edx, 52(%esp)
	movl	12(%ebp), %edx
	movl	%eax, 56(%esp)
	movl	16(%ebp), %eax
	movl	%edx, 60(%esp)
	movl	20(%ebp), %edx
	movl	%eax, 64(%esp)
	movl	24(%ebp), %eax
	movl	%edx, 68(%esp)
	movl	28(%ebp), %edx
	movl	%eax, 72(%esp)
	movl	32(%ebp), %eax
	movl	%edx, 76(%esp)
	movl	36(%ebp), %edx
	movl	%eax, 80(%esp)
	movl	40(%ebp), %eax
	movl	%edx, 84(%esp)
	movl	44(%ebp), %edx
	movl	%eax, 88(%esp)
	movl	%esi, %eax
	movl	%edx, 92(%esp)
	movl	%esi, %edx
	movb	%dl, 1952(%esp)
	movl	%edi, %edx
	shrdl	$8, %edx, %eax
	shrl	$8, %edx
	movl	%eax, 24(%esp)
	movl	%edx, 28(%esp)
	movzbl	24(%esp), %edx
	movb	%al, 110(%esp)
	movl	%esi, %eax
	movb	%dl, 1953(%esp)
	movl	%edi, %edx
	shrdl	$16, %edx, %eax
	shrl	$16, %edx
	movl	%eax, 96(%esp)
	movl	%edx, 100(%esp)
	movzbl	96(%esp), %edx
	movb	%al, 111(%esp)
	movl	%esi, %eax
	movb	%dl, 1954(%esp)
	movl	%edi, %edx
	shrdl	$24, %edx, %eax
	movb	%al, 1955(%esp)
	movl	%edi, %eax
	movb	%al, 1956(%esp)
	shrl	$8, %eax
	movl	2076(%esp), %edx
	movb	%al, 1957(%esp)
	movl	%edi, %eax
	shrl	$16, %eax
	movb	%al, 1958(%esp)
	movl	%edi, %eax
	shrl	$24, %eax
	movb	%al, 1959(%esp)
	movzbl	2072(%esp), %eax
	movb	%cl, 1968(%esp)
	movb	%bl, 1972(%esp)
	movb	%al, 1960(%esp)
	movl	2072(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	2076(%esp), %edx
	movb	%al, 1961(%esp)
	movl	2072(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	2076(%esp), %edx
	movb	%al, 1962(%esp)
	movl	2072(%esp), %eax
	shrdl	$24, %edx, %eax
	movzbl	2088(%esp), %edx
	movb	%al, 1963(%esp)
	movl	2076(%esp), %eax
	movb	%dl, 1976(%esp)
	movl	2092(%esp), %edx
	movb	%al, 1964(%esp)
	shrl	$8, %eax
	movb	%al, 1965(%esp)
	movl	2076(%esp), %eax
	shrl	$16, %eax
	movb	%al, 1966(%esp)
	movl	2076(%esp), %eax
	shrl	$24, %eax
	movb	%al, 1967(%esp)
	movl	%ecx, %eax
	shrdl	$8, %ebx, %eax
	movb	%al, 1969(%esp)
	movl	%ecx, %eax
	shrdl	$16, %ebx, %eax
	movb	%al, 1970(%esp)
	movl	%ecx, %eax
	shrdl	$24, %ebx, %eax
	movb	%al, 1971(%esp)
	movl	%ebx, %eax
	shrl	$8, %eax
	movb	%al, 1973(%esp)
	movl	%ebx, %eax
	shrl	$16, %eax
	movb	%al, 1974(%esp)
	movl	%ebx, %eax
	shrl	$24, %eax
	movb	%al, 1975(%esp)
	movl	2088(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 1977(%esp)
	movl	2092(%esp), %edx
	movl	2088(%esp), %eax
	movzbl	32(%esp), %ecx
	movzbl	2104(%esp), %ebx
	shrdl	$16, %edx, %eax
	movl	2092(%esp), %edx
	movb	%al, 1978(%esp)
	movl	2088(%esp), %eax
	movb	%cl, 1984(%esp)
	movb	%bl, 1992(%esp)
	shrdl	$24, %edx, %eax
	movl	36(%esp), %edx
	movb	%al, 1979(%esp)
	movl	2092(%esp), %eax
	movb	%al, 1980(%esp)
	shrl	$8, %eax
	movb	%al, 1981(%esp)
	movl	2092(%esp), %eax
	shrl	$16, %eax
	movb	%al, 1982(%esp)
	movl	2092(%esp), %eax
	shrl	$24, %eax
	movb	%al, 1983(%esp)
	movl	32(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	36(%esp), %edx
	movb	%al, 1985(%esp)
	movl	32(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	36(%esp), %edx
	movb	%al, 1986(%esp)
	movl	32(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	2108(%esp), %edx
	movb	%al, 1987(%esp)
	movl	36(%esp), %eax
	movb	%al, 1988(%esp)
	shrl	$8, %eax
	movb	%al, 1989(%esp)
	movl	36(%esp), %eax
	shrl	$16, %eax
	movb	%al, 1990(%esp)
	movl	36(%esp), %eax
	shrl	$24, %eax
	movb	%al, 1991(%esp)
	movl	2104(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 1993(%esp)
	movl	2108(%esp), %edx
	movl	2104(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	2108(%esp), %edx
	movb	%al, 1994(%esp)
	movl	2104(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	44(%esp), %edx
	movb	%al, 1995(%esp)
	movl	2108(%esp), %eax
	movb	%al, 1996(%esp)
	shrl	$8, %eax
	movb	%al, 1997(%esp)
	movl	2108(%esp), %eax
	shrl	$16, %eax
	movb	%al, 1998(%esp)
	movl	2108(%esp), %eax
	shrl	$24, %eax
	movb	%al, 1999(%esp)
	movzbl	40(%esp), %eax
	movb	%al, 2000(%esp)
	movl	40(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	44(%esp), %edx
	movb	%al, 2001(%esp)
	movl	40(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	44(%esp), %edx
	movb	%al, 2002(%esp)
	movl	40(%esp), %eax
	shrdl	$24, %edx, %eax
	movzbl	2120(%esp), %edx
	movb	%al, 2003(%esp)
	movl	44(%esp), %eax
	movb	%dl, 2008(%esp)
	movl	2124(%esp), %edx
	movb	%al, 2004(%esp)
	shrl	$8, %eax
	movb	%al, 2005(%esp)
	movl	44(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2006(%esp)
	movl	44(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2007(%esp)
	movl	2120(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 2009(%esp)
	movl	2124(%esp), %edx
	movl	2120(%esp), %eax
	movzbl	48(%esp), %ecx
	movzbl	56(%esp), %ebx
	shrdl	$16, %edx, %eax
	movl	2124(%esp), %edx
	movb	%al, 2010(%esp)
	movl	2120(%esp), %eax
	movb	%cl, 2016(%esp)
	movb	%bl, 2024(%esp)
	shrdl	$24, %edx, %eax
	movl	52(%esp), %edx
	movb	%al, 2011(%esp)
	movl	2124(%esp), %eax
	movb	%al, 2012(%esp)
	shrl	$8, %eax
	movb	%al, 2013(%esp)
	movl	2124(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2014(%esp)
	movl	2124(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2015(%esp)
	movl	48(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	52(%esp), %edx
	movb	%al, 2017(%esp)
	movl	48(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	52(%esp), %edx
	movb	%al, 2018(%esp)
	movl	48(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	60(%esp), %edx
	movb	%al, 2019(%esp)
	movl	52(%esp), %eax
	movb	%al, 2020(%esp)
	shrl	$8, %eax
	movb	%al, 2021(%esp)
	movl	52(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2022(%esp)
	movl	52(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2023(%esp)
	movl	56(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 2025(%esp)
	movl	60(%esp), %edx
	movl	56(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	60(%esp), %edx
	movb	%al, 2026(%esp)
	movl	56(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	68(%esp), %edx
	movb	%al, 2027(%esp)
	movl	60(%esp), %eax
	movb	%al, 2028(%esp)
	shrl	$8, %eax
	movb	%al, 2029(%esp)
	movl	60(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2030(%esp)
	movl	60(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2031(%esp)
	movzbl	64(%esp), %eax
	movb	%al, 2032(%esp)
	movl	64(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	68(%esp), %edx
	movb	%al, 2033(%esp)
	movl	64(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	68(%esp), %edx
	movb	%al, 2034(%esp)
	movl	64(%esp), %eax
	shrdl	$24, %edx, %eax
	movzbl	72(%esp), %edx
	movb	%al, 2035(%esp)
	movl	68(%esp), %eax
	movb	%dl, 2040(%esp)
	movl	76(%esp), %edx
	movb	%al, 2036(%esp)
	shrl	$8, %eax
	movb	%al, 2037(%esp)
	movl	68(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2038(%esp)
	movl	68(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2039(%esp)
	movl	72(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 2041(%esp)
	movl	76(%esp), %edx
	movl	72(%esp), %eax
	movzbl	80(%esp), %ecx
	movzbl	88(%esp), %ebx
	shrdl	$16, %edx, %eax
	movl	76(%esp), %edx
	movb	%al, 2042(%esp)
	movl	72(%esp), %eax
	movb	%cl, 2048(%esp)
	movb	%bl, 2056(%esp)
	shrdl	$24, %edx, %eax
	movl	84(%esp), %edx
	movb	%al, 2043(%esp)
	movl	76(%esp), %eax
	movb	%al, 2044(%esp)
	shrl	$8, %eax
	movb	%al, 2045(%esp)
	movl	76(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2046(%esp)
	movl	76(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2047(%esp)
	movl	80(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	84(%esp), %edx
	movb	%al, 2049(%esp)
	movl	80(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	84(%esp), %edx
	movb	%al, 2050(%esp)
	movl	80(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	92(%esp), %edx
	movb	%al, 2051(%esp)
	movl	84(%esp), %eax
	movb	%al, 2052(%esp)
	shrl	$8, %eax
	movb	%al, 2053(%esp)
	movl	84(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2054(%esp)
	movl	84(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2055(%esp)
	movl	88(%esp), %eax
	shrdl	$8, %edx, %eax
	movb	%al, 2057(%esp)
	movl	92(%esp), %edx
	movl	88(%esp), %eax
	movzbl	111(%esp), %ecx
	movzbl	96(%esp), %ebp
	shrdl	$16, %edx, %eax
	movl	92(%esp), %edx
	movb	%al, 2058(%esp)
	movl	88(%esp), %eax
	sall	$6, %ecx
	shrdl	$24, %edx, %eax
	movl	%esi, %edx
	movb	%al, 2059(%esp)
	movl	92(%esp), %eax
	movb	%al, 2060(%esp)
	shrl	$8, %eax
	movb	%al, 40(%esp)
	movb	%al, 2061(%esp)
	movl	92(%esp), %eax
	shrl	$16, %eax
	movb	%al, 108(%esp)
	movb	%al, 2062(%esp)
	movl	92(%esp), %eax
	shrl	$24, %eax
	movb	%al, 109(%esp)
	movb	%al, 2063(%esp)
	movzbl	%dl, %eax
	movzbl	110(%esp), %edx
	sall	$6, %eax
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+48(%eax), %xmm0
	movdqa	%xmm0, 112(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%eax), %xmm0
	sall	$6, %edx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edx), %xmm0
	movdqa	%xmm0, 128(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%edx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%ecx), %xmm0
	movl	%esi, %ecx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%eax), %xmm0
	movb	%cl, 32(%esp)
	movl	$3, %eax
	movdqa	%xmm0, 144(%esp)
	leal	160(%esp), %ecx
	.p2align 4,,7
	.p2align 3
.L2:
	movzbl	1952(%esp,%eax), %edx
	andl	$255, %ebp
	movzbl	24(%esp), %esi
	sall	$6, %ebp
	movzbl	32(%esp), %ebx
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%ebp), %xmm0
	sall	$6, %edx
	sall	$6, %esi
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edx), %xmm0
	sall	$6, %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ebx), %xmm0
	movzbl	1953(%esp,%eax), %ebx
	movdqa	%xmm0, (%ecx)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%ebp), %xmm0
	movzbl	%bl, %edi
	movb	%bl, 32(%esp)
	movzbl	1954(%esp,%eax), %ebx
	sall	$6, %edi
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+32(%edx), %xmm0
	movdqa	%xmm0, 16(%ecx)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%edi), %xmm0
	movl	%edi, 48(%esp)
	movzbl	%bl, %esi
	sall	$6, %esi
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ebp), %xmm0
	movzbl	1955(%esp,%eax), %ebp
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edx), %xmm0
	movdqa	%xmm0, 32(%ecx)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%esi), %xmm0
	movl	48(%esp), %esi
	addl	$4, %eax
	movb	%bl, 24(%esp)
	movl	%ebp, %ebx
	movzbl	%bl, %edi
	sall	$6, %edi
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edx), %xmm0
	movl	$112, %edx
	movdqa	%xmm0, 48(%ecx)
	addl	$64, %ecx
	subl	%eax, %edx
	cmpl	$111, %eax
	jne	.L2
	leal	2063(%esp), %eax
	xorl	%ecx, %ecx
	sall	$4, %edx
	.p2align 4,,7
	.p2align 3
.L3:
	movzbl	-1(%eax), %esi
	movzbl	(%eax), %ebx
	sall	$6, %esi
	sall	$6, %ebx
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%ebx), %xmm0
	movzbl	-2(%eax), %ebx
	sall	$6, %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%ebx), %xmm0
	movzbl	-3(%eax), %ebx
	addl	$1, %eax
	sall	$6, %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ebx), %xmm0
	movdqa	%xmm0, 1888(%esp,%ecx)
	addl	$16, %ecx
	cmpl	%edx, %ecx
	jne	.L3
	movzbl	108(%esp), %edx
	movl	$111, %ebx
	movdqa	160(%esp), %xmm3
	movzbl	109(%esp), %eax
	movdqa	112(%esp), %xmm2
	movdqa	128(%esp), %xmm1
	movzbl	40(%esp), %ecx
	sall	$6, %edx
	sall	$6, %eax
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edx), %xmm0
	sall	$6, %ecx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ecx), %xmm0
	xorl	%ecx, %ecx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+32(%eax), %xmm0
	movdqa	%xmm0, 1904(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+16(%eax), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edx), %xmm0
	movdqa	%xmm0, 1920(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix(%eax), %xmm0
	leal	176(%esp), %eax
	movdqa	%xmm0, 1936(%esp)
	movdqa	144(%esp), %xmm0
	.p2align 4,,7
	.p2align 3
.L6:
	movdqa	%xmm2, %xmm5
	movdqa	%xmm2, %xmm4
	psrlq	$61, %xmm5
	psllq	$3, %xmm4
	pshufd	$69, %xmm5, %xmm2
	psrldq	$8, %xmm5
	pxor	%xmm2, %xmm4
	movdqa	%xmm1, %xmm2
	psrlq	$61, %xmm2
	pxor	%xmm3, %xmm5
	movdqa	%xmm1, %xmm3
	pshufd	$69, %xmm2, %xmm1
	psllq	$3, %xmm3
	psrldq	$8, %xmm2
	pxor	(%eax), %xmm4
	pxor	%xmm1, %xmm3
	pxor	%xmm2, %xmm4
	movdqa	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	psrlq	$61, %xmm1
	psllq	$3, %xmm2
	pshufd	$69, %xmm1, %xmm0
	psrldq	$8, %xmm1
	pxor	%xmm0, %xmm2
	movdqa	%xmm5, %xmm0
	psrlq	$61, %xmm0
	pxor	16(%eax), %xmm3
	movdqa	%xmm5, -16(%eax)
	pxor	%xmm1, %xmm3
	movdqa	%xmm5, %xmm1
	pshufd	$69, %xmm0, %xmm5
	psllq	$3, %xmm1
	psrldq	$8, %xmm0
	pxor	32(%eax), %xmm2
	pxor	%xmm5, %xmm1
	pxor	%xmm0, %xmm2
	movdqa	%xmm4, %xmm5
	movdqa	%xmm4, %xmm0
	psrlq	$61, %xmm5
	psllq	$3, %xmm0
	movdqa	%xmm4, (%eax)
	pshufd	$69, %xmm5, %xmm4
	psrldq	$8, %xmm5
	pxor	%xmm4, %xmm0
	movdqa	%xmm3, %xmm4
	psrlq	$61, %xmm4
	pxor	48(%eax), %xmm1
	movdqa	%xmm3, 16(%eax)
	pxor	%xmm5, %xmm1
	addl	$6, %ecx
	pshufd	$69, %xmm4, %xmm5
	psllq	$3, %xmm3
	psrldq	$8, %xmm4
	pxor	64(%eax), %xmm0
	movl	%ebx, %edx
	movdqa	%xmm2, 32(%eax)
	movdqa	%xmm1, 48(%eax)
	pxor	%xmm5, %xmm3
	pxor	%xmm4, %xmm0
	pxor	80(%eax), %xmm3
	movdqa	%xmm0, 64(%eax)
	movdqa	%xmm3, 80(%eax)
	subl	%ecx, %edx
	addl	$96, %eax
	cmpl	$108, %ecx
	jne	.L6
	leal	1904(%esp), %eax
	.p2align 4,,7
	.p2align 3
.L7:
	movdqa	-64(%eax), %xmm0
	movdqa	%xmm0, %xmm1
	psrlq	$61, %xmm1
	pshufd	$69, %xmm1, %xmm2
	psllq	$3, %xmm0
	psrldq	$8, %xmm1
	pxor	-16(%eax), %xmm1
	pxor	%xmm2, %xmm0
	movdqa	%xmm1, -16(%eax)
	pxor	(%eax), %xmm0
	movdqa	%xmm0, (%eax)
	addl	$16, %eax
	subl	$1, %edx
	jne	.L7
	movdqa	1888(%esp), %xmm0
	movdqa	%xmm0, %xmm1
	psrlq	$61, %xmm1
	psrldq	$8, %xmm1
	movdqa	1936(%esp), %xmm2
	pand	.LC0, %xmm0
	pxor	%xmm1, %xmm2
	movdqa	%xmm2, 1936(%esp)
	movzbl	1936(%esp), %edx
	movdqa	%xmm0, 1888(%esp)
	movzbl	1888(%esp), %eax
	movl	$63, %ebx
	movb	%dl, 2064(%esp)
	movzbl	1937(%esp), %edx
	movb	%dl, 2065(%esp)
	movzbl	1938(%esp), %edx
	movb	%dl, 2066(%esp)
	movzbl	1939(%esp), %edx
	movb	%dl, 2067(%esp)
	movzbl	1940(%esp), %edx
	movb	%dl, 2068(%esp)
	movzbl	1941(%esp), %edx
	movb	%dl, 2069(%esp)
	movzbl	1942(%esp), %edx
	movb	%dl, 2070(%esp)
	movzbl	1943(%esp), %edx
	movb	%dl, 2071(%esp)
	movzbl	1944(%esp), %edx
	movb	%dl, 2072(%esp)
	movzbl	1945(%esp), %edx
	movb	%dl, 2073(%esp)
	movzbl	1946(%esp), %edx
	movb	%dl, 2074(%esp)
	movzbl	1947(%esp), %edx
	movb	%dl, 2075(%esp)
	movzbl	1948(%esp), %edx
	movb	%dl, 2076(%esp)
	movzbl	1949(%esp), %edx
	movb	%dl, 2077(%esp)
	movzbl	1950(%esp), %edx
	movb	%dl, 2078(%esp)
	movzbl	1951(%esp), %edx
	movb	%dl, 2079(%esp)
	movzbl	1920(%esp), %edx
	movb	%dl, 2080(%esp)
	movzbl	1921(%esp), %edx
	movb	%dl, 2081(%esp)
	movzbl	1922(%esp), %edx
	movb	%dl, 2082(%esp)
	movzbl	1923(%esp), %edx
	movb	%dl, 2083(%esp)
	movzbl	1924(%esp), %edx
	movb	%dl, 2084(%esp)
	movzbl	1925(%esp), %edx
	movb	%dl, 2085(%esp)
	movzbl	1926(%esp), %edx
	movb	%dl, 2086(%esp)
	movzbl	1927(%esp), %edx
	movb	%dl, 2087(%esp)
	movzbl	1928(%esp), %edx
	movb	%dl, 2088(%esp)
	movzbl	1929(%esp), %edx
	movb	%dl, 2089(%esp)
	movzbl	1930(%esp), %edx
	movb	%dl, 2090(%esp)
	movzbl	1931(%esp), %edx
	movb	%dl, 2091(%esp)
	movzbl	1932(%esp), %edx
	movb	%dl, 2092(%esp)
	movzbl	1933(%esp), %edx
	movb	%dl, 2093(%esp)
	movzbl	1934(%esp), %edx
	movb	%dl, 2094(%esp)
	movzbl	1935(%esp), %edx
	movb	%dl, 2095(%esp)
	movzbl	1904(%esp), %edx
	movb	%dl, 2096(%esp)
	movzbl	1905(%esp), %edx
	movb	%dl, 2097(%esp)
	movzbl	1906(%esp), %edx
	movb	%dl, 2098(%esp)
	movzbl	1907(%esp), %edx
	movb	%dl, 2099(%esp)
	movzbl	1908(%esp), %edx
	movb	%dl, 2100(%esp)
	movzbl	1909(%esp), %edx
	movb	%dl, 2101(%esp)
	movzbl	1910(%esp), %edx
	movb	%dl, 2102(%esp)
	movzbl	1911(%esp), %edx
	movb	%dl, 2103(%esp)
	movzbl	1912(%esp), %edx
	movb	%dl, 2104(%esp)
	movzbl	1913(%esp), %edx
	movb	%dl, 2105(%esp)
	movzbl	1914(%esp), %edx
	movb	%dl, 2106(%esp)
	movzbl	1915(%esp), %edx
	movb	%dl, 2107(%esp)
	movzbl	1916(%esp), %edx
	movb	%dl, 2108(%esp)
	movzbl	1917(%esp), %edx
	movb	%dl, 2109(%esp)
	movzbl	1918(%esp), %edx
	movb	%dl, 2110(%esp)
	movzbl	1919(%esp), %edx
	movb	%dl, 2111(%esp)
	movb	%al, 2112(%esp)
	movzbl	1889(%esp), %eax
	movb	%al, 2113(%esp)
	movzbl	1890(%esp), %eax
	movb	%al, 2114(%esp)
	movzbl	1891(%esp), %eax
	movb	%al, 2115(%esp)
	movzbl	1892(%esp), %eax
	movb	%al, 2116(%esp)
	movzbl	1893(%esp), %eax
	movb	%al, 2117(%esp)
	movzbl	1894(%esp), %eax
	movb	%al, 2118(%esp)
	movzbl	1895(%esp), %eax
	movb	%al, 2119(%esp)
	movzbl	1896(%esp), %eax
	movb	%al, 2120(%esp)
	movzbl	1897(%esp), %eax
	movb	%al, 2121(%esp)
	movzbl	1898(%esp), %eax
	movb	%al, 2122(%esp)
	movzbl	1899(%esp), %eax
	movb	%al, 2123(%esp)
	movzbl	1900(%esp), %eax
	movb	%al, 2124(%esp)
	movzbl	1901(%esp), %eax
	movb	%al, 2125(%esp)
	movzbl	1902(%esp), %eax
	movb	%al, 2126(%esp)
	movzbl	1903(%esp), %eax
	movb	%al, 2127(%esp)
	.p2align 4,,7
	.p2align 3
.L8:
	movzbl	2064(%esp,%ebx), %eax
	subl	$1, %ebx
	movl	$.LC1, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	cmpl	$-1, %ebx
	jne	.L8
	movl	$10, (%esp)
	call	putchar
	movl	104(%esp), %eax
	movdqa	2064(%esp), %xmm0
	movdqu	%xmm0, (%eax)
	movdqa	2080(%esp), %xmm0
	movdqu	%xmm0, 16(%eax)
	movdqa	2096(%esp), %xmm0
	movdqu	%xmm0, 32(%eax)
	movdqa	2112(%esp), %xmm0
	movdqu	%xmm0, 48(%eax)
	addl	$2140, %esp
	.cfi_def_cfa_offset 20
	xorl	%eax, %eax
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE507:
	.size	crypto_hashblocks.constprop.0, .-crypto_hashblocks.constprop.0
	.p2align 4,,15
	.globl	crypto_hashblocks
	.type	crypto_hashblocks, @function
crypto_hashblocks:
.LFB505:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$2236, %esp
	.cfi_def_cfa_offset 2256
	movl	2268(%esp), %edx
	movl	2264(%esp), %eax
	movl	%edx, 164(%esp)
	movl	2256(%esp), %edx
	cmpl	$0, 164(%esp)
	movl	%eax, 160(%esp)
	movdqu	(%edx), %xmm0
	movdqa	%xmm0, 2160(%esp)
	movdqu	16(%edx), %xmm0
	movdqa	%xmm0, 2176(%esp)
	movdqu	32(%edx), %xmm0
	movdqa	%xmm0, 2192(%esp)
	movdqu	48(%edx), %xmm0
	movdqa	%xmm0, 2208(%esp)
	ja	.L44
	cmpl	$47, 160(%esp)
	jbe	.L20
.L44:
	leal	1984(%esp), %edx
	movdqa	.LC0, %xmm0
	movdqa	%xmm0, 176(%esp)
	leal	2159(%esp), %ebx
	movl	%edx, 192(%esp)
	leal	2049(%esp), %edx
	movl	%ebx, 172(%esp)
	leal	2048(%esp), %ebx
	movl	%edx, 132(%esp)
	leal	2051(%esp), %edx
	movl	%ebx, 128(%esp)
	leal	2050(%esp), %ebx
	movl	%edx, 140(%esp)
	leal	2000(%esp), %edx
	movl	%ebx, 136(%esp)
	leal	272(%esp), %ebx
	movl	%edx, 196(%esp)
	leal	208(%esp), %edx
	movl	%ebx, 204(%esp)
	leal	2160(%esp), %ebx
	movl	%edx, 124(%esp)
	leal	256(%esp), %edx
	movl	%ebx, 148(%esp)
	movl	%edx, 200(%esp)
.L39:
	movl	148(%esp), %edx
	movl	(%edx), %eax
	movl	4(%edx), %edx
	movl	%eax, 104(%esp)
	movl	%edx, 108(%esp)
	movl	148(%esp), %edx
	movl	12(%edx), %ebx
	movl	20(%edx), %edi
	movl	8(%edx), %ecx
	movl	16(%edx), %esi
	movl	24(%edx), %eax
	movl	28(%edx), %edx
	movl	%eax, 96(%esp)
	movl	%edx, 100(%esp)
	movl	148(%esp), %edx
	movl	32(%edx), %eax
	movl	36(%edx), %edx
	movl	%eax, 88(%esp)
	movl	%edx, 92(%esp)
	movl	148(%esp), %edx
	movl	40(%edx), %eax
	movl	44(%edx), %edx
	movl	%eax, 80(%esp)
	movl	%edx, 84(%esp)
	movl	148(%esp), %edx
	movl	48(%edx), %eax
	movl	52(%edx), %edx
	movl	%eax, 72(%esp)
	movl	%edx, 76(%esp)
	movl	148(%esp), %edx
	movl	56(%edx), %eax
	movl	60(%edx), %edx
	movl	%eax, 64(%esp)
	movl	%edx, 68(%esp)
	movl	2260(%esp), %edx
	movzbl	104(%esp), %ebp
	movl	(%edx), %eax
	movl	4(%edx), %edx
	movl	%eax, 56(%esp)
	movl	%edx, 60(%esp)
	movl	2260(%esp), %edx
	movl	8(%edx), %eax
	movl	12(%edx), %edx
	movl	%eax, 48(%esp)
	movl	%edx, 52(%esp)
	movl	2260(%esp), %edx
	movl	16(%edx), %eax
	movl	20(%edx), %edx
	movl	%eax, 40(%esp)
	movl	%edx, 44(%esp)
	movl	2260(%esp), %edx
	movl	24(%edx), %eax
	movl	28(%edx), %edx
	movl	%eax, 32(%esp)
	movl	%edx, 36(%esp)
	movl	2260(%esp), %edx
	movl	32(%edx), %eax
	movl	36(%edx), %edx
	movl	%eax, 24(%esp)
	movl	%edx, 28(%esp)
	movl	2260(%esp), %edx
	movl	40(%edx), %eax
	movl	44(%edx), %edx
	movl	%eax, 16(%esp)
	movl	%ebp, %eax
	movl	%edx, 20(%esp)
	movl	108(%esp), %edx
	movb	%al, 2048(%esp)
	movl	104(%esp), %eax
	shrdl	$8, %edx, %eax
	shrl	$8, %edx
	movl	%eax, 112(%esp)
	movl	%edx, 116(%esp)
	movzbl	112(%esp), %edx
	movb	%al, 170(%esp)
	movl	104(%esp), %eax
	movb	%bl, 2060(%esp)
	movb	%cl, 2056(%esp)
	movb	%dl, 2049(%esp)
	movl	108(%esp), %edx
	shrdl	$16, %edx, %eax
	shrl	$16, %edx
	movl	%eax, 152(%esp)
	movl	%edx, 156(%esp)
	movzbl	152(%esp), %edx
	movb	%al, 171(%esp)
	movl	104(%esp), %eax
	movb	%dl, 2050(%esp)
	movl	108(%esp), %edx
	shrdl	$24, %edx, %eax
	movl	%ebx, %edx
	movb	%al, 2051(%esp)
	movl	108(%esp), %eax
	movb	%al, 2052(%esp)
	shrl	$8, %eax
	movb	%al, 2053(%esp)
	movl	108(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2054(%esp)
	movl	108(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2055(%esp)
	movl	%ecx, %eax
	shrdl	$8, %edx, %eax
	movl	%ebx, %edx
	movb	%al, 2057(%esp)
	movl	%ecx, %eax
	shrdl	$16, %edx, %eax
	movl	%edi, %edx
	movb	%al, 2058(%esp)
	movl	%ecx, %eax
	shrdl	$24, %ebx, %eax
	movb	%al, 2059(%esp)
	movl	%ebx, %eax
	shrl	$8, %eax
	movb	%al, 2061(%esp)
	movl	%ebx, %eax
	shrl	$16, %eax
	movb	%al, 2062(%esp)
	movl	%ebx, %eax
	movl	%esi, %ebx
	shrl	$24, %eax
	movb	%al, 2063(%esp)
	movl	%esi, %eax
	shrdl	$8, %edi, %eax
	movb	%al, 2065(%esp)
	movl	%esi, %eax
	shrdl	$16, %edi, %eax
	movb	%al, 2066(%esp)
	movl	%esi, %eax
	shrdl	$24, %edi, %eax
	movb	%al, 2067(%esp)
	movl	%edi, %eax
	shrl	$8, %eax
	movb	%bl, 2064(%esp)
	movb	%dl, 2068(%esp)
	movl	100(%esp), %edx
	movb	%al, 2069(%esp)
	movl	%edi, %eax
	shrl	$16, %eax
	movb	%al, 2070(%esp)
	movl	%edi, %eax
	shrl	$24, %eax
	movb	%al, 2071(%esp)
	movzbl	96(%esp), %eax
	movb	%al, 2072(%esp)
	movl	96(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	100(%esp), %edx
	movb	%al, 2073(%esp)
	movl	96(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	100(%esp), %edx
	movb	%al, 2074(%esp)
	movl	96(%esp), %eax
	shrdl	$24, %edx, %eax
	movzbl	88(%esp), %edx
	movb	%al, 2075(%esp)
	movl	100(%esp), %eax
	movb	%dl, 2080(%esp)
	movl	92(%esp), %edx
	movb	%al, 2076(%esp)
	shrl	$8, %eax
	movb	%al, 2077(%esp)
	movl	100(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2078(%esp)
	movl	100(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2079(%esp)
	movl	88(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	92(%esp), %edx
	movb	%al, 2081(%esp)
	movl	88(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	92(%esp), %edx
	movb	%al, 2082(%esp)
	movl	88(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2083(%esp)
	movl	92(%esp), %eax
	movb	%al, 2084(%esp)
	shrl	$8, %eax
	movl	84(%esp), %edx
	movb	%al, 2085(%esp)
	movl	92(%esp), %eax
	movzbl	80(%esp), %ebx
	shrl	$16, %eax
	movb	%al, 2086(%esp)
	movl	92(%esp), %eax
	movb	%bl, 2088(%esp)
	shrl	$24, %eax
	movb	%al, 2087(%esp)
	movl	80(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	84(%esp), %edx
	movb	%al, 2089(%esp)
	movl	80(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	84(%esp), %edx
	movb	%al, 2090(%esp)
	movl	80(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	76(%esp), %edx
	movb	%al, 2091(%esp)
	movl	84(%esp), %eax
	movb	%al, 2092(%esp)
	shrl	$8, %eax
	movb	%al, 2093(%esp)
	movl	84(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2094(%esp)
	movl	84(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2095(%esp)
	movzbl	72(%esp), %eax
	movb	%al, 2096(%esp)
	movl	72(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	76(%esp), %edx
	movb	%al, 2097(%esp)
	movl	72(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	76(%esp), %edx
	movb	%al, 2098(%esp)
	movl	72(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2099(%esp)
	movl	76(%esp), %eax
	movzbl	64(%esp), %edx
	movzbl	56(%esp), %ebx
	movb	%al, 2100(%esp)
	shrl	$8, %eax
	movb	%al, 2101(%esp)
	movl	76(%esp), %eax
	movb	%dl, 2104(%esp)
	movl	68(%esp), %edx
	movb	%bl, 2112(%esp)
	shrl	$16, %eax
	movb	%al, 2102(%esp)
	movl	76(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2103(%esp)
	movl	64(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	68(%esp), %edx
	movb	%al, 2105(%esp)
	movl	64(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	68(%esp), %edx
	movb	%al, 2106(%esp)
	movl	64(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	60(%esp), %edx
	movb	%al, 2107(%esp)
	movl	68(%esp), %eax
	movb	%al, 2108(%esp)
	shrl	$8, %eax
	movb	%al, 2109(%esp)
	movl	68(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2110(%esp)
	movl	68(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2111(%esp)
	movl	56(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	60(%esp), %edx
	movb	%al, 2113(%esp)
	movl	56(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	60(%esp), %edx
	movb	%al, 2114(%esp)
	movl	56(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2115(%esp)
	movl	60(%esp), %eax
	movl	52(%esp), %edx
	movb	%al, 2116(%esp)
	shrl	$8, %eax
	movb	%al, 2117(%esp)
	movl	60(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2118(%esp)
	movl	60(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2119(%esp)
	movzbl	48(%esp), %eax
	movb	%al, 2120(%esp)
	movl	48(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	52(%esp), %edx
	movb	%al, 2121(%esp)
	movl	48(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	52(%esp), %edx
	movb	%al, 2122(%esp)
	movl	48(%esp), %eax
	shrdl	$24, %edx, %eax
	movzbl	40(%esp), %edx
	movb	%al, 2123(%esp)
	movl	52(%esp), %eax
	movb	%dl, 2128(%esp)
	movl	44(%esp), %edx
	movb	%al, 2124(%esp)
	shrl	$8, %eax
	movb	%al, 2125(%esp)
	movl	52(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2126(%esp)
	movl	52(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2127(%esp)
	movl	40(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	44(%esp), %edx
	movb	%al, 2129(%esp)
	movl	40(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	44(%esp), %edx
	movb	%al, 2130(%esp)
	movl	40(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2131(%esp)
	movl	44(%esp), %eax
	movl	36(%esp), %edx
	movzbl	32(%esp), %ebx
	movb	%al, 2132(%esp)
	shrl	$8, %eax
	movb	%al, 2133(%esp)
	movl	44(%esp), %eax
	movb	%bl, 2136(%esp)
	movl	%ebp, %ebx
	shrl	$16, %eax
	movb	%al, 2134(%esp)
	movl	44(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2135(%esp)
	movl	32(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	36(%esp), %edx
	movb	%al, 2137(%esp)
	movl	32(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	36(%esp), %edx
	movb	%al, 2138(%esp)
	movl	32(%esp), %eax
	shrdl	$24, %edx, %eax
	movl	28(%esp), %edx
	movb	%al, 2139(%esp)
	movl	36(%esp), %eax
	movb	%al, 2140(%esp)
	shrl	$8, %eax
	movb	%al, 2141(%esp)
	movl	36(%esp), %eax
	shrl	$16, %eax
	movb	%al, 2142(%esp)
	movl	36(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2143(%esp)
	movzbl	24(%esp), %eax
	movb	%al, 2144(%esp)
	movl	24(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	28(%esp), %edx
	movb	%al, 2145(%esp)
	movl	24(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	28(%esp), %edx
	movb	%al, 2146(%esp)
	movl	24(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2147(%esp)
	movl	28(%esp), %eax
	movzbl	16(%esp), %edx
	movzbl	170(%esp), %ecx
	movb	%al, 2148(%esp)
	shrl	$8, %eax
	movb	%al, 2149(%esp)
	movl	28(%esp), %eax
	movb	%dl, 2152(%esp)
	movl	20(%esp), %edx
	sall	$6, %ecx
	shrl	$16, %eax
	movb	%al, 2150(%esp)
	movl	28(%esp), %eax
	shrl	$24, %eax
	movb	%al, 2151(%esp)
	movl	16(%esp), %eax
	shrdl	$8, %edx, %eax
	movl	20(%esp), %edx
	movb	%al, 2153(%esp)
	movl	16(%esp), %eax
	shrdl	$16, %edx, %eax
	movl	20(%esp), %edx
	movb	%al, 2154(%esp)
	movl	16(%esp), %eax
	shrdl	$24, %edx, %eax
	movb	%al, 2155(%esp)
	movl	20(%esp), %eax
	movb	%al, 2156(%esp)
	shrl	$8, %eax
	movb	%al, 147(%esp)
	movb	%al, 2157(%esp)
	movl	20(%esp), %eax
	shrl	$16, %eax
	movb	%al, 168(%esp)
	movb	%al, 2158(%esp)
	movl	20(%esp), %eax
	shrl	$24, %eax
	movb	%al, 169(%esp)
	movb	%al, 2159(%esp)
	movzbl	%bl, %eax
	sall	$6, %eax
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+48(%eax), %xmm0
	movdqa	%xmm0, 208(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%eax), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%ecx), %xmm0
	movdqa	%xmm0, 224(%esp)
	movzbl	171(%esp), %edx
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%ecx), %xmm0
	movzbl	152(%esp), %ebp
	movl	200(%esp), %ecx
	movb	%bl, 123(%esp)
	sall	$6, %edx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%eax), %xmm0
	movl	$3, %eax
	movdqa	%xmm0, 240(%esp)
	.p2align 4,,7
	.p2align 3
.L23:
	movl	128(%esp), %ebx
	movzbl	112(%esp), %edi
	movzbl	(%ebx,%eax), %edx
	movl	%ebp, %ebx
	movzbl	%bl, %esi
	movzbl	123(%esp), %ebx
	sall	$6, %esi
	sall	$6, %edi
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%esi), %xmm0
	sall	$6, %edx
	sall	$6, %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ebx), %xmm0
	movl	132(%esp), %ebx
	movdqa	%xmm0, (%ecx)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%edx), %xmm0
	movzbl	(%ebx,%eax), %ebx
	movb	%bl, 123(%esp)
	movzbl	%bl, %ebx
	sall	$6, %ebx
	movl	%ebx, 152(%esp)
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%ebx), %xmm0
	movl	136(%esp), %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edi), %xmm0
	movdqa	%xmm0, 16(%ecx)
	movzbl	(%ebx,%eax), %ebx
	movb	%bl, 112(%esp)
	movzbl	%bl, %edi
	movl	152(%esp), %ebx
	sall	$6, %edi
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%ebx), %xmm0
	movl	140(%esp), %ebx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%esi), %xmm0
	movdqa	%xmm0, 32(%ecx)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%edi), %xmm0
	movzbl	(%ebx,%eax), %ebp
	addl	$4, %eax
	movl	%ebp, %ebx
	movzbl	%bl, %esi
	movl	152(%esp), %ebx
	sall	$6, %esi
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%esi), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%ebx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edx), %xmm0
	movl	$112, %edx
	movdqa	%xmm0, 48(%ecx)
	subl	%eax, %edx
	addl	$64, %ecx
	cmpl	$111, %eax
	jne	.L23
	movl	172(%esp), %eax
	sall	$4, %edx
	xorl	%ecx, %ecx
	movl	192(%esp), %esi
	movl	%edx, %edi
	.p2align 4,,7
	.p2align 3
.L21:
	movzbl	-1(%eax), %ebx
	movzbl	(%eax), %edx
	sall	$6, %ebx
	sall	$6, %edx
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+32(%ebx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+48(%edx), %xmm0
	movzbl	-2(%eax), %edx
	sall	$6, %edx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edx), %xmm0
	movzbl	-3(%eax), %edx
	addl	$1, %eax
	sall	$6, %edx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edx), %xmm0
	movdqa	%xmm0, (%esi,%ecx)
	addl	$16, %ecx
	cmpl	%edi, %ecx
	jne	.L21
	movzbl	168(%esp), %edx
	movdqa	256(%esp), %xmm3
	movdqa	208(%esp), %xmm2
	movzbl	169(%esp), %eax
	movdqa	224(%esp), %xmm1
	movzbl	147(%esp), %ecx
	sall	$6, %edx
	sall	$6, %eax
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+16(%edx), %xmm0
	sall	$6, %ecx
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%ecx), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix+32(%eax), %xmm0
	movdqa	%xmm0, 2000(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix+16(%eax), %xmm0
	pxor	crypto_hashblocks_rfsb509_xmm1_matrix(%edx), %xmm0
	movl	204(%esp), %edx
	xorl	%ecx, %ecx
	movdqa	%xmm0, 2016(%esp)
	movdqa	crypto_hashblocks_rfsb509_xmm1_matrix(%eax), %xmm0
	movdqa	%xmm0, 2032(%esp)
	movdqa	240(%esp), %xmm0
	.p2align 4,,7
	.p2align 3
.L25:
	movdqa	%xmm2, %xmm5
	movdqa	%xmm2, %xmm4
	psrlq	$61, %xmm5
	psllq	$3, %xmm4
	pshufd	$69, %xmm5, %xmm2
	psrldq	$8, %xmm5
	pxor	%xmm2, %xmm4
	movdqa	%xmm1, %xmm2
	psrlq	$61, %xmm2
	pxor	%xmm3, %xmm5
	movdqa	%xmm1, %xmm3
	pshufd	$69, %xmm2, %xmm1
	psllq	$3, %xmm3
	psrldq	$8, %xmm2
	pxor	(%edx), %xmm4
	pxor	%xmm1, %xmm3
	pxor	%xmm2, %xmm4
	movdqa	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	psrlq	$61, %xmm1
	psllq	$3, %xmm2
	pshufd	$69, %xmm1, %xmm0
	psrldq	$8, %xmm1
	pxor	%xmm0, %xmm2
	movdqa	%xmm5, %xmm0
	psrlq	$61, %xmm0
	pxor	16(%edx), %xmm3
	movdqa	%xmm5, -16(%edx)
	pxor	%xmm1, %xmm3
	movdqa	%xmm5, %xmm1
	pshufd	$69, %xmm0, %xmm5
	psllq	$3, %xmm1
	psrldq	$8, %xmm0
	pxor	32(%edx), %xmm2
	pxor	%xmm5, %xmm1
	pxor	%xmm0, %xmm2
	movdqa	%xmm4, %xmm5
	movdqa	%xmm4, %xmm0
	psrlq	$61, %xmm5
	psllq	$3, %xmm0
	movdqa	%xmm4, (%edx)
	pshufd	$69, %xmm5, %xmm4
	psrldq	$8, %xmm5
	pxor	%xmm4, %xmm0
	movdqa	%xmm3, %xmm4
	psrlq	$61, %xmm4
	pxor	48(%edx), %xmm1
	movdqa	%xmm3, 16(%edx)
	pxor	%xmm5, %xmm1
	addl	$6, %ecx
	pshufd	$69, %xmm4, %xmm5
	psllq	$3, %xmm3
	psrldq	$8, %xmm4
	pxor	64(%edx), %xmm0
	movl	$111, %eax
	movdqa	%xmm2, 32(%edx)
	movdqa	%xmm1, 48(%edx)
	pxor	%xmm5, %xmm3
	pxor	%xmm4, %xmm0
	pxor	80(%edx), %xmm3
	movdqa	%xmm0, 64(%edx)
	movdqa	%xmm3, 80(%edx)
	subl	%ecx, %eax
	addl	$96, %edx
	cmpl	$108, %ecx
	jne	.L25
	movl	196(%esp), %edx
	.p2align 4,,7
	.p2align 3
.L26:
	movdqa	-64(%edx), %xmm0
	movdqa	%xmm0, %xmm1
	psrlq	$61, %xmm1
	pshufd	$69, %xmm1, %xmm2
	psllq	$3, %xmm0
	psrldq	$8, %xmm1
	pxor	-16(%edx), %xmm1
	pxor	%xmm2, %xmm0
	movdqa	%xmm1, -16(%edx)
	pxor	(%edx), %xmm0
	movdqa	%xmm0, (%edx)
	addl	$16, %edx
	subl	$1, %eax
	jne	.L26
	movl	124(%esp), %edx
	movdqa	1984(%esp), %xmm0
	movdqa	%xmm0, %xmm1
	psrlq	$61, %xmm1
	pand	176(%esp), %xmm0
	movdqa	%xmm0, 1984(%esp)
	psrldq	$8, %xmm1
	movl	$63, %ebx
	pxor	2032(%esp), %xmm1
	movdqa	%xmm1, 2032(%esp)
	movzbl	1824(%edx), %eax
	movb	%al, 2160(%esp)
	movzbl	1825(%edx), %eax
	movb	%al, 2161(%esp)
	movzbl	1826(%edx), %eax
	movb	%al, 2162(%esp)
	movzbl	1827(%edx), %eax
	movb	%al, 2163(%esp)
	movzbl	1828(%edx), %eax
	movb	%al, 2164(%esp)
	movzbl	1829(%edx), %eax
	movb	%al, 2165(%esp)
	movzbl	1830(%edx), %eax
	movb	%al, 2166(%esp)
	movzbl	1831(%edx), %eax
	movb	%al, 2167(%esp)
	movzbl	1832(%edx), %eax
	movb	%al, 2168(%esp)
	movzbl	1833(%edx), %eax
	movb	%al, 2169(%esp)
	movzbl	1834(%edx), %eax
	movb	%al, 2170(%esp)
	movzbl	1835(%edx), %eax
	movb	%al, 2171(%esp)
	movzbl	1836(%edx), %eax
	movb	%al, 2172(%esp)
	movzbl	1837(%edx), %eax
	movb	%al, 2173(%esp)
	movzbl	1838(%edx), %eax
	movb	%al, 2174(%esp)
	movzbl	1839(%edx), %eax
	movb	%al, 2175(%esp)
	movzbl	1808(%edx), %eax
	movb	%al, 2176(%esp)
	movzbl	1809(%edx), %eax
	movb	%al, 2177(%esp)
	movzbl	1810(%edx), %eax
	movb	%al, 2178(%esp)
	movzbl	1811(%edx), %eax
	movb	%al, 2179(%esp)
	movzbl	1812(%edx), %eax
	movb	%al, 2180(%esp)
	movzbl	1813(%edx), %eax
	movb	%al, 2181(%esp)
	movzbl	1814(%edx), %eax
	movb	%al, 2182(%esp)
	movzbl	1815(%edx), %eax
	movb	%al, 2183(%esp)
	movzbl	1816(%edx), %eax
	movb	%al, 2184(%esp)
	movzbl	1817(%edx), %eax
	movb	%al, 2185(%esp)
	movzbl	1818(%edx), %eax
	movb	%al, 2186(%esp)
	movzbl	1819(%edx), %eax
	movb	%al, 2187(%esp)
	movzbl	1820(%edx), %eax
	movb	%al, 2188(%esp)
	movzbl	1821(%edx), %eax
	movb	%al, 2189(%esp)
	movzbl	1822(%edx), %eax
	movb	%al, 2190(%esp)
	movzbl	1823(%edx), %eax
	movb	%al, 2191(%esp)
	movzbl	1792(%edx), %eax
	movb	%al, 2192(%esp)
	movzbl	1793(%edx), %eax
	movb	%al, 2193(%esp)
	movzbl	1794(%edx), %eax
	movb	%al, 2194(%esp)
	movzbl	1795(%edx), %eax
	movb	%al, 2195(%esp)
	movzbl	1796(%edx), %eax
	movb	%al, 2196(%esp)
	movzbl	1797(%edx), %eax
	movb	%al, 2197(%esp)
	movzbl	1798(%edx), %eax
	movb	%al, 2198(%esp)
	movzbl	1799(%edx), %eax
	movb	%al, 2199(%esp)
	movzbl	1800(%edx), %eax
	movb	%al, 2200(%esp)
	movzbl	1801(%edx), %eax
	movb	%al, 2201(%esp)
	movzbl	1802(%edx), %eax
	movb	%al, 2202(%esp)
	movzbl	1803(%edx), %eax
	movb	%al, 2203(%esp)
	movzbl	1804(%edx), %eax
	movb	%al, 2204(%esp)
	movzbl	1805(%edx), %eax
	movb	%al, 2205(%esp)
	movzbl	1806(%edx), %eax
	movb	%al, 2206(%esp)
	movzbl	1807(%edx), %eax
	movb	%al, 2207(%esp)
	movzbl	1776(%edx), %eax
	movl	148(%esp), %esi
	movb	%al, 2208(%esp)
	movzbl	1777(%edx), %eax
	movb	%al, 2209(%esp)
	movzbl	1778(%edx), %eax
	movb	%al, 2210(%esp)
	movzbl	1779(%edx), %eax
	movb	%al, 2211(%esp)
	movzbl	1780(%edx), %eax
	movb	%al, 2212(%esp)
	movzbl	1781(%edx), %eax
	movb	%al, 2213(%esp)
	movzbl	1782(%edx), %eax
	movb	%al, 2214(%esp)
	movzbl	1783(%edx), %eax
	movb	%al, 2215(%esp)
	movzbl	1784(%edx), %eax
	movb	%al, 2216(%esp)
	movzbl	1785(%edx), %eax
	movb	%al, 2217(%esp)
	movzbl	1786(%edx), %eax
	movb	%al, 2218(%esp)
	movzbl	1787(%edx), %eax
	movb	%al, 2219(%esp)
	movzbl	1788(%edx), %eax
	movb	%al, 2220(%esp)
	movzbl	1789(%edx), %eax
	movb	%al, 2221(%esp)
	movzbl	1790(%edx), %eax
	movb	%al, 2222(%esp)
	movzbl	1791(%edx), %eax
	movb	%al, 2223(%esp)
	.p2align 4,,7
	.p2align 3
.L27:
	movzbl	(%esi,%ebx), %eax
	subl	$1, %ebx
	movl	$.LC1, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	cmpl	$-1, %ebx
	jne	.L27
	movl	$10, (%esp)
	call	putchar
	addl	$48, 2260(%esp)
	addl	$-48, 160(%esp)
	adcl	$-1, 164(%esp)
	cmpl	$0, 164(%esp)
	ja	.L39
	cmpl	$47, 160(%esp)
	ja	.L39
.L20:
	movl	2256(%esp), %ebx
	movdqa	2160(%esp), %xmm0
	movl	160(%esp), %eax
	movdqu	%xmm0, (%ebx)
	movdqa	2176(%esp), %xmm0
	movdqu	%xmm0, 16(%ebx)
	movdqa	2192(%esp), %xmm0
	movdqu	%xmm0, 32(%ebx)
	movdqa	2208(%esp), %xmm0
	movdqu	%xmm0, 48(%ebx)
	addl	$2236, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE505:
	.size	crypto_hashblocks, .-crypto_hashblocks
	.section	.rodata.str1.1
.LC2:
	.string	"r"
.LC3:
	.string	"rfsb.c"
.LC4:
	.string	"f"
	.globl	__umoddi3
.LC5:
	.string	"%.2x"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB506:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	$32, %ecx
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$208, %esp
	movl	stdin, %ebx
	.cfi_offset 3, -20
	.cfi_offset 6, -16
	.cfi_offset 7, -12
	leal	32(%esp), %eax
	movl	%eax, 28(%esp)
	movl	28(%esp), %edi
	xorl	%eax, %eax
	cmpl	$1, 8(%ebp)
	rep stosl
	jle	.L47
	movl	12(%ebp), %eax
	movl	$.LC2, 4(%esp)
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	fopen
	movl	%eax, %ebx
.L47:
	testl	%ebx, %ebx
	je	.L54
	movl	$0, 16(%esp)
	leal	160(%esp), %esi
	movl	$0, 20(%esp)
	jmp	.L48
	.p2align 4,,7
	.p2align 3
.L55:
	movl	%esi, %edx
	leal	32(%esp), %eax
	call	crypto_hashblocks.constprop.0
.L48:
	movl	%ebx, 12(%esp)
	movl	$48, 8(%esp)
	movl	$1, 4(%esp)
	movl	%esi, (%esp)
	call	fread
	xorl	%edx, %edx
	movl	%ebx, (%esp)
	addl	%eax, 16(%esp)
	adcl	%edx, 20(%esp)
	call	feof
	testl	%eax, %eax
	je	.L55
	movl	%ebx, (%esp)
	call	fclose
	movl	16(%esp), %eax
	movl	20(%esp), %edx
	movl	$48, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__umoddi3
	cmpl	$40, %eax
	ja	.L56
.L50:
	movl	$40, %edx
	movl	$64, %ebx
	subl	%eax, %edx
	addl	%esi, %eax
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	memset
	movl	16(%esp), %eax
	movl	20(%esp), %edx
	movl	%eax, 200(%esp)
	leal	32(%esp), %eax
	movl	%edx, 204(%esp)
	movl	%esi, %edx
	call	crypto_hashblocks.constprop.0
	.p2align 4,,7
	.p2align 3
.L51:
	movzbl	31(%esp,%ebx), %eax
	movl	$.LC5, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	subl	$1, %ebx
	jne	.L51
	movl	$10, (%esp)
	call	putchar
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	.cfi_remember_state
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
.L56:
	.cfi_restore_state
	movl	$48, %edx
	subl	%eax, %edx
	addl	%esi, %eax
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	memset
	movl	%esi, %edx
	leal	32(%esp), %eax
	call	crypto_hashblocks.constprop.0
	xorl	%eax, %eax
	jmp	.L50
.L54:
	movl	$__PRETTY_FUNCTION__.4213, 12(%esp)
	movl	$93, 8(%esp)
	movl	$.LC3, 4(%esp)
	movl	$.LC4, (%esp)
	call	__assert_fail
	.cfi_endproc
.LFE506:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.4213, @object
	.size	__PRETTY_FUNCTION__.4213, 5
__PRETTY_FUNCTION__.4213:
	.string	"main"
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	-1
	.long	-1
	.long	-1
	.long	536870911
	.ident	"GCC: (Debian 4.6.3-1) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
