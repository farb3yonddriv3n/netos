#include <netos.h>

unsigned int k_pci_read_reg(unsigned char bus, unsigned char device, unsigned char reg)
{
	unsigned int address;

	address = (((bus << 16) | (device << 8) | (reg << 2)) & 0x00ffffff) | 0x80000000;

	outdw(PCI_CONFIG_ADDRESS, address);
	return indw(PCI_CONFIG_DATA);
}
