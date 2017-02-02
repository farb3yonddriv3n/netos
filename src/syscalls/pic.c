/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 * http://wiki.osdev.org/PIC
 */
#include <netos.h>

/* This is issued to the PIC chips at the end of an IRQ-based interrupt routine
 * If the IRQ came from the Master PIC, it is sufficient to issue this command only to the Master PIC;
 * however if the IRQ came from the Slave PIC, it is necessary to issue the command to both PIC chips.
 */
void pic_eoi(unsigned char irq)
{
	if(irq >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
	}

	outb(PIC1_COMMAND, PIC_EOI);
}

/* To use the processor local APIC and the IOAPIC, disable the PIC first */
void pic_disable()
{
	outb(PIC2_DATA, PIC_EOI);
	outb(PIC2_DATA, PIC_EOI);
}

void pic_remap(int offset1, int offset2)
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void pic_irq_set_mask(unsigned char irq_line)
{
	unsigned short port;
	unsigned char value;

	if(irq_line < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq_line -= 8;
	}
	value = inb(port) | (1 << irq_line);
	outb(port, value);
}

void pic_irq_clear_mask(unsigned char irq_line)
{
	unsigned short port;
	unsigned char value;

	if(irq_line < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq_line -= 8;
	}
	value = inb(port) & ~(1 << irq_line);
	outb(port, value);
}
