/* =============================================================================
 * netOS -- 32-bit OS
 * Copyright (C) 2017 Filip Pancik -- see LICENSE
 * =============================================================================
 */
#ifndef TYPES_H_
#define TYPES_H_

#define NULL ((void *)0)

struct registers_s {
	unsigned int ds;                  // Data segment selector
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	unsigned int int_no, err_code;    // Interrupt number and error code (if applicable)
	unsigned int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
};

#endif
