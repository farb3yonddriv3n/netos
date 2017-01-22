#include <netos.h>

void k_cli(struct netos_s *src)
{
	unsigned char c;

	c = k_keyboard_input(src);

	if(c > 0) {
		k_screen_char(c);
	}
}
