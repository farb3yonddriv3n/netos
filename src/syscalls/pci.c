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

void io_wait(void)
{
	/* Port 0x80 is used for 'checkpoints' during POST. */
	/* The Linux kernel seems to think it is free for use :-/ */
	asm volatile ( "outb %%al, $0x80" : : "a"(0) );
	/* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
}
