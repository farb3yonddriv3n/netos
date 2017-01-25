/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef UTIL_H_
#define UTIL_H_

struct netos_s {
	struct {
		unsigned int flag;
		char down;
		char s[256];
		int n;
	} input;
	struct {
		unsigned int base;
		unsigned int irq;
		char mac[6];
		struct nic_s *driver;
	} net;
};

inline static void outb(int portnum, int data)
{
	__asm__ __volatile__("outb %%al, %%dx" :: "a" (data),"d" (portnum));
}

inline static unsigned char inb(int port)
{
	unsigned char b = 0;

	__asm__ __volatile__("inb %%dx, %%al" : "=a" (b) : "d" (port));

	return b;
}

inline static void outdw(unsigned short portnum, unsigned int data)
{
	__asm__ __volatile__("out %%eax, %%dx" :: "a" (data),"d" (portnum));
}

inline static unsigned int indw(unsigned short port)
{
	unsigned int b = 0;

	__asm__ __volatile__("in %%dx, %%eax" : "=a" (b) : "d" (port));

	return b;
}


#define flag_eq(m_dst, m_flag) ((m_dst & m_flag) == m_flag)
#define flag_set(m_dst, m_flag) (m_dst |= m_flag)
#define flag_unset(m_dst, m_flag) (m_dst &= (~m_flag))

#endif
