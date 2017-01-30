/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 *
 * http://wiki.osdev.org/PCI
 * BareMetal-OS/os/drivers/pci.asm
 * =============================================================================
 */
#include <netos.h>

#define ADDRESS (address = (((bus << 16) | (device << 8) | (reg << 2)) & 0x00ffffff) | 0x80000000)

unsigned int k_pci_read_reg(unsigned char bus, unsigned char device, unsigned char reg)
{
	unsigned int address;

	ADDRESS;

	outdw(PCI_CONFIG_ADDRESS, address);
	return indw(PCI_CONFIG_DATA);
}

void k_pci_write_reg(unsigned char bus, unsigned char device, unsigned char reg, unsigned int data)
{
	unsigned int address;

	ADDRESS;

	outdw(PCI_CONFIG_ADDRESS, address);
	outdw(PCI_CONFIG_DATA, data);
}
