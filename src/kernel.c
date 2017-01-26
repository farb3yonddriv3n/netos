/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

void kernel_init(void) {
	struct netos_s r;

	memset(&r, 0, sizeof(r));

	k_screen_init();

	network_init(&r);

	while(1 == 1) {
		k_cli(&r);
	}

	for(;;) __asm("hlt");
}
