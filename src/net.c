/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

#define NIC_MAX	43

static const struct nic_map_s nic_device_vendor_id[NIC_MAX];

char k_eth_tx_buffer[1024 * 32];
char k_eth_rx_buffer[1024 * 32];

void __stack_chk_fail()
{
}

void build_arp(struct netos_s *os, struct arp_s *a)
{
	memcpy(a->srchw_s, os->net.mac, sizeof(os->net.mac));
	memset(a->dsthw_s, 0, sizeof(a->dsthw_s));
	a->ptype_s = 0x0806;

	swap_memory((void *)&a->ptype_s, sizeof(a->ptype_s));
	a->htype = 0x1;
	swap_memory((void *)&a->htype, sizeof(a->htype));

	a->ptype = 0x0800;
	swap_memory((void *)&a->ptype, sizeof(a->ptype));

	a->hlen = 6;
	a->plen = 4;

	a->opcode = 0x1;
	swap_memory((void *)&a->opcode, sizeof(a->opcode));

	memcpy(a->srchw, os->net.mac, sizeof(os->net.mac));
	memset(a->srcpr, 0, sizeof(a->srcpr));
	memset(a->dsthw, 0, sizeof(a->dsthw));
	memset(a->dstpr, 0, sizeof(a->dstpr));
}

static struct nic_s *cmp_device_vendor_id(const unsigned int dv_id)
{
	int i;

	for(i = 0; i < NIC_MAX; i++) {
		if(nic_device_vendor_id[i].dv_id == dv_id) {
			return nic_device_vendor_id[i].driver;
		}
	}

	return NULL;
}

static void browse_bus(struct pci_s *p)
{
	int reg;

	for(p->bus = 0; p->bus < PCI_BUS_MAX; p->bus++) {
		for(p->dev = 0; p->dev < PCI_FUNCS_PER_BUS; p->dev++) {
			reg = k_pci_read_reg(p->bus, p->dev, 2);
			if((unsigned short )(reg >> 16) == 0x0200) {
				p->dv_id = k_pci_read_reg(p->bus, p->dev, 0);
				return;
			}
		}
	}

	p->dv_id = -1;
}

void network_init(struct netos_s *os)
{
	struct pci_s p;
	struct nic_s *nic;

	browse_bus(&p);

	if(p.dv_id == -1) {
		k_screen_print("NIC not found");
		return;
	}

	nic = cmp_device_vendor_id(p.dv_id);
	if(nic == NULL) {
		k_screen_print("NIC not supported or not found");
		return;
	}

	os->net.driver = nic;

	nic->init(os, &p);
	k_screen_print("NIC initialized");

	nic->reset(os);
}

static const struct nic_map_s nic_device_vendor_id[NIC_MAX] = {
	// Realtek 816x/811x Gigabit Ethernet
	{0x8169FFFF, NULL},
	{0x816710EC, NULL},      // 8110SC/8169SC
	{0x816810EC, NULL},      // 8111/8168B
	{0x816910EC, NULL},      // 8169

	// Intel 8254x Gigabit Ethernet
	{0x8254FFFF, &nic_i8254x},
	{0x10008086, &nic_i8254x},      // 82542 (Fiber)
	{0x10018086, &nic_i8254x},      // 82543GC (Fiber)
	{0x10048086, &nic_i8254x},      // 82543GC (Copper)
	{0x10088086, &nic_i8254x},      // 82544EI (Copper)
	{0x10098086, &nic_i8254x},      // 82544EI (Fiber)
	{0x100A8086, &nic_i8254x},      // 82540EM
	{0x100C8086, &nic_i8254x},      // 82544GC (Copper)
	{0x100D8086, &nic_i8254x},      // 82544GC (LOM)
	{0x100E8086, &nic_i8254x},      // 82540EM
	{0x100F8086, &nic_i8254x},      // 82545EM (Copper)
	{0x10108086, &nic_i8254x},      // 82546EB (Copper)
	{0x10118086, &nic_i8254x},      // 82545EM (Fiber)
	{0x10128086, &nic_i8254x},      // 82546EB (Fiber)
	{0x10138086, &nic_i8254x},      // 82541EI
	{0x10148086, &nic_i8254x},      // 82541ER
	{0x10158086, &nic_i8254x},      // 82540EM (LOM)
	{0x10168086, &nic_i8254x},      // 82540EP (Mobile)
	{0x10178086, &nic_i8254x},      // 82540EP
	{0x10188086, &nic_i8254x},      // 82541EI
	{0x10198086, &nic_i8254x},      // 82547EI
	{0x101a8086, &nic_i8254x},      // 82547EI (Mobile)
	{0x101d8086, &nic_i8254x},      // 82546EB
	{0x101e8086, &nic_i8254x},      // 82540EP (Mobile)
	{0x10268086, &nic_i8254x},      // 82545GM
	{0x10278086, &nic_i8254x},      // 82545GM
	{0x10288086, &nic_i8254x},      // 82545GM
	{0x105b8086, &nic_i8254x},      // 82546GB (Copper)
	{0x10758086, &nic_i8254x},      // 82547GI
	{0x10768086, &nic_i8254x},      // 82541GI
	{0x10778086, &nic_i8254x},      // 82541GI
	{0x10788086, &nic_i8254x},      // 82541ER
	{0x10798086, &nic_i8254x},      // 82546GB
	{0x107a8086, &nic_i8254x},      // 82546GB
	{0x107b8086, &nic_i8254x},      // 82546GB
	{0x107c8086, &nic_i8254x},      // 82541PI
	{0x10b58086, &nic_i8254x},      // 82546GB (Copper)
	{0x11078086, &nic_i8254x},      // 82544EI
	{0x11128086, &nic_i8254x},      // 82544GC
};
