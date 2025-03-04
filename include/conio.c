#include "conio.h"

static IOCharMap		giocharmap = IOCHM_ASCII;

#if defined(__ATMOS__)
#warning "ATMOS configuration"
// Atmos-specific I/O routines using ROM calls
// 0x0238: Output char in X, 0x023B: Input char with status in A, 0xE9E4: Init, 0xFDF0: Plot/clear
__asm bsout
{
_putchar:
    ldy #0
    lda (sp),y
    cmp #0x0A       // Newline
    bne putchar2
    pha
    ldx #0x0D       // Precede LF with CR
    jsr 0x0238
    pla
putchar2:
    tax
    jmp 0x0238      // Output char
}

__asm bsin
{
_getchar:
    jsr 0x023B      // Get input char
    bpl _getchar    // Loop until valid (negative flag set)
    tax
    jsr 0x0238      // Echo to screen
    lda #0          // Clear high byte for C compatibility
    rts
}

__asm bsget
{
_getchar_noecho:
    jsr 0x023B      // Non-echo version for flexibility
    bpl _getchar_noecho
    lda #0
    rts
}

__asm bsplot
{
    jsr 0xFDF0      // Plot or clear screen (context-dependent)
}

__asm bsinit
{
    jsr 0xE9E4      // Initialize Atmos environment (screen, I/O)
}

__asm dswap
{
    nop             // Placeholder; no double buffering on Atmos
}

void atmos_cls(void) {
    __asm__("jsr 0xFDF0");  // Clear screen
}

void atmos_test(void) {
    atmos_cls();
    const char* msg = "Hello, Atmos!\n";
    while (*msg) {
        _putchar(*msg++);
    }
}
#elif defined(__C128__)
#pragma code(lowcode)
__asm bsout
{	
		ldx #0
		stx 0xff00
		jsr 0xffd2
		sta 0xff01
}
__asm bsin
{
		lda #0
		sta 0xff00
		jsr 0xffe4
		sta 0xff01	
}
__asm bsget
{
		lda #0
		sta 0xff00
		jsr 0xffcf
		sta 0xff01		
}
__asm bsplot
{	
		lda #0
		sta 0xff00
		jsr 0xfff0
		sta 0xff01
}
__asm bsinit
{	
		lda #0
		sta 0xff00
		jsr 0xff81
		sta 0xff01
}
__asm dswap
{	
		sta 0xff00
		jsr 0xff5f
		sta 0xff01
}
#pragma code(code)
#elif defined(__C128B__) || defined(__C128E__)
#define dswap 	0xff5f
#define bsout	0xffd2
#define bsin	0xffe4
#define bsget	0xffcf
#define bsplot	0xfff0
#define bsinit	0xff81
#elif defined(__PLUS4__)
#pragma code(lowcode)
__asm bsout
{	
		sta 0xff3e
		jsr 0xffd2
		sta 0xff3f
}
__asm bsin
{
		sta 0xff3e
		jsr 0xffe4
		sta 0xff3f
}
__asm bsget
{
		sta 0xff3e
		jsr 0xffcf
		sta 0xff3f
}
__asm bsplot
{	
		sta 0xff3e
		jsr 0xfff0
		sta 0xff3f
}
__asm bsinit
{	
		sta 0xff3e
		jsr 0xff81
		sta 0xff3f
}
#pragma code(code)
#elif defined(__ATARI__)
__asm bsout
{
		tax
		lda	0xe407
		pha
		lda 0xe406
		pha
		txa
}

__asm bsin
{
		lda	0xe405
		pha
		lda 0xe404
		pha
}

__asm bsget
{
		lda	0xe405
		pha
		lda 0xe404
		pha
}

__asm bsplot
{

}
__asm bsinit
{

}
#elif defined(__VIC20__)
#define bsout	0xffd2
#define bsin	0xffe4
#define bsplot	0xfff0
#define bsget	0xffcf
__asm bsinit
{
	lda #147
	jmp $ffd2	
}
#else
#define bsout	0xffd2
#define bsin	0xffe4
#define bsplot	0xfff0
#define bsinit	0xff81
#define bsget	0xffcf
#endif

#if defined(__C128__) || defined(__C128B__) || defined(__C128E__)
void dispmode40col(void)
{
	if (*(volatile char *)0xd7 >= 128)
	{
		__asm
		{		
			jsr dswap
		}
	}
}

void dispmode80col(void)
{
	if (*(volatile char *)0xd7 < 128)
	{
		__asm
		{		
			jsr dswap
		}
	}
}
#endif


void iocharmap(IOCharMap chmap)
{
	giocharmap = chmap;	
#if !defined(__ATARI__) && !defined(__ATMOS__)
	if (chmap == IOCHM_PETSCII_1)
		putrch(128 + 14);
	else if (chmap == IOCHM_PETSCII_2)
		putrch(14);
#endif
}

void putrch(char c)
{
	__asm {
		lda 	c
		jsr		bsout
	}
}

void putpch(char c)
{
#if defined(__ATARI__)
	if (c == 10)
		c = 0x9b;
#else
	if (giocharmap >= IOCHM_ASCII)
	{
		if (c == '\n')
			c = 13;
		else if (c == '\t')
		{
			char n = wherex() & 3;
			do {
				putrch(' ');
			} while (++n < 4);
			return;
		}
		else if (giocharmap >= IOCHM_PETSCII_1)
		{
			if (c >= 65 && c < 123)
			{
				if (c >= 97 || c < 91)
				{
#if defined(__CBMPET__)
					if (c >= 97)
						c ^= 0xa0;
					c ^= 0x20;
#else
					if (c >= 97)
						c ^= 0x20;
#endif				

					if (giocharmap == IOCHM_PETSCII_2)
						c &= 0xdf;
				}
			}
		}
	}

#endif

	putrch(c);
}

static char convch(char ch)
{
#if !defined(__ATARI__)

	if (giocharmap >= IOCHM_ASCII)
	{
		if (ch == 13)
			ch = 10;
		else if (giocharmap >= IOCHM_PETSCII_1)
		{
			if (ch >= 65 && ch < 219)
			{
				if (ch >= 193)
					ch ^= 0xa0;
				if (ch < 123 && (ch >= 97 || ch < 91))
					ch ^= 0x20;
			}
		}
	}

#endif
	return ch;	
}

char getrch(void)
{
	return __asm {
		jsr bsget
		sta accu
	};
}

char getpch(void)
{
	return convch(getrch());
}


char kbhit(void)
{
#if defined(__CBMPET__)
	return __asm
	{
		lda $9e
		sta	accu
	};
#else
	return __asm
	{
		lda $c6
		sta	accu
	};
#endif
}

char getche(void)
{
	char ch;
	do {
		ch = __asm {
			jsr	bsin
			sta accu
		};		
	} while (!ch);

	__asm {
		lda ch
		jsr	bsout
	}

	return convch(ch);
}

char getch(void)
{
	char ch;
	do {
		ch = __asm {
			jsr	bsin
			sta accu
		};
	} while (!ch);

	return convch(ch);
}

char getchx(void)
{
	char ch = __asm {
		jsr	bsin
		sta accu
	};

	return convch(ch);
}

void putch(char c)
{
	putpch(c);
}

void clrscr(void)
{
	putrch(147);
}

void textcursor(bool show)
{
	*(volatile char *)0xcc = show ? 0 : 1;
}

void gotoxy(char cx, char cy)
{
	__asm
	{
		ldx	cy
		ldy	cx
		clc
		jsr bsplot
	}	
}

void textcolor(char c)
{
	*(volatile char *)0x0286 = c;
}

void bgcolor(char c)
{
	*(volatile char *)0xd021 = c;
}

void bordercolor(char c)
{
	*(volatile char *)0xd020 = c;
}

void revers(char r)
{
	if (r) 
		putrch(18);
	else
		putrch(18 + 128);
}

char wherex(void)
{
#if defined(__C128__) || defined(__C128B__) || defined(__C128E__)
	return *(volatile char *)0xec;
#elif defined(__PLUS4__)
	return *(volatile char *)0xca;	
#else
	return *(volatile char *)0xd3;
#endif
}

char wherey(void)
{
#if defined(__C128__) || defined(__C128B__) || defined(__C128E__)
	return *(volatile char *)0xeb;
#elif defined(__PLUS4__)
	return *(volatile char *)0xcd;	
#else
	return *(volatile char *)0xd6;
#endif
}
