#ifndef SYSTEM_H
#define SYSTEM_H

/* Function declarations for gdt */
void gdt_install();
void gdt_set_gate( int , unsigned long , unsigned long, unsigned char , unsigned char);
/* Function declarations for idt */
void idt_set_gate(unsigned char , unsigned long , unsigned short , unsigned char );
void idt_install();

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
/* Function declarations for isrs */
void isrs_install();
void fault_handler(struct regs );

/* Function declarations for irq */
void irq_install();
void irq_install_handler(int , void (*handler)(struct regs* ));
void irq_uninstall_handler(int);


#endif
