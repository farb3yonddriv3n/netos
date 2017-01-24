/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef PCI_H_
#define PCI_H_

#define PCI_CONFIG_ADDRESS	0x0CF8
#define PCI_CONFIG_DATA		0x0CFC
#define PCI_FUNCS_PER_BUS	0x100
#define PCI_BUS_MAX			0x100

struct pci_s {
	int bus;
	int dev;
	int dv_id;
};

unsigned int k_pci_read_reg(unsigned char bus, unsigned char device, unsigned char reg);
void k_pci_write_reg(unsigned char bus, unsigned char device, unsigned char reg, unsigned int data);

#endif
