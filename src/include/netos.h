/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef NETOS_H_
#define NETOS_H_

#define NETOS_VERSION 		"netos0.1"
#define NETOS_VERSION_N 	(sizeof(NETOS_VERSION) - 1)

extern char k_eth_tx_buffer[1024 * 32];
extern char k_eth_rx_buffer[1024 * 32];

struct netos_s {
	struct {
		unsigned int flag;
		char down;
		char s[256];
		int n;
	} input;
	struct {
		unsigned int base;
		unsigned int irq;
		char mac[6];
		struct nic_s *driver;
		struct {
			char buf[2048];
			int len;
		} received;
	} net;

	unsigned int flag;
};

#include <util.h>
#include <types.h>
#include <memory.h>
#include <cli.h>
#include <screen.h>
#include <keyboard.h>
#include <pci.h>
#include <net.h>
#include <i8254x.h>

#define FN_EXIT		0x1

#endif
