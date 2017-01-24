/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

typedef struct text_attr_st text_attr_t;

char *screen_mem = (char *)0xb8000;
static struct screen_region_s *screen = (struct screen_region_s *)0xb8000;
static int offset = 0;

static void update_cursor(int row, int col)
{
	unsigned short position = (row * 80) + col;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position >> 8) & 0xFF));
}

inline static void display_char(char c)
{
	screen[offset].c = c;
	screen[offset].attr = 0x07;
	offset++;
}

void k_screen_clear(const int w, const int c)
{
	int i;

	for(i = 0; i < (w * c); i++) {
		screen[i].c = ' ';
		screen[i].attr = 5;
	}

	offset = 0;
	update_cursor(0, 0);
}

void k_screen_char(char c)
{
	display_char(c);

	update_cursor(0, offset);
}

void k_screen_debug(char c)
{
	char *dst = (char *)(screen_mem + (80 * 24));
	*dst = c;
}

void k_screen_newline()
{
	offset += SCREEN_W - (offset % SCREEN_W);
}

void k_screen_string(char *src, int nsrc)
{
	int i;

	for(i = 0; i < nsrc; i++) {
		display_char(src[i]);
	}

	update_cursor(0, offset);
}

void k_screen_print(const char *src)
{
	int len = strlen(src);

	k_screen_string((char *)src, len);
}
