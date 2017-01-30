/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef NET_H_
#define NET_H_

#define MAC_LEN		6
#define IP4_LEN		4

struct nic_s {
	const char *name;
	void (*init)(struct netos_s *os, struct pci_s *p);
	void (*reset)(struct netos_s *os);
	void (*transmit)(struct netos_s *os, void *data, unsigned short n);
	void (*poll)(struct netos_s *os);
	int (*ack_init)(struct netos_s *os);
};

struct nic_map_s {
	unsigned int dv_id;
	struct nic_s *driver;
};

struct arp_s {
	unsigned char  	dsthw_s[MAC_LEN]; // Source hardware address - hlen bytes (see above)
	unsigned char  	srchw_s[MAC_LEN]; // Source hardware address - hlen bytes (see above)
	unsigned short 	ptype_s;

	unsigned short 	htype; // Hardware type
	unsigned short 	ptype; // Protocol type
	unsigned char  	hlen; // Hardware address length (Ethernet = 6)
	unsigned char  	plen; // Protocol address length (IPv4 = 4)
	unsigned short  opcode;
	unsigned char  	srchw[MAC_LEN]; // Source hardware address - hlen bytes (see above)
	unsigned char 	srcpr[IP4_LEN]; // Source protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
	unsigned char  	dsthw[MAC_LEN]; // Destination hardware address - hlen bytes (see above)
	unsigned char 	dstpr[IP4_LEN]; // Destination protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
};

void network_init(struct netos_s *os);

void build_arp(struct netos_s *os, struct arp_s *a);

extern struct nic_s nic_i8254x;

#endif
