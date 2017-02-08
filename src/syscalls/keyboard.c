/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

static struct keyboard_map_s keyboard_layout[KEY_STROKES] = {
	{0x10, 'q', 0},
	{0x11, 'w', 0},
	{0x12, 'e', 0},
	{0x13, 'r', 0},
	{0x14, 't', 0},
	{0x15, 'y', 0},
	{0x16, 'u', 0},
	{0x17, 'i', 0},
	{0x18, 'o', 0},
	{0x19, 'p', 0},
	{0x1e, 'a', 0},
	{0x1f, 's', 0},
	{0x20, 'd', 0},
	{0x21, 'f', 0},
	{0x22, 'g', 0},
	{0x23, 'h', 0},
	{0x24, 'j', 0},
	{0x25, 'k', 0},
	{0x26, 'l', 0},
	{0x2c, 'z', 0},
	{0x2d, 'x', 0},
	{0x2e, 'c', 0},
	{0x2f, 'v', 0},
	{0x30, 'b', 0},
	{0x31, 'n', 0},
	{0x32, 'm', 0},
	{0x1c, '\r', 0},
	{0x0e, 0x8, 0},
};

void k_keyboard_input()
{
	unsigned char c = inb(0x60);
	int i = 0;

	netos.input.down = 0;

	for(i = 0; i < KEY_STROKES; i++) {
		if(keyboard_layout[i].sc == c && !(flag_eq(keyboard_layout[i].flag, KEY_HELD))) {
			k_screen_debug(keyboard_layout[i].sc);
			netos.input.down = keyboard_layout[i].ascii;
			flag_set(keyboard_layout[i].flag, KEY_HELD);
			flag_unset(keyboard_layout[i].flag, KEY_UP);
			k_cli(&netos);
			break;
		} else if((keyboard_layout[i].sc | SC_BREAK) == c && flag_eq(keyboard_layout[i].flag, KEY_HELD)) {
			flag_unset(keyboard_layout[i].flag, KEY_HELD);
			flag_set(keyboard_layout[i].flag, KEY_UP);
			break;
		}
	}
}
