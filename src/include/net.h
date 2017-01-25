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
	void (*transmit)(struct netos_s *os, char *data, int n);
	void (*poll)(struct netos_s *os);
	void (*ack_init)(struct netos_s *os);
};

struct nic_map_s {
	unsigned int dv_id;
	struct nic_s *driver;
};

struct arp_s {
	unsigned short 	htype; // Hardware type
	unsigned short 	ptype; // Protocol type
	unsigned char  	hlen; // Hardware address length (Ethernet = 6)
	unsigned char  	plen; // Protocol address length (IPv4 = 4)
	unsigned short 	opcode; // ARP Operation Code
	unsigned char  	srchw[6]; // Source hardware address - hlen bytes (see above)
	unsigned char 	srcpr[4]; // Source protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
	unsigned char  	dsthw[6]; // Destination hardware address - hlen bytes (see above)
	unsigned char 	dstpr[4]; // Destination protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
};

void network_init(struct netos_s *os);

extern struct nic_s nic_i8254x;

#endif
