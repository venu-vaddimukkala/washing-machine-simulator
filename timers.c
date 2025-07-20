#include <xc.h>
#include "timers.h"

void init_timer2(void){
 
    PR2 = 250;
    TMR2IE = 1;
    TMR2ON = 0;
}
