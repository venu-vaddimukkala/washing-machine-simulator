/*
 * File:   main.c
 * Author: venuv
 *
 * Created on 25 June, 2025, 9:10 AM
 */


#include "main.h"

#pragma config WDTE = OFF

unsigned char operational_mode = WASHING_PROGRAM_SCREEN;
unsigned char reset_flag = RESET_WASH_PROGRAM_SCREEN;
static void init_config(void) {
    //to initialize clcd
    init_clcd();
    //to initialize digital key pad
    init_digital_keypad();
    //to initialize timer
    init_timer2();
    //to enable global interrupt and peripheral interrupt
    GIE = 1;
    PEIE = 1;
    BUZZER_DDR  = 0;
    FAN_DDR = 0;
    BUZZER = OFF;
    FAN    = OFF;
 }

void main(void) {
    init_config();
    unsigned char key ;
     clcd_print("Press key5 to",LINE1(1));
     clcd_print("Power On",LINE2(5));
     clcd_print("washing Machine",LINE3(1));
     while(read_digital_keypad(STATE) !=SW5){
         for(unsigned long int delay=3000;delay--;);
     }
     
     clear_screen();
     power_on_screen();
    
    while(1)
    {
       key = read_digital_keypad(STATE);
       /*To avoid bouncing effect*/
       for(unsigned int delay=3000;delay--;);
       if((key == LPSW4)  && (operational_mode) == WASHING_PROGRAM_SCREEN  ){
           operational_mode = WATER_LEVEL_SCREEN;
           reset_flag = RESET_WATER_LEVEL_SCREEN;
       }
       else if(key == LPSW4 && operational_mode == WATER_LEVEL_SCREEN ){
           operational_mode = START_STOP_SCREEN;
           clear_screen();
           clcd_print("Press Switch",LINE1(0));
           clcd_print("SW5: START",LINE2(0));
           clcd_print("SW6: STOP",LINE3(0));
           set_time();
       }
       else if(key == SW5 && operational_mode == PAUSE){
           operational_mode = START_SCREEN;
           TMR2ON = ON ;
           FAN = ON;
       }
       
       switch(operational_mode)
       {
           case WASHING_PROGRAM_SCREEN:
               washing_program_display(key);
               break;
           case WATER_LEVEL_SCREEN:
               water_level_screen(key);
               break;
           case START_STOP_SCREEN:
           {
               
               if(key == SW5)
               {
                   operational_mode = START_SCREEN;
                   reset_flag = RESET_START_SCREEN;
               }
               else if (key == SW6)
               {
                    operational_mode = WASHING_PROGRAM_SCREEN;
                    reset_flag= RESET_WASH_PROGRAM_SCREEN;
               }   
           }
               break;
           case START_SCREEN:
               //clear_screen();
               run_program(key);
               break;
       }
    }
    return;
}