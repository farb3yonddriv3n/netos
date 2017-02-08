/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
/*
 * descriptor_tables.c - Initialises the GDT and IDT, and defines the default
 * ISR and IRQ handler.
 * Based on code from Bran's kernel development tutorials.
 * Rewritten for JamesM's kernel development tutorials.
 */
#include <netos.h>

#define NELEM(x)	(sizeof((x)) / sizeof((x)[0]))

extern void	gdt_flush(unsigned int gdt_p);
static void	init_gdt(void);
static void	gdt_set_gate(unsigned int n, unsigned int base, unsigned int limit,
		unsigned char access, unsigned char gran);

extern void	idt_flush(unsigned int idt_p);
static void	init_idt(void);
void	idt_set_gate(unsigned char n, unsigned int base, unsigned short sel,
		unsigned char flags);

static struct gdt_entry_s		gdt_entries[5];
static struct gdt_ptr_s		gdt_ptr;
static struct idt_entry_s		idt_entries[256];
static struct idt_ptr_s		idt_ptr;

typedef void (*isrhdl_t)(struct registers_s);
static isrhdl_t interrupt_handlers[256];

/* This gets called from our ASM interrupt handler stub. */
void isr_handler(struct registers_s regs)
{
	if (interrupt_handlers[regs.int_no] != NULL) {
		isrhdl_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	} else {
		k_screen_print("unhandled interrupt");
		k_screen_int(regs.int_no, 1);
	}
}

/* This gets called from our ASM interrupt handler stub. */
void irq_handler(struct registers_s regs)
{
	switch(regs.int_no - 0x20) {
		case 1: {
			k_keyboard_input();
		}
		break;
		default: {
			k_screen_print("default");
		}
		break;
	}

	pic_eoi(regs.int_no - 0x20);
}

void register_interrupt_handler(unsigned int n, isrhdl_t handler)
{
	if(n > NELEM(interrupt_handlers)) {
		k_screen_print("Bad interrupt handler index.");
	}
	interrupt_handlers[n] = handler;
}

void init_descriptor_tables(void)
{
	init_gdt();
	init_idt();
}

static void init_gdt(void)
{
	gdt_ptr.gp_limit = sizeof(gdt_entries) - 1;
	gdt_ptr.gp_base  = (unsigned int)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                /* Null segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */

	gdt_flush((unsigned int)&gdt_ptr);
}

static void gdt_set_gate(unsigned int n, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
	if(n >= NELEM(gdt_entries)) {
		k_screen_print("bad gd entries index");
		return;
	}

	gdt_entries[n].ge_base_lo = (base & 0xFFFF);
	gdt_entries[n].ge_base_mi = (base >> 16) & 0xFF;
	gdt_entries[n].ge_base_hi = (base >> 24) & 0xFF;

	gdt_entries[n].ge_limit_lo    = (limit & 0xFFFF);
	gdt_entries[n].ge_granularity = (limit >> 16) & 0x0F;

	gdt_entries[n].ge_granularity |= gran & 0xF0;
	gdt_entries[n].ge_access       = access;
}

static void init_idt(void)
{
	idt_ptr.ip_limit = sizeof(idt_entries) - 1;
	idt_ptr.ip_base  = (unsigned int)&idt_entries;

	(void)memset(&idt_entries, 0, sizeof(idt_entries));

	/* Remap the irq table */
	pic_remap(0x20, 0x28);

	idt_set_gate( 0,  (unsigned int)isr0, 0x08, 0x8E);
	idt_set_gate( 1,  (unsigned int)isr1, 0x08, 0x8E);
	idt_set_gate( 2,  (unsigned int)isr2, 0x08, 0x8E);
	idt_set_gate( 3,  (unsigned int)isr3, 0x08, 0x8E);
	idt_set_gate( 4,  (unsigned int)isr4, 0x08, 0x8E);
	idt_set_gate( 5,  (unsigned int)isr5, 0x08, 0x8E);
	idt_set_gate( 6,  (unsigned int)isr6, 0x08, 0x8E);
	idt_set_gate( 7,  (unsigned int)isr7, 0x08, 0x8E);
	idt_set_gate( 8,  (unsigned int)isr8, 0x08, 0x8E);
	idt_set_gate( 9,  (unsigned int)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned int)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned int)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned int)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned int)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned int)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned int)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned int)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned int)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned int)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned int)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned int)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned int)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned int)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned int)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned int)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned int)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned int)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned int)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned int)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned int)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned int)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned int)isr31, 0x08, 0x8E);
	idt_set_gate(32,  (unsigned int)irq0, 0x08, 0x8E);
	idt_set_gate(33,  (unsigned int)irq1, 0x08, 0x8E);
	idt_set_gate(34,  (unsigned int)irq2, 0x08, 0x8E);
	idt_set_gate(35,  (unsigned int)irq3, 0x08, 0x8E);
	idt_set_gate(36,  (unsigned int)irq4, 0x08, 0x8E);
	idt_set_gate(37,  (unsigned int)irq5, 0x08, 0x8E);
	idt_set_gate(38,  (unsigned int)irq6, 0x08, 0x8E);
	idt_set_gate(39,  (unsigned int)irq7, 0x08, 0x8E);
	idt_set_gate(40,  (unsigned int)irq8, 0x08, 0x8E);
	idt_set_gate(41,  (unsigned int)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned int)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned int)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned int)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned int)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned int)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned int)irq15, 0x08, 0x8E);

	idt_flush((unsigned int)&idt_ptr);
}

void idt_set_gate(unsigned char n, unsigned int base, unsigned short sel, unsigned char flags)
{
	idt_entries[n].ie_base_lo = base & 0xFFFF;
	idt_entries[n].ie_base_hi = (base >> 16) & 0xFFFF;

	idt_entries[n].ie_sel     = sel;
	idt_entries[n].ie_always0 = 0;
	/* We must uncomment the OR below when we get to using user-mode. It
	   sets the interrupt gate's privilege level to 3. */
	idt_entries[n].ie_flags = flags /* | 0x60 */;
}
