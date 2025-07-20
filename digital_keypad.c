#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char long_press = 1;
    unsigned char key = KEYPAD_PORT & INPUT_LINES;
    static unsigned char pre_key;

    if ((key != ALL_RELEASED) && once) {

        once = 0;
        long_press = 0;
        pre_key = key;

    } else if (key == ALL_RELEASED && !once) {
        once = 1;
        if (long_press < 30)
        return pre_key;
    }
    else if(!once && long_press <= 30)
         long_press++;

    else if(!once && long_press == 31 && key == SW4) {
        long_press++;
        return LPSW4;
    }
    
   /* static unsigned char once = 1;
    
    if (mode == LEVEL_DETECTION)
    {
        return KEYPAD_PORT & INPUT_LINES;
    }
    else
    {
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            
            return KEYPAD_PORT & INPUT_LINES;
        }
        else if ((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED)
        {
            once = 1;
        }
    }*/
    
    
    return ALL_RELEASED;
}
