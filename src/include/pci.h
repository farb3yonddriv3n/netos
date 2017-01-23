#ifndef PCI_H_
#define PCI_H_

#define PCI_CONFIG_ADDRESS	0x0CF8
#define PCI_CONFIG_DATA		0x0CFC

unsigned int k_pci_read_reg(unsigned char bus, unsigned char device, unsigned char reg);

#endif
