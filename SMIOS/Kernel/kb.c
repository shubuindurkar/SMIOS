#include <system.h>
char kbdusnsh[128] =
{
    -1,  27, '1', '2', '3', '4', '5', '6', '7', '8',   /* 9 */
  '9', '0', '-', '=', '\b', '\t',
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',      /* Enter key */
    0,         /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   /* 39 */
'\'', '`',   0,      /* Left shift */
'\\', 'z', 'x', 'c', 'v', 'b', 'n',         /* 49 */
  'm', ',', '.', '/',   0,               /* Right shift */
  '*',
    0,   /* Alt */
  ' ',   /* Space bar */
    58,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   /* < ... F10 */
    0,   /* 69 - Num lock*/
    0,   /* Scroll Lock */
    0,   /* Home key */
    0,   /* Up Arrow */
    0,   /* Page Up */
  '-',
    0,   /* Left Arrow */
    0,
    0,   /* Right Arrow */
  '+',
    0,   /* 79 - End key*/
    0,   /* Down Arrow */
    0,   /* Page Down */
    0,   /* Insert Key */
    0,   /* Delete Key */
    0,   0,   0,
    0,   /* F11 Key */
    0,   /* F12 Key */
    0,   /* All other keys are undefined */
   
};

char kbdusysh[128] =
{ 
0,  0, '!', '@', '#', '$', '%', '^', '&', '*',   /* 9 */
  '(', ')', '_', '+', '\b', '\t',
  'Q', 'W', 'E', 'R',
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',      /* Enter key */
    0,         /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',   /* 39 */
'"', '~',   0,      /* Left shift */
'|', 'Z', 'X', 'C', 'V', 'B', 'N',         /* 49 */
  'M', '<', '>', '?',   0,               /* Right shift */
  0,
    0,   /* Alt */
  ' ',   /* Space bar */
    58,   /* Caps lock */
    0,   /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   /* < ... F10 */
    0,   /* 69 - Num lock*/
    0,   /* Scroll Lock */
    0,   /* Home key */
    0,   /* Up Arrow */
    0,   /* Page Up */
  '-',
    0,   /* Left Arrow */
    0,
    0,   /* Right Arrow */
  '+',
    0,   /* 79 - End key*/
    0,   /* Down Arrow */
    0,   /* Page Down */
    0,   /* Insert Key */
    0,   /* Delete Key */
    0,   0,   0,
    0,   /* F11 Key */
    0,   /* F12 Key */
    0,   /* All other keys are undefined */
};

 unsigned shift_state;
 unsigned capslock_state;
 unsigned numlock_state;
/* Numeric keypad  handler */
unsigned char numeric_keypad(unsigned char scancode){
	switch(scancode){
		case 0x47:printch('7');break;
		case 0x48:printch('8');break;
		case 0x49:printch('9');break;
		case 0x4B:printch('4');break;
		case 0x4C:printch('5');break;
		case 0x4D:printch('6');break;
		case 0x4F:printch('1');break;
		case 0x50:printch('2');break;
		case 0x51:printch('3');break;
		case 0x52:printch('0');break;	
		case 0x53:printch('.');break;
 	}
	return;
}
/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    char asciicode;
    unsigned char scancode;
    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
	//if((scancode == 42) || (scancode == 54)){
		if(scancode == 0x2A || scancode == 0x36){	
			shift_state = 1;
			return;
		}
		if(scancode == 0xAA || scancode == 0xB6){
			shift_state = 0;
			return;
		}
/* handle if it is capslock scancode*/
		if(scancode == 0x3A){	
			if(capslock_state)
				capslock_state = 0;
			else
				capslock_state = 1;
			return;
		}
		if(scancode == 0xBA){
			/*no operation*/			
			return;
		}
/* handle if it is numlock scancode*/
		if(scancode == 0x45){	
			if(numlock_state)
				numlock_state = 0;
			else
				numlock_state = 1;
			return;
		}
		if(scancode == 0xC5){
			/*no operation*/			
			return;
		}
/* handle keypad strike */
		if(scancode == 0x47 ||scancode == 0x48 ||scancode == 0x49
 ||scancode == 0x4B ||scancode == 0x4C ||scancode == 0x4D ||scancode == 0x4F ||
scancode == 0x50 ||scancode == 0x51 ||scancode == 0x52 ){
			if(!numlock_state)
				numeric_keypad(scancode);
			return;
		}
	//}
	else if ((scancode & 0x80));
	else{
		if(shift_state || capslock_state){
			asciicode = kbdusysh[scancode];
			printch(asciicode);
		}
		
		else{
			asciicode = kbdusnsh[scancode];
			printch(asciicode);
		}

	}
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}


