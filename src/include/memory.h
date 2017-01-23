#ifndef MEMORY_H_
#define MEMORY_H_

#define k_memcmp(m_src, m_nsrc, m_dst, m_ndst) (m_nsrc == m_ndst && memcmp(m_src, m_dst, m_ndst) == 0)

void *memset(void *s, char c, int n);
int memcmp(const void *dst, const void *src, int nsrc);
void swap_memory(char *dst, int ndst);
int int_to_str(char *dst, int ndst, int num);

#endif
