#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
AnalogOut aout(PA_4);
//AnalogOut Rvin(D6);
DigitalIn But1(A2);
DigitalIn But2(A1);
DigitalIn But3(A0);
DigitalIn mypin(USER_BUTTON);

AnalogIn VIN(A3);


int main(){

    int frequency = 100;
    uint16_t sample = 0;
    float sample2[200];
    aout = 1;
    while(1){
        if (But1 == 1){
            frequency += 10;
            uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%d\n", frequency);
        }

        if (But2 == 1){
            break;

        }

        if (But3 == 1){

            frequency -= 10;
            uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%d\n", frequency);

        }


    }
    printf("%d\r\n", frequency);
    while(1){
            if (!mypin) break;
            for (int j = 0; j < 4; j++){
                  for (int i = 0; i < 40; i++) {
                        sample = (uint16_t)(59578 * i / 40);
                        aout.write_u16(sample);
                        sample2[i + j * 50] = VIN;
                        wait_us(20000/frequency);
                  }
                  for (int i = 0; i < 10; i++) {
                        sample = (uint16_t)(59578 * (10 - i) / 10);
                        aout.write_u16(sample);
                        sample2[i + 40 + j * 50] = VIN;
                  
                        wait_us(20000/frequency);
                  }
            }
      }
      for (int i = 0; i < 200; i++) {
            printf("%f\r\n", sample2[i]);
      }
}