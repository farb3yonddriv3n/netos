/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

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
