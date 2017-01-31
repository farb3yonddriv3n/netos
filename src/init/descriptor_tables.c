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

void isr_handler(struct registers_s regs)
{
	(void )regs;
	k_screen_print("recieved interrupt:");		//regs.int_no
}

void irq_handler(struct registers_s regs)
{
	(void )regs;
	k_screen_print("irq handler");

	/* Send reset signal to master. */
	/*
	   if (regs.int_no >= 40) {
	   outb(0xA0, 0x20);
	   }   
	   outb(0x20, 0x20);

	   if (interrupt_handlers[regs.int_no] != 0) {
	   isrhdl_t handler = interrupt_handlers[regs.int_no];
	   handler(regs);
	   }
	 */   
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
	int i;
	idt_ptr.ip_limit = sizeof(idt_entries) - 1;
	idt_ptr.ip_base  = (unsigned int)&idt_entries;

	(void)memset(&idt_entries, 0, sizeof(idt_entries));

	/* Remap the irq table */
	/*
	   outb(0x20, 0x11);
	   outb(0xA0, 0x11);
	   outb(0x21, 0x20);
	   outb(0xA1, 0x28);
	   outb(0x21, 0x04);
	   outb(0xA1, 0x02);
	   outb(0x21, 0x01);
	   outb(0xA1, 0x01);
	   outb(0x21, 0x0);
	   outb(0xA1, 0x0);
	 */
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

	for(i = 32; i < (unsigned char )(NELEM(idt_entries)); i++) {
		idt_set_gate(i,  (unsigned int)irq0, 0x08, 0x8E);
	}

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