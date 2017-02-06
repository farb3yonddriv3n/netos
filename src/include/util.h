/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef UTIL_H_
#define UTIL_H_

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

#define size(m_x) ((int )(sizeof(m_x) / sizeof(m_x[0])))

#define flag_eq(m_dst, m_flag) ((m_dst & m_flag) == m_flag)
#define flag_set(m_dst, m_flag) (m_dst |= m_flag)
#define flag_unset(m_dst, m_flag) (m_dst &= (~m_flag))

void k_create_gate(void *handler, unsigned int gate);
void k_pic_mask_clear(unsigned char irq);

#endif
