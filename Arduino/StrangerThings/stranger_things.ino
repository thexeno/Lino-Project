/*
 * USAGE:
 * After upload, will run a default sentence on APA102 string. To upload a new one, just send a new one from the serial line. 
 *
 * stranger_lights.ino - StrangerThings lights control - Version 1.0
 * Created on 12/2017
 * Original sketch         (0.1)   by Enrico Sanino
 * Final first issue       (1.0)   by Eddy
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <APA102.h>

#define STRIP_SIZE 26
#define INPUT_BUFF_SIZE 64
#define ITERATIONS 10

// Define which pins to use.
const uint8_t dataPin = 5;
const uint8_t clockPin = 6;


// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

int index[STRIP_SIZE] = { 25, 24, 23, 22, 21, 20, 19, 18, 10, 11, 12, 13, 14, 15, 16, 17, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
char input_buffer[INPUT_BUFF_SIZE] = "merry christmas";
volatile int input_size = 15;
rgb_color colors[STRIP_SIZE];

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  ledStrip.startFrame();
  
  for (int i = 0; i < STRIP_SIZE; i++) {
    colors[i] = rgb_color(0,0,0);
  }
  
  ledStrip.write(colors, STRIP_SIZE, 31);
  ledStrip.endFrame(STRIP_SIZE);
}

void loop(){
  if (Serial.available() > 0) {
    input_size = Serial.available();
    Serial.readBytes(input_buffer, input_size);
    Serial.print(input_buffer);
    Serial.print(" ");
    Serial.print(input_size);
  }
  
  ledStrip.startFrame();
  process(input_buffer, input_size);   
  ledStrip.endFrame(STRIP_SIZE);

  delay(500);
  for (int i = 0; i < STRIP_SIZE; i++) {
    colors[i] = rgb_color(64,64,64);
  }

  for (int i = 0; i < 31; i++) {
    ledStrip.startFrame();
    ledStrip.write(colors, STRIP_SIZE, i);
    ledStrip.endFrame(STRIP_SIZE);
    delay(10);
  }

  for (int i = 31; i >= 0; i--) {
    ledStrip.startFrame();
    ledStrip.write(colors, STRIP_SIZE, i);
    ledStrip.endFrame(STRIP_SIZE);
    delay(10);
  }

  for (int i = 0; i < STRIP_SIZE; i++) {
    colors[i] = rgb_color(0,0,0);
  }
  
  ledStrip.startFrame();
  ledStrip.write(colors, STRIP_SIZE, 31);
  ledStrip.endFrame(STRIP_SIZE);
  delay(500);
}

void process(char* s, char n) {

    int flickers = 10;
    int flicker_delay = 10;
    int flicker_toggle = 1;
    
    for (int j = 0; j < n; j++) {

        if (Serial.available() > 0) {
          break;
        }

        if (s[j] < 'a' || s[j] > 'z') {
          delay(1000);
          continue;
        }
        
        for (int k = 0; k < flickers; k++) {
            flicker_delay = random(10, 151);
            
            if (flicker_toggle) {
              int led_number = index[(s[j]-'a')];
              switch(led_number % 4) {
                case 0: 
                  colors[led_number] = rgb_color(255,102,0);
                  break;
                case 1:
                  colors[led_number] = rgb_color(0,0,255);
                  break;
                case 2:
                  colors[led_number] = rgb_color(0,255,0);
                  break;
                case 3:
                  colors[led_number] = rgb_color(255,0,0);    
                  break;
                default:
                  colors[led_number] = rgb_color(255,255,255);
              }
              flicker_toggle = 0;
            }
            else {
              colors[index[(s[j]-'a')]] = rgb_color(0,0,0);
              flicker_toggle = 1;
            }
            
            ledStrip.write(colors, STRIP_SIZE, 31); 
            delay(flicker_delay);
        }
            
        colors[index[(s[j]-'a')]] = rgb_color(0,0,0);
        ledStrip.write(colors, STRIP_SIZE, 31); 
        delay(100);
  }
}
