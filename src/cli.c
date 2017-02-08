/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

struct cli_map_s {
	const char *cmd;
	int ncmd;
	void (*func)(struct netos_s *s);
};

static void cli_version(struct netos_s *src);
static void cli_help(struct netos_s *src);
static void cli_arp(struct netos_s *src);
static void cli_clear(struct netos_s *src);
static void cli_exit(struct netos_s *src);

static struct cli_map_s cli_map[] = {
	{CMD_VERSION, CMD_VERSION_N, cli_version},
	{CMD_HELP, CMD_HELP_N, cli_help},
	{CMD_ARP, CMD_ARP_N, cli_arp},
	{CMD_CLEAR, CMD_CLEAR_N, cli_clear},
	{CMD_EXIT, CMD_EXIT_N, cli_exit}
};

static void cli_version(struct netos_s *src)
{
	(void )src;
	k_screen_string(NETOS_VERSION, NETOS_VERSION_N, 1);
}

static void cli_help(struct netos_s *src)
{
	(void )src;
	k_screen_string(CMD_COMMANDS, CMD_COMMANDS_N, 1);
}

static void cli_arp(struct netos_s *src)
{
	struct arp_s a;
	build_arp(src, &a);
	if(src->net.driver) {
		src->net.driver->transmit(src, (void *)&a, sizeof(a));
		k_screen_print("ARP dummy call");
	} else {
		k_screen_print("nic not initialized");
	}
}

static void cli_clear(struct netos_s *src)
{
	(void )src;
	k_screen_clear();
}

static void cli_exit(struct netos_s *src)
{
	flag_set(src->flag, FN_EXIT);
}

void parse_input(struct netos_s *src)
{
	k_screen_newline();

	if(src->input.n == 0) {
		return;
	}

	int i;

	for(i = 0; i < size(cli_map); i++) {
		if(k_memcmp(src->input.s, src->input.n, cli_map[i].cmd, cli_map[i].ncmd)) {
			cli_map[i].func(src);
			return;
		}
	}

	k_screen_print("command not found");
}

void k_cli(struct netos_s *src)
{
	unsigned char c;

	// display prompt
	if(!flag_eq(src->input.flag, KEY_PROMPT)) {
		k_screen_string("> ", 2, 0);
		flag_set(src->input.flag, KEY_PROMPT);
	}

	c = src->input.down;

	if(c == '\r') {
		flag_unset(src->input.flag, KEY_PROMPT);
		parse_input(src);
		src->input.n = 0;
	} else if(c == 0x8) {
		src->input.n--;
	} else if(c > 0) {
		src->input.s[(src->input.n)++] = c;
		k_screen_char(c);
	}
}
