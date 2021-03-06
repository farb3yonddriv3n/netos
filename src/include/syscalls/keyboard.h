/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEY_STROKES		28
#define SC_BREAK		0x80

struct keyboard_map_s {
	char sc;
	unsigned char ascii;
	unsigned int flag;
};

enum key_e {
	KEY_HELD =      (1<<1),
	KEY_UP =        (1<<2),
	KEY_PROMPT =    (1<<3),
};

void k_keyboard_input();

#endif
