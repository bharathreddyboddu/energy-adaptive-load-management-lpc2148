#include <LPC214x.h>
/* ---------------- LCD PINS ---------------- */
#define RS (1U << 16)
#define RW (1U << 17)
#define EN (1U << 18)
#define D4 (1U << 19)
#define D5 (1U << 20)
#define D6 (1U << 21)
#define D7 (1U << 22)
/* ---------------- RELAY PINS ---------------- */
#define RELAY1 (1U << 16)
#define RELAY2 (1U << 17)
#define RELAY3 (1U << 18)
#define RELAY4 (1U << 19)
/* ---------------- DELAY ---------------- */
void delay_us(unsigned int us)
{
    unsigned int i, j;
    for(i=0;i<us;i++)
        for(j=0;j<10;j++);
}
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i=0;i<ms;i++)
        for(j=0;j<6000;j++);
}
/* ---------------- LCD ---------------- */
void lcd_send_nibble(unsigned char nibble)
{
    IOCLR0 = D4|D5|D6|D7; //clears the data line
    if(nibble & 1) IOSET0 = D4;
    if(nibble & 2) IOSET0 = D5;
    if(nibble & 4) IOSET0 = D6;
    if(nibble & 8) IOSET0 = D7;
    IOSET0 = EN; //Data transmission is enabled 
    delay_us(50);
    IOCLR0 = EN;//Data transmission Is disabled
}
void lcd_cmd(unsigned char cmd)
{
    IOCLR0 = RS;
    IOCLR0 = RW;
    lcd_send_nibble(cmd>>4);
    lcd_send_nibble(cmd);
    delay_ms(2);
}
void lcd_data(unsigned char data)
{
    IOSET0 = RS;
    IOCLR0 = RW;
    lcd_send_nibble(data>>4);
    lcd_send_nibble(data);
    delay_ms(2);
}
void lcd_init(void)
{
    PINSEL1 &= ~0x00003FFF;
    IODIR0 |= RS|RW|EN|D4|D5|D6|D7;
    IOCLR0  = RS|RW|EN|D4|D5|D6|D7;
    delay_ms(20);
    lcd_send_nibble(0x03); delay_ms(5);
    lcd_send_nibble(0x03); delay_ms(5);
    lcd_send_nibble(0x03); delay_ms(5);
    lcd_send_nibble(0x02);
    lcd_cmd(0x28); // 4-bit, 2-line
    lcd_cmd(0x0C); // display ON
    lcd_cmd(0x06); // cursor right
    lcd_cmd(0x01); // clear screen
}
void lcd_string(char *s)
{
    while(*s) lcd_data(*s++);
}
void lcd_gotoxy(unsigned char pos)
{
    lcd_cmd(pos);
}
void lcd_clear(void)
{
    lcd_cmd(0x01);
    delay_ms(5);
}
void lcd_print_num(unsigned int num)
{
    lcd_data((num/1000)+'0');
    lcd_data(((num/100)%10)+'0');
    lcd_data(((num/10)%10)+'0');
    lcd_data((num%10)+'0');
}
void lcd_print_status(unsigned char level)
{
    lcd_gotoxy(0xC0);
    switch(level)
    {
        case 0: lcd_string("L1L2L3L4 ON    "); break;
        case 1: lcd_string("L4 OFF         "); break;
        case 2: lcd_string("L3L4 OFF       "); break;
        case 3: lcd_string("L2L3L4 OFF     "); break;
        default: lcd_string("UNKNOWN        ");
    }
}
/* ---------------- ADC ---------------- */
void ADC_Init(void)
{
    VPBDIV = 0; 
    // P0.28 -> AD0.1
    PINSEL1 &= ~(3U << 24);
    PINSEL1 |=  (1U << 24);
    // Select channel 1
    AD0CR = (1<<1) | (15<<8) | (1<<21);
}
unsigned int ADC_Read(void)
{
    unsigned int result;
    AD0CR |= (1<<24);
    while(!(AD0GDR & (1U<<31)));
    result = AD0GDR;
    AD0CR &= ~(7U<<24);
    return (result >> 6) & 0x3FF;
}
/* ---------------- RELAYS ---------------- */
void relays_init(void)
{
    PINSEL2 = 0;
    IO1DIR |= RELAY1|RELAY2|RELAY3|RELAY4;
    IO1SET = RELAY1|RELAY2|RELAY3|RELAY4;
}
void set_relays(unsigned char r1,unsigned char r2,unsigned char r3,unsigned char r4)
{
    if(r1) IO1CLR = RELAY1; else IO1SET = RELAY1;
    if(r2) IO1CLR = RELAY2; else IO1SET = RELAY2;
    if(r3) IO1CLR = RELAY3; else IO1SET = RELAY3;
    if(r4) IO1CLR = RELAY4; else IO1SET = RELAY4;
}
/* ---------------- MAIN ---------------- */
int main(void)
{
    unsigned int adc;
    unsigned char level;
    lcd_init();
    ADC_Init();
    relays_init();
    lcd_string("Initializing...");
    delay_ms(1500);
    lcd_clear();
	lcd_clear();
             lcd_string("GPIO P1.16-19");
	lcd_gotoxy(0xC0);
	lcd_string("LOADS ON");
	//delay_ms(200);
	set_relays(1,1,1,1);   // loads ON before ADC
	//delay_ms(500);
	lcd_clear();
	lcd_string("Computing ADC");
	//delay_ms(1000);
    adc = ADC_Read();
    /* RECTIFIED THRESHOLD LOGIC */
    if(adc < 530)
    {
        set_relays(1,1,1,1);   // low load: all ON
        level = 0;
    }
    else if(adc < 560)
    {
        set_relays(1,1,1,0);   // medium load: L4 OFF
        level = 1;
    }
    else if(adc < 590)
    {
        set_relays(1,1,0,0);   // high load: L3,L4 OFF
        level = 2;
    }
    else
    {
        set_relays(1,0,0,0);   // very high load: only L1 ON
        level = 3;
    }
    while(1)
    {
        lcd_gotoxy(0x80);
        lcd_string("ADC:");
        lcd_print_num(adc);
        lcd_print_status(level);
        delay_ms(300);
    }
}
