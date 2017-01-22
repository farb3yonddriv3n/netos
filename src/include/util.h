#ifndef UTIL_H_
#define UTIL_H_

struct netos_s {
	struct {
		unsigned int flag;
		char down;
		char s[256];
		int n;
	} input;
};

inline static void outb (int portnum, int data)
{
	__asm__ __volatile__("outb %%al, %%dx" :: "a" (data),"d" (portnum));
}

inline static unsigned char inb(int port)
{
	unsigned char b = 0;

	__asm__ __volatile__("inb %%dx, %%al" : "=a" (b) : "d" (port));

	return b;
}

#define flag_eq(m_dst, m_flag) ((m_dst & m_flag) == m_flag)
#define flag_set(m_dst, m_flag) (m_dst |= m_flag)
#define flag_unset(m_dst, m_flag) (m_dst &= (~m_flag))

#endif
