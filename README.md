# foobar
v. 0.0.1

Just for fun...

## Problem
Write a computer program to count from 1 to 100. For each number n, the program
should produce output according to the following rules: 

* If n is evenly divisible by 3, output the word 'foo'.
* If n is evenly divisible by 5, output the word 'bar'.
* If n is evenly divisible by both 3 and 5, output the word 'foobar'.
* If n is divisible by neither 3 nor 5, output the number itself.

## Code
A python implementation is straightforward- modulus is a clear way to check to
see if a number is evenly divisible, and ordering the cases from largest to
smallest avoids the problem of things that are divisible by 15 also being
divisible by 3 and 5:

foobar.py

```python
for i in range(1, 101):
  if i % 15 == 0:
    print('foobar')
  elif i % 5 == 0:
    print('bar')
  elif i % 3 == 0:
    print('foo')
  else:
    print i
```

Running the command produces the following output:

```console
$ python foobar.py
1
2
foo
4
bar
foo
7
8
foo
bar
11
foo
13
14
foobar
16
17
foo
19
bar
foo
22
23
foo
bar
26
foo
28
29
foobar
31
32
foo
34
bar
foo
37
38
foo
bar
41
foo
43
44
foobar
46
47
foo
49
bar
foo
52
53
foo
bar
56
foo
58
59
foobar
61
62
foo
64
bar
foo
67
68
foo
bar
71
foo
73
74
foobar
76
77
foo
79
bar
foo
82
83
foo
bar
86
foo
88
89
foobar
91
92
foo
94
bar
foo
97
98
foo
bar
$
```

Getting Python to solve the problem is fun. For a bit more of a challenge,
here's a solution in C:

foobar.c

```c
#include <stdio.h>

int main() {
  char i = 1;
  while (i <= 100) {
    if (i % 15 == 0) {
      printf("foobar\n");
    } else if (i % 5 == 0) {
      printf("bar\n");
    } else if (i % 3 == 0) {
      printf("foo\n");
    } else {
      printf("%d\n", i);
    }
    i++;
  }
  return 0;
}
```

To run the program in C, you have to compile it first. I used gcc on my mac:

```console
$ gcc -o foobar foobar.c
$ ./foobar
1
2
foo
...
97
98
foo
bar
$
```

C is pretty cool, but for a program like this it's not all that different from
Python. For something really different, let's try solving the problem in
assembly. 

First, lets get assembly for our C code so we have something to start working
with:

```console
$ gcc -S foobar.c
```

This produces foobar.s. Here it is, in all it's glory:

```nasm
	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movb	$1, -5(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movsbl	-5(%rbp), %eax
	cmpl	$100, %eax
	jg	LBB0_12
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	$15, %eax
	movsbl	-5(%rbp), %ecx
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-12(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	cmpl	$0, %edx
	jne	LBB0_4
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	jmp	LBB0_11
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	$5, %eax
	movsbl	-5(%rbp), %ecx
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-20(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	cmpl	$0, %edx
	jne	LBB0_6
## %bb.5:                               ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	jmp	LBB0_10
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	$3, %eax
	movsbl	-5(%rbp), %ecx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-28(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	cmpl	$0, %edx
	jne	LBB0_8
## %bb.7:                               ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	jmp	LBB0_9
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str.3(%rip), %rdi
	movsbl	-5(%rbp), %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -36(%rbp)         ## 4-byte Spill
LBB0_9:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_10
LBB0_10:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_11
LBB0_11:                                ##   in Loop: Header=BB0_1 Depth=1
	movb	-5(%rbp), %al
	addb	$1, %al
	movb	%al, -5(%rbp)
	jmp	LBB0_1
LBB0_12:
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"foobar\n"

L_.str.1:                               ## @.str.1
	.asciz	"bar\n"

L_.str.2:                               ## @.str.2
	.asciz	"foo\n"

L_.str.3:                               ## @.str.3
	.asciz	"%d\n"


.subsections_via_symbols
```

Now we're having fun! I didn't have time to write a cleaned up version in
assembly that would run, but I did start digging into assembly to see how that
might work. The following code doesn't use variables, it just loads values
directly into registers and looks in other registers for the result of
calculations.

pseudo-assembly:

```nasm
          mov     cx,       1         ; set count register to 1. 

foobar    mov     ax,       cx        ; move the counter into ax.
          mov     bx,       0xf       ; move 15 into bx. 
          div     bx                  ; divide ax by bx. 
          cmp     dx,       0x0       ; is the remainder 0?
          jnz     bar                 ; if not, jump to bar.
          mov     rax,      0x2000004 ; write
          mov     rdi,      0x1       ; stdout
          mov     rsi,      foo   
          mov     rdx,      0x6
          syscall
          jmp     increment           ; jump to the end of the loop.

bar       mov     ax,       cx        ; move the counter into ax.
          mov     bx,       0x5       ; move 5 into bx.
          div     bx                  ; divide ax by bx.
          cmp     dx,       0x0       ; is the remainder 0?
          jnz     foo                 ; if not, jump to foo.
          mov     rax,      0x2000004 ; write
          mov     rdi,      0x1                ; stdout
          mov     rsi,      bar
          mov     rdx,      0x3
          syscall
          jmp     increment           ; jump to the end of the loop.

foo       mov     ax,       cx        ; move the counter into ax.
          mov     bx,       0x3       ; move 3 into bx.
          div     bx                  ; divide ax by bx.
          cmp     dx,       0x0       ; is the remainder 0?
          jnz     else                ; if not, jump to else.
          mov     rax,      0x2000004 ; write
          mov     rdi,      0x1       ; stdout
          mov     rsi,      foo   
          mov     rdx,      0x3
          syscall
          jmp     increment           ; jump to the end of the loop.

else      mov     ax,       cx        ; print a number.
          push    ax                           
          push    dword     format
          call    printf
                           
increment inc     cx                  ; increment cx.
          cmp     cx,       0x64      ; compare cx to 100.
          jle     foobar              ; jump if less than or equal.

.data                      
          foo     db        "foo"
          bar     db        "bar"
```

Here are some registers from the code above:

Register | Name | Notes
--- | :--- | :---
`ax` | **primary accumulator** | Stores our number from 1 to 100 when we want to divide it by 3, 5 or 15.
`bx` | **base register** | Stores the divisor, e.g., 3, 5, or 15.
`cx` | **count register** | Store the count itself, from 1 to 100.
`dx` | **data register** | Used for the comparison function, to check to see if the remainder is 0.
