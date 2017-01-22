#include <netos.h>

void kernel_init(void) {
	struct netos_s r;

	memset(&r, 0, sizeof(r));

	k_screen_clear(SCREEN_W, SCREEN_H);

	while(1 == 1) {
		k_cli(&r);
	}

	for(;;) __asm("hlt");
}
