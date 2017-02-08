/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

struct netos_s netos;

void kernel_init(void)
{
	asm("sti;");

	memset(&netos, 0, sizeof(netos));

	k_screen_init();

	init_descriptor_tables();

	pic_irq_set_mask(1);	// keyboard

	network_init(&netos);

	while(!flag_eq(netos.flag, FN_EXIT));

	asm("cli;");
	k_screen_print("Turn off now");
	for(;;) __asm("hlt");
}
