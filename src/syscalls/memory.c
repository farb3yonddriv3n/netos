/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#include <netos.h>

void swap_memory(char *dst, int ndst)
{
	int i, j;

	for(i = 0, j = ndst - 1; (i < (ndst / 2) && j > 0); i++, j--) {
		dst[j] ^= dst[i];
		dst[i] ^= dst[j];
		dst[j] ^= dst[i];
	}
}

void *memcpy(void *dst, const void *src, int nsrc)
{
	int i;
	for(i = 0; i < nsrc; i++) {
		((char *)(dst))[i] = ((char *)(src))[i];
	}

	return dst;
}

int int_to_str(char *dst, int ndst, int num)
{
	int i = 0;
	unsigned char r;

	for(i = 0; (num > 0 && ndst > 0); i++, ndst--) {
		r = num % 10;
		num /= 10;
		dst[i] = r + 0x30;
	}

	swap_memory(dst, i);

	return i;
}

void *memset(void *s, char c, int n)
{
	int i;

	for(i = 0; i < n; i++) {
		*(char *)(s + i) = c;
	}

	return s;
}

int memcmp(const void *dst, const void *src, int nsrc)
{
	int i;
	int r;

	for(i = 0; i < nsrc; i++) {
		r = ((char *)dst)[i] - ((char *)src)[i];
		if(r != 0) {
			return r;
		}
	}

	return 0;
}

int strlen(const char *src)
{
	char *end;

	for(end = (char *)src; *end != 0; end++);

	return (end - src);
}
