#include "system.h"
#include "screen.h"
main(){
	/* Switch to protected mode by
	 * calling install gdt_install */
	gdt_install();
	
	/* Pointer to video ram */
	char *p = 0xb8000;	
	/* Writing to video ram */
	print("Welcome to protected mode\n");
	/* Installing idt and corresponding isrs */
	idt_install();

	/* Writing to video ram */
	print("IDT configured successfully\n");
	
	/* Install irq for our custom interrupt
	 * handler registration 
	 */
	irq_install();
	/* Writing to video ram */
	print("IRQ installed\n");
	/*Enable interrupts*/
	 __asm__ __volatile__ ("sti");
	/*Install keyboard handler*/
	keyboard_install();
	/* endless loop,this will never return */
	while(1);
}
