// #include "timer.h"
// #include "../drivers/screen.h"
// #include "../drivers/ports.h"
// #include "isr.h"

// uint8_t tick = 0;

// static void timer_callback(registers_t regs) {
//     tick++;

//     if(tick >= 20){
//         pprint("Tick");
//         pprint("\n\r");
//         tick = 0;
//     }
// }

#include "timer.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "isr.h"

static uint32_t system_uptime = 0;  // Uptime in seconds

static void timer_callback(registers_t regs) {
    static uint32_t tick_count = 0;
    tick_count++;

    if (tick_count >= 20) {  // Assuming the timer fires 20 times a second
        system_uptime++;
        tick_count = 0;
    }
}

uint32_t get_system_uptime() {
    return system_uptime;
}

void init_timer(uint32_t freq) {

    //Check arguments
    if(freq == 0){
        pprint("Error: The frequency cannot be 0");
        return;
    }

    //Install the callback as the ISR for IRQ0
    register_interrupt_handler(IRQ0, timer_callback);
    
    //Get the correct divisor value
    uint16_t startValue = 0; 
    if(freq <= 18){
         startValue = HARDWARE_TIMER_FREQUENCY/freq;
    }
   

    //Split the divisor
    uint8_t low  = (uint8_t)(startValue & 0xFF);
    uint8_t high = (uint8_t)((startValue >> 8) & 0xFF);

    
    write_port_byte(0x43, 0x36); //Set the timer : Timer Channel0, Acces mode in low/high style, square wave generator, 16-bits binary 
    
    //Send the reload value
    write_port_byte(0x40, low);
    for(uint32_t i = 0;i<1000;i++) __asm__ __volatile__("nop");
    write_port_byte(0x40, high);
}