/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

void parse_input(struct netos_s *src)
{
	if(k_memcmp(src->input.s, src->input.n, CMD_VERSION, CMD_VERSION_N)) {
		k_screen_string(NETOS_VERSION, NETOS_VERSION_N);
	} else if(k_memcmp(src->input.s, src->input.n, CMD_HELP, CMD_HELP_N)) {
		k_screen_string(CMD_COMMANDS, CMD_COMMANDS_N);
	} else if(k_memcmp(src->input.s, src->input.n, CMD_ARP, CMD_ARP_N)) {
		struct arp_s a;
		build_arp(src, &a);
		src->net.driver->transmit(src, (void *)&a, sizeof(a));
		k_screen_print("ARP call");
	}

	k_screen_newline();
}

void k_cli(struct netos_s *src)
{
	unsigned char c;

	// display prompt
	if(!flag_eq(src->input.flag, KEY_PROMPT)) {
		char *prompt = "> ";
		k_screen_string(prompt, 2);
		flag_set(src->input.flag, KEY_PROMPT);
	}

	c = k_keyboard_input(src);

	if(c == '\r') {
		k_screen_clear(SCREEN_W, SCREEN_H);
		flag_unset(src->input.flag, KEY_PROMPT);
		//k_screen_string(src->input.s, src->input.n);
		parse_input(src);
		src->input.n = 0;
	} else if(c == 0x8) {
		src->input.n--;
	} else if(c > 0) {
		src->input.s[(src->input.n)++] = c;
		k_screen_char(c);
	}
}
