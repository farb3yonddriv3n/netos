/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

#define WW(m_dst, m_src) (*(unsigned int *)m_dst = m_src)

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

void kernel_init(void)
{
	struct netos_s r;

	memset(&r, 0, sizeof(r));

	k_screen_init();

	init_descriptor_tables();

	network_init(&r);

	while(!flag_eq(r.flag, FN_EXIT)) {
		k_cli(&r);
	}

	k_screen_print("Turn off now");
	for(;;) __asm("hlt");
}
