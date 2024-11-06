#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "config.h"
#include "pins.h"


//int mode = 1;
//bool eye1 = true;
//bool eye2 = true;
#define noise true
bool babin = false; 
bool kohler = false;
bool highpower = false;

#define eye_brightness  20 //0-255
#define total_cues 7
#define DEBOUNCE_DELAY 50 // Debounce delay in milliseconds
#define SLEEP_TIMEOUT 600000 // 10 minutes in milliseconds
volatile unsigned long lastActivityTime = 0; // Tracks the time of last activity



volatile uint8_t cue = 1;  // Variable to be incremented by the interrupt
//volatile uint32_t last_interrupt_time = 0; // Store the last interrupt time for debounce

//rainbow array
const uint8_t colors[][3] = {
  {255, 0, 0},    // Red
  {255, 127, 0},  // Orange
  {255, 255, 0},  // Yellow
  {0, 255, 0},    // Green
  {0, 255, 255},  // Cyan
  {0, 0, 255},    // Blue
  {255, 0, 255},  // Magenta
  {255, 0, 127}   // Pink
};

volatile bool PoorMansDebounce = false; 

ISR(PORTA_PORT_vect) {
    // Clear the interrupt flag for the button pin (PA7 in this case)
    if (PORTA.INTFLAGS & PIN7_bm) {
        PORTA.INTFLAGS = PIN7_bm;  // Clear the interrupt flag for PA7
    }

    // Increment cue every other interrupt
    if (PoorMansDebounce) {
        // Increment cue if it's within the limit; reset if it exceeds total_cues
        if (cue <= total_cues) {
            cue++;
        } else {
            cue = 1;
        }
    }
    // Toggle the PoorMansDebounce flag every time the ISR is called
    PoorMansDebounce = !PoorMansDebounce;
    lastActivityTime = millis(); // Reset the activity timer on wake
}


void delay500(){
  delay(500);
}
//sets sleep modes for kitty
void sleepCat() {
    power_all_disable();              // Disable power to unused peripherals
    set_sleep_mode(SLEEP_MODE_IDLE); // Use PWR_DOWN for the lowest power mode
    //    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Use PWR_DOWN for the lowest power mode

    sleep_enable();                   // Enable sleep before entering mode
    //sleep_cpu();
    sleep_mode();                     // Enter sleep mode (device will sleep until interrupt wakes it)
    // Device wakes here upon interrupt
    //sleep_disable();                  // Disable sleep mode after waking up
   // power_all_enable();               // Re-enable power to all peripherals
}
unsigned long current = 0;

void appTimeout(){
  current = millis();
  if (((current - lastActivityTime) > SLEEP_TIMEOUT) && !highpower) {
    eyes.setPixelColor(0, 0, 0,0);
    eyes.setPixelColor(1,0,0,0);
    eyes.show();
    //delay(30);
    sleep_enable();                   // Enable sleep before entering mode
    sleep_cpu();
    sei();
    sleep_mode();                     // Enter sleep mode (device will sleep until interrupt wakes it)
    // Device wakes here upon interrupt
    sleep_disable();                  // Disable sleep mode after waking up
    power_all_enable();               // Re-enable power to all peripherals
    lastActivityTime = millis(); // Reset the activity timer on wake
    }
}

void initSleepMode(void) {
  //SLPCTRL.CTRLA = SLPCTRL_SMODE_IDLE_gc; // set sleep mode to "idle"
  //SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc; // set sleep mode to "standby"  
  SLPCTRL.CTRLA = SLPCTRL_SMODE_PDOWN_gc; // set sleep mode to "power down"
  SLPCTRL.CTRLA |= SLPCTRL_SEN_bm;  // enable sleep mode
}

void setup() {
    pinMode(EAR_GPI, INPUT_PULLUP);
    pinMode(TAIL_GPI, INPUT_PULLUP);
    initSleepMode();  // set up the sleep mode
        
    highpower = digitalRead(PIN_PA7);
    highpower = !highpower;
    kohler = highpower;
    //babin = highpower;
    //kohler = babin = highpower;
    if(!digitalRead(EAR_GPI)){kohler = true;}
    if(!digitalRead(TAIL_GPI)){babin = true;}
    
    PORTA.DIRCLR = PIN7_bm;                    // Set PA7 as input
    
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; // Enable pull-up and interrupt on falling edge
//PORT_ISC_
    
    eyes.setBrightness(digitalRead(PIN_PA7) ? eye_brightness : 100);

    // disable ADC
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
    //PRR |= (1 << ADC0_bp);
    
    eyes.begin();           // INITIALIZE NeoPixel eyes object (REQUIRED)
    
    if(kohler){eyes.setPixelColor(0, 0, 0, 50);}
    if(babin){eyes.setPixelColor(1, 0, 0, 50);}
    eyes.show();            // Turn OFF all pixels ASAP
    
    if(kohler){delay(1000);}
    else if(babin){delay(1000);}
    sei();                                     // Enable global interrupts
    lastActivityTime = millis(); // Initialize the activity timer

}
///////////////////

void cue1(){ //Babin Green
  //eyes.setBrightness(eye_brightness); 
  eyes.setPixelColor(0, 0,255,0);
  eyes.setPixelColor(1, 0,255,0);
  eyes.show();
  //if (noise) tone(MEOWS, 1000, 20);
  delay(50);
  
  //eyes.setBrightness(0); 
  eyes.setPixelColor(0, 0,0,0);
  eyes.setPixelColor(1, 0,0,0);
  eyes.show();
  delay(50);
  //appTimeout();
    appTimeout();
}
int i = 0;


void cue2(){ //Kohler Rainbow
  #define RAINBOWDELAY 500
    if(i < 8) {
    // Set colors for LEDs 0 and 1 in pairs
    eyes.setPixelColor(0, colors[i][0], colors[i][1], colors[i][2]);           // LED 0
    eyes.setPixelColor(1, colors[(i + 1) % 8][0], colors[(i + 1) % 8][1], colors[(i + 1) % 8][2]);  // LED 1
    eyes.show();
      i++;
      delay(RAINBOWDELAY);
   }
    else{i = 0;}
  appTimeout();


}

void cue3(){ //both random pulse Bonus look
  int eye1 = (millis() % 255);
  eyes.setPixelColor(0, eye1, eye1, eye1);
  eyes.setPixelColor(1, eye1, eye1, eye1);
  eyes.show();
  //tone(MEOWS, (eye1*4), 50);

  delay(100);
    appTimeout();
}

void cue4(){ //red green 
  eyes.setPixelColor(0, 255, 255, 0); 
  eyes.setPixelColor(1, 255, 0, 0);
  eyes.show();        
  //if (noise) tone(MEOWS, 500, 100);
  delay(500);

  eyes.setPixelColor(0, 255, 0, 0); 
  eyes.setPixelColor(1, 255, 255, 0);
  eyes.show();  
  //if (noise) tone(MEOWS, 700, 100);      
  delay(500);
    appTimeout();
}

void cue5(){ //white flash
  eyes.setPixelColor(0, 255, 255, 255); 
  eyes.setPixelColor(1, 255, 255, 255);
  eyes.show();        
  if (noise) tone(MEOWS, 500, 100);
  delay(200);

  eyes.setPixelColor(0, 0, 0, 0); 
  eyes.setPixelColor(1, 0, 0, 0);
  eyes.show();  
  if (noise) tone(MEOWS, 700, 100);      
  delay(200);
    appTimeout();
}

void cue6(){ //cyan magenta strobe
  
  eyes.setPixelColor(0, 0, 255, 255); 
  eyes.setPixelColor(1, 0, 0, 0);
  eyes.show();        
  if (noise) tone(MEOWS, 1500, 50);
  delay(100);

  eyes.setPixelColor(0, 0, 0, 0); 
  eyes.setPixelColor(1, 0, 255, 255);
  eyes.show();  
  if (noise) tone(MEOWS, 1700, 50);      
  delay(100);

  eyes.setPixelColor(0, 255, 0, 255); 
  eyes.setPixelColor(1, 0, 0, 0);
  eyes.show();        
  if (noise) tone(MEOWS, 2500, 50);
  delay(100);

  eyes.setPixelColor(0, 0, 0, 0); 
  eyes.setPixelColor(1, 255, 0, 255);
  eyes.show();  
  if (noise) tone(MEOWS, 2700, 50);      
  delay(100);
    appTimeout();
}

void cue7(){ //angry red
  eyes.setPixelColor(0, colors[0][0], colors[0][1], colors[0][2]); 
  eyes.setPixelColor(1, colors[0][0], colors[0][1], colors[0][2]);
  eyes.show();        
  if (noise) tone(MEOWS, 400, 300);
  delay(700);
  
  eyes.setPixelColor(0, 0, 0, 0); 
  eyes.setPixelColor(1, 0, 0, 0);
  eyes.show();  
  if (noise) tone(MEOWS, 200, 300);      
  delay(700);
  appTimeout();
}



void loop() {
  switch(cue) {

    
    case 1: //Babin Cue green
      if(babin != true){cue++;}
      else{cue1();}
      break;
    
    case 2:
      if(kohler != true){cue++;}
      else{cue2(); 
        } //Kohler Cue rainbow
      break;

    case 3: //Both Cue cyan magenta chase
      if(babin && kohler){cue6();}
      else{cue++;}
      break;
   
    case 4: //red green
      cue4();   
      break;
    
    //case 5: //skip
      //cue5();
      //cue++; //we're skipping this one
      //break;

    case 5: // white random
      cue3();  
      break;

    case 6: // angry red
      cue7();  
      break;

    case 7: // sleep
      lastActivityTime = 0;
      appTimeout();  // Enter sleep mode when cue is 8
      break;
    }
}