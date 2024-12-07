#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "config.h"
#include "pins.h"
//#include "pitches.h"
 #include "EEPROM.h"
#include "ledbits.h"
#include "music.h"

////////////// BadegeKitty ////////////
// December 7 2024
// ababin@fuse-tg.com
// codebase for the badgekitty handout
//////////////////////////////////////

#define noise false
#define eye_brightness  20 //0-255
#define total_cues 8
#define SLEEP_TIMEOUT 600000 // 10 minutes in milliseconds

char rndColor;

bool babin = false; 
bool kohler = false;
bool highpower = false;
volatile bool PoorMansDebounce = false; 
bool makeNoise = false;
//const int noteTrue = 1000/16;
//const int noteFalse = 1000/8;
#define noteTrue 62
#define noteFalse 126

volatile int lastActivityTime = 0; // Tracks the time of last activity
volatile uint8_t cue = 1;  // Variable to be incremented by the interrupt
unsigned int current = 0;

//inturruprt routine
//clears all flags, and incriments the cue number, also updates the idle timeout
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
        makeNoise = false;
      } 
      else {
        cue = 1;
        makeNoise = false;
      }
    }
    // Toggle the PoorMansDebounce flag every time the ISR is called
    PoorMansDebounce = !PoorMansDebounce;
    lastActivityTime = millis(); // Reset the activity timer on wake
        rndColor = (millis() % 8) ;
}

//helper function to turn off eyes, this buys us back some precious flash space.
void turnOffEyes() {
  setPixelColor(0, 0, 0);
  setPixelColor(0, 0, 0);
  show();
}



//sleeps kitty after a specified time, we rewrite current to 0 to sleep instantly 
void sleepKitty(){
  current = millis();
  turnOffEyes();
  if (((current - lastActivityTime) > SLEEP_TIMEOUT) && !highpower) {
    turnOffEyes();
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


//sleep mode setup helper function 
void initSleepMode(void) {
  //SLPCTRL.CTRLA = SLPCTRL_SMODE_IDLE_gc; // set sleep mode to "idle"
  //SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc; // set sleep mode to "standby"  
  SLPCTRL.CTRLA = SLPCTRL_SMODE_PDOWN_gc; // set sleep mode to "power down"
  SLPCTRL.CTRLA |= SLPCTRL_SEN_bm;  // enable sleep mode
}


//main setup function, called on powerup
void setup() {
    pinMode(EAR_GPI, INPUT_PULLUP);
    pinMode(TAIL_GPI, INPUT_PULLUP);
    initSleepMode();  // set up the sleep mode
        
    highpower = digitalRead(PIN_PA7);
    highpower = !highpower;
    if(highpower){brightScalar = 4;}
    kohler = highpower;
    babin = highpower;
    //kohler = babin = highpower;
    if(!digitalRead(EAR_GPI)){kohler = true;}
    if(!digitalRead(TAIL_GPI)){babin = true;}
    
    PORTA.DIRCLR = PIN7_bm;                    // Set PA7 as input
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; // Enable pull-up and interrupt on falling edge
    
   // setBrightness(digitalRead(PIN_PA7) ? eye_brightness : 100);
    //rndColor = (analogRead(PIN_PA7) % 4);
    // disable ADC

    ADC0.CTRLA &= ~ADC_ENABLE_bm;
    
    //eyes.begin();           // INITIALIZE NeoPixel eyes object (REQUIRED)
    ledsetup();  
    
    if(kohler && babin){
        setPixelColor(0,0,255);
        setPixelColor(0,0,255);
        show();
        delay(1000);
    }

    sei();                                     // Enable global interrupts
    lastActivityTime = millis(); // Initialize the activity timer

   //rndColor = (millis() % 8);
}
///////////////////


void MeowMeowMeow(){
    makeNoise = true;
    while(makeNoise){
      if(!makeNoise){break; cue++;}
      for (unsigned char thisNote = 0; thisNote < sizeof(melody); thisNote++) {
              if(!makeNoise){break; cue++;}

        setPixelColor(colors[(thisNote % 8)][0],colors[(thisNote % 8)][1],colors[(thisNote % 8)][2]);
        setPixelColor(colors[(thisNote % 4)][0],colors[(thisNote % 4)][1],colors[(thisNote % 4)][2]);
        show();

        int noteDuration = 0;
        if(noteDurations[thisNote]){
          noteDuration = noteTrue;
        } else if(!noteDurations[thisNote]){
          noteDuration = noteFalse;
        }
        
        tone(MEOWS, melody[thisNote]*6,noteDuration);

        int pauseBetweenNotes = noteDuration * 1.82 ;
        delay(pauseBetweenNotes);
        
        noTone(MEOWS); //stop the tone playing:
        //return;
    }
    return;
  }
}

void cue1BabinGreen(){ //Babin Green
  //eyes.setBrightness(eye_brightness); 
  setPixelColor(0,255,0);
  setPixelColor(0,255,0);
  show();
  //if (noise) tone(MEOWS, 1000, 20);
  delay(50);
  
  turnOffEyes();
  delay(50);
 // MeowMeowMeow();
  sleepKitty();
}

//int i = 0; //counter for rainbow cues 

void cue2KohlerRainbow(){ //Kohler Rainbow
/*

  #define RAINBOWDELAY 500
    if(i < 8) {
    // Set colors for LEDs 0 and 1 in pairs
    setPixelColor(colors[i][0], colors[i][1], colors[i][2]);           // LED 0
    setPixelColor(colors[(i + 1) % 8][0], colors[(i + 1) % 8][1], colors[(i + 1) % 8][2]);  // LED 1
    show();
      i++;
      delay(RAINBOWDELAY);
   }
    else{i = 0;}
  sleepKitty();
  */
  rainbowCycle(360, 8, 60 );
   //Homeslice's docs suck, A == B*C
}

void cue3randomColor(){ //both random pulse 
  //MeowMeowMeow();
  int eye1 = (millis() % 4);
  setPixelColor((colors[rndColor][0]/eye1),(colors[rndColor][1] / eye1),(colors[rndColor][2] / eye1));
  setPixelColor((colors[rndColor][0]/eye1),(colors[rndColor][1] / eye1),(colors[rndColor][2] / eye1));
  
  setPixelColor(eye1, eye1, eye1);
  setPixelColor(eye1, eye1, eye1);
  show();
  //tone(MEOWS, (eye1*400), 50);

  delay(100);
  sleepKitty();
}

void cue4yellowRed(){ //Yellow Red
  setPixelColor(255, 255, 0); 
  setPixelColor(255, 0, 0);
  show();        
  //if (noise) tone(MEOWS, 500, 100);
  delay(500);

  setPixelColor(255, 0, 0); 
  setPixelColor(255, 255, 0);
  show();  
  //if (noise) tone(MEOWS, 700, 100);      
  delay(500);
  sleepKitty();
}

void cue5(){ //white flash
  setPixelColor(255, 255, 255); 
  setPixelColor(255, 255, 255);
  show();        
  if (noise) tone(MEOWS, 500, 100);
  delay(200);

  turnOffEyes();
  if (noise) tone(MEOWS, 700, 100);      
  delay(200);
   sleepKitty();
}

void cue6cyanStrobe(){ //cyan magenta strobe BONUS Look
  
  setPixelColor(0, 255, 255); 
  setPixelColor(0, 0, 0);
  show();        
  if (noise) tone(MEOWS, 1500, 50);
  delay(100);

  setPixelColor(0, 0, 0); 
  setPixelColor(0, 255, 255);
  show();  
  if (noise) tone(MEOWS, 1700, 50);      
  delay(100);

  setPixelColor(255, 0, 255); 
  setPixelColor(0, 0, 0);
  show();        
  if (noise) tone(MEOWS, 2500, 50);
  delay(100);

  setPixelColor(0, 0, 0); 
  setPixelColor(255, 0, 255);
  show();  
  if (noise) tone(MEOWS, 2700, 50);      
  delay(100);
  sleepKitty();
}

void cue7angryRed(){ //angry red
  setPixelColor(colors[0][0], colors[0][1], colors[0][2]); 
  setPixelColor(colors[0][0], colors[0][1], colors[0][2]);
  show();        
  if (noise) tone(MEOWS, 400, 300);
  delay(700);
  
  turnOffEyes();
  if (noise) tone(MEOWS, 200, 300);      
  delay(700);
  sleepKitty();
}


char brightness = 0;  // Brightness level (0 to 255)
char increment = 1;   // How much to increase/decrease brightness per step


void cue8(){ //blue
  
  brightness += increment;
  if (brightness >= 255 || brightness <= 0) {
    increment = -increment;
  }
  int eye1 = (millis() % 4);
  setPixelColor(0, 0, brightness); 
  setPixelColor(0, 0, brightness);
  show();        
  delay(60);
  
  //turnOffEyes();
  //delay(500);
  //sleepKitty();
}

void cue9meow(){
  MeowMeowMeow();
  sleepKitty();
}

void loop() {
  
  switch(cue) {
    case 1: //Babin Cue green
      if(babin != true){cue++;}
      else{cue1BabinGreen();}
      break;
    
    case 2: // kohler rainbow
      if(kohler != true){cue++;}
      else{cue2KohlerRainbow();} //Kohler Cue rainbow
      break;

    case 3: //Both Cue cyan magenta chase
      if(babin && kohler){cue6cyanStrobe();}
      else{cue++;}
      break;
   
    case 4: //red yellow
      cue4yellowRed();   
      break;
    
    //case 5: //skip
      //cue5();
      //cue++; //we're skipping this one
      //break;

    case 5: // white random
      cue3randomColor();  
      //MeowMeowMeow();
      break;

    case 6: // angry red
      cue7angryRed();  
      break;

    case 7: 
      cue9meow();
      cue++;
      break;

    case 8: // sleep
    //turnOffEyes();
      lastActivityTime = 0; //this forces instant sleep
      sleepKitty();  // Enter sleep mode when cue is 8
      //cue8();
      break;
    }
    
}