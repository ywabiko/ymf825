/*
  YMF825 sample for ESP32

  This code is based on the official sample code.
  https://github.com/yamaha-webmusic/ymf825board

  Wiring (tested with Lolin32)
    VSPI
      RST_N - GPIO 32   
      SS    - GPIO 5
      MOSI  - GPIO 23
      MISO  - GPIO 19
      SCK   - GPIO 18

    HSPI
      RST_N - GPIO 32   
      SS    - GPIO 15
      MOSI  - GPIO 13
      MISO  - GPIO 12
      SCK   - GPIO 14

  Note for ESP32: 
     - Software CS is needed. Do not use hardware CS. (see set_ss_pin)
     - Software RST is needed as well. (see set_rst_pin)
*/

#include <SPI.h>
//0 :5V 1:3.3V
#define OUTPUT_power 0

#define PIN_RESET 32

// VSPI
#define PIN_CS 5
#define PIN_SCLK 18
#define PIN_MOSI 23
#define PIN_MISO 19
SPIClass spi_;

// HSPI
//#define PIN_CS 15
//#define PIN_SCLK 14
//#define PIN_MOSI 13
//#define PIN_MISO 12
//SPIClass spi_(HSPI);

void set_ss_pin(int val) {
    digitalWrite(PIN_CS, val);
}

void set_rst_pin(int val) {
    digitalWrite(PIN_RESET, val);
}

void if_write(char addr, unsigned char* data, char num){
    char i;
    char snd;

    set_ss_pin(LOW);
    spi_.transfer(addr);
    for (i = 0; i < num; i++){
        spi_.transfer(data[i]);    
    }
    set_ss_pin(HIGH);  
}

void if_s_write(char addr, unsigned char data){
    if_write(addr, &data, 1);
}

unsigned char if_s_read(char addr){
    unsigned char rcv;

    set_ss_pin(LOW);    
    spi_.transfer(0x80|addr);
    rcv = spi_.transfer(0x00);
    set_ss_pin(HIGH);  

    return rcv;  
}

void init_825(void) {

    set_rst_pin(LOW);
    delay(1);
    set_rst_pin(HIGH);
    if_s_write(0x1D, OUTPUT_power);
    if_s_write(0x02, 0x0E);
    delay(1);
    if_s_write(0x00, 0x01); //CLKEN
    if_s_write(0x01, 0x00); //AKRST
    if_s_write(0x1A, 0xA3);
    delay(1);
    if_s_write(0x1A, 0x00);
    delay(30);
    if_s_write(0x02, 0x04); //AP1,AP3
    delay(1);
    if_s_write(0x02, 0x00);
    //add
    if_s_write(0x19, 0xF0); //MASTER VOL
    if_s_write(0x1B, 0x3F); //interpolation
    if_s_write(0x14, 0x00); //interpolation
    if_s_write(0x03, 0x01); //Analog Gain
   
    if_s_write(0x08, 0xF6);
    delay(21);
    if_s_write(0x08, 0x00);
    if_s_write(0x09, 0xF8);
    if_s_write(0x0A, 0x00);
   
    if_s_write(0x17, 0x40); //MS_S
    if_s_write(0x18, 0x00);
}

void set_tone(void){
    unsigned char tone_data[35] = {
        0x81, //header
        //T_ADR 0
        0x01, 0x85,
        0x00, 0x7F, 0xF4, 0xBB, 0x00, 0x10, 0x40,
        0x00, 0xAF, 0xA0, 0x0E, 0x03, 0x10, 0x40,
        0x00, 0x2F, 0xF3, 0x9B, 0x00, 0x20, 0x41,
        0x00, 0xAF, 0xA0, 0x0E, 0x01, 0x10, 0x40,
        0x80, 0x03, 0x81, 0x80,
    };
  
    if_s_write(0x08, 0xF6);
    delay(1);
    if_s_write(0x08, 0x00);
  
    if_write(0x07, &tone_data[0], 35); //write to FIFO
}

void set_ch(void){
    if_s_write(0x0F, 0x30); // keyon = 0
    if_s_write(0x10, 0x71); // chvol
    if_s_write(0x11, 0x00); // XVB
    if_s_write(0x12, 0x08); // FRAC
    if_s_write(0x13, 0x00); // FRAC  
}

void keyon(unsigned char fnumh, unsigned char fnuml){
    if_s_write(0x0B, 0x00);  // voice num
    if_s_write(0x0C, 0x54);  // vovol
    if_s_write(0x0D, fnumh); // fnum
    if_s_write(0x0E, fnuml); // fnum
    if_s_write(0x0F, 0x40);  // keyon = 1  
}

void keyoff(void){
    if_s_write(0x0F, 0x00); // keyon = 0
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_RESET, OUTPUT);
    pinMode(PIN_CS, OUTPUT);

    spi_.begin(PIN_SCLK, PIN_MISO, PIN_MOSI, PIN_CS);
    spi_.setFrequency(7000000);
    spi_.setDataMode(SPI_MODE3);
    spi_.setHwCs(false);

    set_ss_pin(HIGH);
    init_825();
    set_tone();
    set_ch();
}

int count = 0;
void loop() {
    Serial.println("loop" + String(count++));

    keyon(0x14, 0x65);
    delay(500);
    keyoff();
    delay(200);
    keyon(0x1c, 0x11);
    delay(500);
    keyoff();
    delay(200);
    keyon(0x1c, 0x42);
    delay(500);
    keyoff();
    delay(200);
    keyon(0x1c, 0x5d);
    delay(500);
    keyoff();
    delay(200);
    keyon(0x24, 0x17);
    delay(500);
    keyoff();
    delay(200);
}
