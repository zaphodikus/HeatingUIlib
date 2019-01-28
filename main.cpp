/* */

#include <events/mbed_events.h>
#include <mbed.h>



// https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/
// UART pins on Discovery DISCO_L475VG_IOT01A
// PC_1 serial1_TX
// PC_0 serial1_RX

// pwm pins
// Red PA_7 pwm1
// Grn   
// Blu
//Serial ser_lcd(PC_1,PC_0);
Serial ser_lcd(PC_4, PC_5, 9600);

Serial pc(USBTX, USBRX);
static DigitalOut led1(LED1, 1);
DigitalOut led2(PB_14,0);

void selectLineTwo();
void selectLineOne();

void select_line(uint8_t line=0){
   ser_lcd.putc(0xFE);   //command flag
   ser_lcd.putc(128+(line*64));    //position
}

void printline1(char const * msg){
  int i=0;
  char *p = (char*)msg;
  select_line(0);
  while ((i < 16) && (*p)) {pc.printf("[%c]",*p); ser_lcd.putc(*(p++)); i++; }
  while (i < 16 ) { ser_lcd.putc(' '); i++;}
  pc.printf("<<==LCD data '%s' \r\n", msg);
}


void printline2(const char * msg){
  int i=0;
  char *p = (char*)msg;

  pc.printf("LEN: %d \r\n", strlen(msg));

  //select_line(1);
  selectLineTwo();
  while ((i < 16) && (*p)) {pc.printf("[%c]",*p); ser_lcd.putc(*(p++)); i++; }
  while (i < 16 ) { ser_lcd.putc(' '); i++;}
  pc.printf("<<==LCD data '%s' \r\n", msg);
}

void selectLineOne(){  //puts the cursor at line 0 char 0.
  //  ser_lcd.putc(0xFE);   //command flag
  //  ser_lcd.putc(128+0);    //position
select_line(0);
}

void selectLineTwo(){  //puts the cursor at line 0 char 0.
    ser_lcd.putc(0xFE);   //command flag
    ser_lcd.putc(128+64);    //position
select_line(1);
}

void clearLCD(){
   ser_lcd.putc(0xFE);   //command flag
   ser_lcd.putc(0x01);   //clear command.
}

void backlightOn(uint8_t level = 10){  //turns on the backlight
    ser_lcd.putc(0x7C);   //command flag for backlight stuff
    ser_lcd.putc(127 + (level & 0x1F));    //light level.
}

class SerLCD {
public:
   SerLCD(Serial & port) : _port(port) {};

   void write(const char *buffer);
   void putc(uint8_t ch);
   void putc(char ch)
   {
      putc((uint8_t)ch);
   };
   void cmd(uint8_t value)
   {
      putc((uint8_t)0xFE); putc(value);
   };
   void special(uint8_t value)
   {
      putc((uint8_t)0x7C); putc(value);
   };
   void backlightOn(uint8_t level = 10)
   {
      special(level);
   };
   void backlightOff()
   {
      special(0);
   };
   void select_line(int line)
   {
      cmd(128 + (64*line));
   };
   void clear()
   {
      cmd(0x01);
   };

private:
   Serial & _port;
};

void SerLCD::write(const char *buffer)
{
   char *p = (char*)buffer;
   while (*p) {
      putc(*p++);
   }
}
void SerLCD::putc(uint8_t ch)
{
  _port.putc(ch);
}


void setup()
{
  ser_lcd.format(8, SerialBase::None, 1);
  ser_lcd.putc(0x12);   //ctrl-R = reset
  backlightOn();
}

  int level=0;

void loop()
{
  static char buff[17];
  
  selectLineOne();
  ser_lcd.printf("0123456789ABCDEF\r\n");
  select_line(1);
  ser_lcd.printf("Jam\r\n");
  sprintf(buff, "backlight = %d\r\n",  level);
  //char * p = buff;
  //while (*p) { ser_lcd.putc(*p); p++;}
  printline2(buff);
  //ser_lcd.printf(buff);
  wait(0.5);
  led1 = !led1;
  led2 = !led1;
  clearLCD();
}

int main()
{
    setup();
    wait(0.5);
    while (1) 
    {
      loop();
      backlightOn(level++);
      if (level > (157-128)) {level = 0;}
    }
    return 0;
}
