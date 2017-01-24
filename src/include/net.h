/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef NET_H_
#define NET_H_

struct nic_s {
	const char *name;
	void (*init)(struct netos_s *os, struct pci_s *p);
	void (*reset)(struct netos_s *os);
	void (*transmit)(struct netos_s *os);
	void (*poll)(struct netos_s *os);
	void (*ack_init)(struct netos_s *os);
};

struct nic_map_s {
	unsigned int dv_id;
	struct nic_s *driver;
};

void network_init(struct netos_s *os);

extern struct nic_s nic_i8254x;

#endif
