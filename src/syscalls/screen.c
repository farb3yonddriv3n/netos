/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

typedef struct text_attr_st text_attr_t;

static struct screen_s screen;

static void update_cursor()
{
	unsigned short position = screen.view.offset;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position >> 8) & 0xFF));
}

inline static void update()
{
	update_cursor();
}

inline static void display_char(char c)
{
	screen.view.port[screen.view.offset].c = c;
	screen.view.port[screen.view.offset].attr = 0x7;
	screen.view.offset++;
}

void k_screen_clear()
{
	unsigned short c = 0x0720;
	int i;

	for(i = 0; i < (SCREEN_MAX / 2); i++)
		memcpy(screen.view.port + i, &c, sizeof(c));
	screen.view.offset = 0;

	update();
}

void k_screen_init()
{
	screen.view.offset = 0;
	screen.view.port = (struct viewport_s *)0xb8000;

	k_screen_clear();
}

void k_screen_char(char c)
{
	display_char(c);
	update();
}

void k_screen_debug(char c)
{
	(void )c;
}

void k_screen_newline()
{
	if(SCREEN_ROW(screen.view.offset) > 10) {
		k_screen_clear();
	}
	screen.view.offset += SCREEN_W - (screen.view.offset % SCREEN_W);
	update();
}

void k_screen_string(char *src, int nsrc, char newline)
{
	int i;

	for(i = 0; i < nsrc; i++) {
		display_char(src[i]);
	}

	if(newline == 1)
		k_screen_newline();

	update();
}

void k_screen_print(const char *src)
{
	int len = strlen(src);

	k_screen_string((char *)src, len, 1);
}
