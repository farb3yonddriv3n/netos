/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef SCREEN_H_
#define SCREEN_H_

#define SCREEN_W	80
#define SCREEN_H	25

#define SCREEN_ROW(m_s) (m_s / SCREEN_W)

#define SCREEN_MAX	((SCREEN_W * SCREEN_H) * 2)

struct viewport_s {
	char c;
	unsigned char attr;
};

struct screen_s {
	struct {
		int offset;
		struct viewport_s *port;
		int screen;
	} view;
};

void k_screen_init();
void k_screen_clear();
void k_screen_char(char c);
void k_screen_string(char *src, int nsrc, char newline);
void k_screen_debug(char c);
void k_screen_print(const char *src);
void k_screen_newline();
void k_screen_int(int n, char newline);

#endif
