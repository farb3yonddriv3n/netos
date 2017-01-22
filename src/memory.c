#include <netos.h>

void *memset(void *s, char c, int n)
{
	int i;

	for(i = 0; i < n; i++) {
		*(char *)(s + i) = c;
	}

	return s;
}
