/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

#define WW(m_dst, m_src) (*(unsigned short *)m_dst = m_src)

void k_pic_mask_clear(unsigned char irq)
{
	unsigned short dx;
	unsigned char lirq = irq;
	unsigned short ax;

	if(lirq < 8) {
		dx = 0x21;
	} else {
		dx = 0xA1;
		lirq -= 8;
	}

	ax = inb(dx);
	ax &= ~lirq;
	outb(dx, ax);
}

void k_create_gate(void *handler, unsigned int gate)
{
	unsigned int h;

	h = (unsigned int )handler;

	gate <<= 4;
	WW(gate, (unsigned short )h);
	gate += 4;
	h >>= 16;
	WW(gate, (unsigned short )h);
}

void kernel_init(void)
{
	struct netos_s r;

	memset(&r, 0, sizeof(r));

	k_screen_init();

	network_init(&r);

	while(!flag_eq(r.flag, FN_EXIT)) {
		k_cli(&r);
	}

	k_screen_print("Turn off now");
	for(;;) __asm("hlt");
}
