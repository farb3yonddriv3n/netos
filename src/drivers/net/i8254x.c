/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 *
 * http://wiki.osdev.org/Intel_8254x
 * BareMetal-OS/os/drivers/net/i8254x.asm
 * =============================================================================
 */
#include <netos.h>

static void i8254x_init(struct netos_s *os, struct pci_s *p);
static void i8254x_reset(struct netos_s *os);
static void i8254x_transmit(struct netos_s *os);
static void i8254x_poll(struct netos_s *os);
static void i8254x_ack_init(struct netos_s *os);

struct nic_s nic_i8254x = {
	"I8254X",
	i8254x_init,
	i8254x_reset,
	i8254x_transmit,
	i8254x_poll,
	i8254x_ack_init,
};

static void i8254x_init(struct netos_s *os, struct pci_s *p)
{
	int i;
	int mac;
	unsigned int status_command;

	// get base I/O address and clear 4 low bits
	os->net.base = (k_pci_read_reg(p->bus, p->dev, 0x4) & 0xFFFFFFF0);

	// get IRQ
	os->net.irq = k_pci_read_reg(p->bus, p->dev, 0x0F);

	// enable pci bus mastering
	status_command = k_pci_read_reg(p->bus, p->dev, 0x1);

	// bts status_command, 2
	status_command |= 0x4;
	k_pci_write_reg(p->bus, p->dev, 0x1, status_command);

	// get MAC
#define MAC(m_start, m_offset, m_region)\
	mac = *(int *)((void *)(os->net.base) + m_offset);\
	for(i = m_start; i < m_region; os->net.mac[i] = (char )mac, i++, mac >>= 8);
	MAC(0, 0x5400, 4);
	MAC(4, 0x5404, 6);
}

static void i8254x_transmit(struct netos_s *os)
{
}

static void i8254x_poll(struct netos_s *os)
{
}

static void i8254x_ack_init(struct netos_s *os)
{
}

static void i8254x_reset(struct netos_s *os)
{

#define R(m_offset, m_data) (*((int *)(os->net.base + m_offset)) = (m_data))

	// disable interrupts
	R(I8254X_REG_IMC, 0xFFFFFFFF);

	// disable interrupt throttling logic
	R(I8254X_REG_ITR, 0x0);

	// set RX buffer size to 48KB(TX buffer is calculated as 64 - RX)
	R(I8254X_REG_PBA, 0x00000030);

	// TXCW: set ANE, TxConfigWord (Half/Full duplex, Next Page Request)
	R(I8254X_REG_TXCW, 0x80008060);

	// CTRL: clear LRST, set SLU and ASDE, clear RSTPHY, VME, and ILOS
	*((unsigned int *)(os->net.base + I8254X_REG_CTRL)) &= 0x3fffff77;

	// MTA reset
	memset((void *)(os->net.base + 0x5200), 0x0, (4 * sizeof(int)));

	// Receive Descriptor Base Address Low
	R(I8254X_REG_RDBAL, (unsigned int)k_eth_rx_buffer);

	// Receive Descriptor Length
	R(I8254X_REG_RDLEN, 32 * 16);

	// Receive Descriptor Head
	R(I8254X_REG_RDH, 0x0);

	// Receive Descriptor Tail
	R(I8254X_REG_RDT, 0x1);

	// Receiver Enable, Store Bad Packets, Broadcast Accept Mode, Strip Ethernet CRC from incoming packet
	R(I8254X_REG_RCTL, 0x04008006);

	*(int *)(k_eth_rx_buffer) = 0x1c9000;

	// Transmit Descriptor Base Address Low
	R(I8254X_REG_TDBAL, (unsigned int)k_eth_tx_buffer);

	// Transmit Descriptor Length
	R(I8254X_REG_TDLEN, 32 * 16);

	// Transmit Descriptor Head
	R(I8254X_REG_TDH, 0x0);

	// Transmit Descriptor Tail
	R(I8254X_REG_TDT, 0x0);

	// Enabled, Pad Short Packets, 15 retries, 64-byte COLD, Re-transmit on Late Collision
	R(I8254X_REG_TCTL, 0x010400FA);

	// Transmit IPG Register
	R(I8254X_REG_TIPG, 0x0060200A);

	// Clear the Receive Delay Timer Register
	R(I8254X_REG_RDTR, 0x0);
	// Clear the Receive Interrupt Absolute Delay Timer
	R(I8254X_REG_RADV, 0x0);
	// Clear the Receive Small Packet Detect Interrupt
	R(I8254X_REG_RSRPD,  0x0);

	// Enable interrupt types
	R(I8254X_REG_IMS, 0x1FFFF);
}
