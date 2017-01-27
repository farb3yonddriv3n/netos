/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef CLI_H_
#define CLI_H_

#define SZ(m_d) (sizeof(m_d) - 1)

#define CMD_EXIT 		"exit"
#define CMD_EXIT_N		SZ(CMD_EXIT)

#define CMD_VERSION 		"version"
#define CMD_VERSION_N		SZ(CMD_VERSION)

#define CMD_HELP 			"help"
#define CMD_HELP_N			SZ(CMD_HELP)

#define CMD_CLEAR 			"clear"
#define CMD_CLEAR_N			SZ(CMD_CLEAR)

#define CMD_ARP 			"arp"
#define CMD_ARP_N			SZ(CMD_ARP)

#define CMD_COMMANDS		"help, version"
#define CMD_COMMANDS_N		SZ(CMD_COMMANDS)

void k_cli(struct netos_s *src);

#endif
