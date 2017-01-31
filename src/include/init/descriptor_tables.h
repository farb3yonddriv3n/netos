/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
/*
 * descriptor_tables.h - Initialises the GDT and IDT, and defines the default
 * ISR and IRQ handler.
 * Based on code from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 */
#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

/*
 * This structure contains the value of one GDT entry. We use the attribute
 * 'packed' to tell the compiler not to change any of the alignment in the
 * structure.
 */
struct gdt_entry_s {
	unsigned short	ge_limit_lo;    /* The lower 16 bits of the limit. */
	unsigned short	ge_base_lo;     /* The lower 16 bits of the base. */
	unsigned char		ge_base_mi;     /* The next 8 bits of the base. */
	unsigned char		ge_access;      /* Access flags, determine what ring this segment can be used in. */
	unsigned char		ge_granularity;
	unsigned char		ge_base_hi;     /* The last 8 bits of the base. */
} __attribute__((packed)); 

struct gdt_ptr_s {
	unsigned short	gp_limit; /* The upper 16 bits of all selector limits. */
	unsigned int	gp_base;  /* The address of the first gdt_entry_t struct. */
} __attribute__((packed));


/* A struct describing an interrupt gate. */
struct idt_entry_s
{
	unsigned short	ie_base_lo; /* The lower 16 bits of the address to jump to when this interrupt fires. */
	unsigned short	ie_sel;     /* Kernel segment selector. */
	unsigned char		ie_always0; /* This must always be zero. */
	unsigned char		ie_flags;   /* More flags. See documentation. */
	unsigned short	ie_base_hi; /* The upper 16 bits of the address to jump to. */
} __attribute__((packed));

/* A struct describing a pointer to an array of interrupt handlers.
   This is in a format suitable for giving to 'lidt'. */
struct idt_ptr_s
{
	unsigned short	ip_limit;
	unsigned int	ip_base;  /* The address of the first element in our idt_entry_t array. */
} __attribute__((packed));


void	init_descriptor_tables(void);


/* These extern directives let us access the addresses of our ASM ISR
   handlers. */
extern void  isr0(void);
extern void  isr1(void);
extern void  isr2(void);
extern void  isr3(void);
extern void  isr4(void);
extern void  isr5(void);
extern void  isr6(void);
extern void  isr7(void);
extern void  isr8(void);
extern void  isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void  irq0(void);
extern void  irq1(void);
extern void  irq2(void);
extern void  irq3(void);
extern void  irq4(void);
extern void  irq5(void);
extern void  irq6(void);
extern void  irq7(void);
extern void  irq8(void);
extern void  irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

void idt_set_gate(unsigned char n, unsigned int base, unsigned short sel, unsigned char flags);

#endif /* ndef DESCRIPTOR_TABLES_H */
