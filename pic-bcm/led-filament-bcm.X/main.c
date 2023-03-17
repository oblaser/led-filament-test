
#define USE_INTOSC (0)

#if USE_INTOSC
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#else
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#endif
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB2      // CCP1 Pin Selection bit (CCP1 function on RB2)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <stddef.h>
#include <stdint.h>

#include <xc.h>
#include <pic16f819.h>



#define LED_R PORTAbits.RA3
#define LED_G PORTAbits.RA2
#define LED_B PORTAbits.RA1
#define LED_W PORTAbits.RA0

#define BTN_0 PORTAbits.RA4



uint8_t led_r_value = 0;
uint8_t led_g_value = 0;
uint8_t led_b_value = 0;
uint8_t led_w_value = 0;

uint16_t tmr_led = 0;

void HW_init();
void LED_bcm();
//int UTIL_pow(int b, int e);



void main()
{
    HW_init();
    GIE = 1;
    
    led_r_value = 0;
    led_g_value = 5;
    led_b_value = 10;
    led_w_value = 0;
    
    while(1)
    {
        LED_bcm();
        
        if(tmr_led == 0)
        {
            tmr_led = 2;
            
            led_r_value += 2;
        }
    }
}

void __interrupt() global_isr()
{
    // ~10ms (9.984ms)
    if(TMR0IE && TMR0IF)
    {
        if(tmr_led) --tmr_led;
        
        TMR0 = 100;
        TMR0IF = 0;
    }
}



void HW_init()
{
#if USE_INTOSC
    OSCCON      = 0b01110000; // 8MHz
#else
    //nop; XTAL = 16MHz
#endif
    
    PORTA       = 0x00;
    ADCON1      = 0b00000110; // all pins are digital
    TRISA       = 0b11110000; // RA0..3 are outputs
    
#if USE_INTOSC
    OPTION_REG  = 0b11010110; // CS = Fosc/4 PS = 1:128
#else
    OPTION_REG  = 0b11010111; // CS = Fosc/4 PS = 1:256
#endif
    
    INTCON      = 0b00100000;
}

const int bcm_bit_times[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void LED_bcm()
{
    static int pos = 0;
    static int cnt = 0;
    
    if(cnt == 0)
    {
        LED_R = (led_r_value & (1 << pos)) >> pos;
        LED_G = (led_g_value & (1 << pos)) >> pos;
        LED_B = (led_b_value & (1 << pos)) >> pos;
        LED_W = (led_w_value & (1 << pos)) >> pos;
        
        //cnt = UTIL_pow(2, pos);
        cnt = bcm_bit_times[pos];
        if(pos < 7) ++pos;
        else pos = 0;
    }
    
    --cnt;
}

//int UTIL_pow(int b, int e)
//{
//    int r = 1;
//    
//    for(int i = 0; i < e; ++i)
//    {
//        r *= b;
//    }
//    
//    return r;
//}
