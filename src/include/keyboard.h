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

unsigned char k_keyboard_input(struct netos_s *src);

#endif
