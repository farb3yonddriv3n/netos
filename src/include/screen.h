/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef SCREEN_H_
#define SCREEN_H_

#define SCREEN_W	80
#define SCREEN_H	25

struct screen_region_s {
	char c;
	unsigned char attr;
};

void k_screen_clear(const int w, const int c);
void k_screen_char(char c);
void k_screen_string(char *src, int nsrc);
void k_screen_debug(char c);
void k_screen_print(const char *src);

#endif
