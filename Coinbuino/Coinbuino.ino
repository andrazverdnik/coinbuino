
#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;

//declare all the variables needed for the game :
int man_x = LCDWIDTH/2; //set the horizontal position to the middle of the screen
int man_y = LCDHEIGHT/2; //vertical position
int man_vx = 1; //horizontal velocity
int man_vy = 1; //vertical velocity
int man_size_x = 5; //size of a man by x
int man_size_y = 8; // size of a man by y
int coin_x = 10;//x of diamond
int coin_y = 10;//y of diamond
int points = 0;//points
int coin_height = 7;//coin height
int coin_width = 7;//coin width
int direction = 0;//direction of man

//here are our figures
const byte PROGMEM man[] = {
  8, 8,
  B01110000,
  B01110000,
  B01110000,
  B00101111,
  B11111000,
  B00100000,
  B01010000,
  B10001000,
};
const byte PROGMEM coin[] = {
  8, 8, 
  B00111100,
  B01111110,
  B11100111,
  B11100111,
  B11100111,
  B11100111,
  B01111110,
  B00111100,
};


// the setup routine runs once when Gamebuino starts up
void setup(){
  // initialize the Gamebuino object
  gb.begin();
  // show the start manu
  gb.titleScreen(F("COINBUINO"));
}

// the loop routine runs over and over again forever
void loop(){
  //updates the gamebuino (the display, the sound, the auto backlight... everything)
  //returns true when it's time to render a new frame (20 times/second)
  if(gb.update()){
    man_vx = 1;
    man_vy = 1;
    if(gb.buttons.repeat(BTN_A, 1)){
      man_vx = 4;
      man_vy = 4;     
    }
    
    //move man using the buttons
    if(gb.buttons.repeat(BTN_RIGHT,2)){ //every 2 frames when the right button is held down
      man_x = man_x + man_vx; //increase the horizontal position by the man's velocity
      gb.sound.playTick(); //play a preset "tick" sound every time the button is pressed
      direction = 0;
    }
    
    if(gb.buttons.repeat(BTN_LEFT,2)){
      man_x = man_x - man_vx;
      gb.sound.playTick();
      direction = 1;
    }
    
    if(gb.buttons.repeat(BTN_DOWN,2)){
      man_y = man_y + man_vy;
      gb.sound.playTick();
    }
    
    if(gb.buttons.repeat(BTN_UP,2)){
      man_y = man_y - man_vy;
      gb.sound.playTick();
    }
   
   
    if(gb.buttons.pressed(BTN_C)){
      gb.titleScreen(F("COINBUINO"));
    }

    
  
    if(man_x < 0){
     
      man_x = 0;
    }
    
    if((man_x + man_size_x) > LCDWIDTH){
      man_x = LCDWIDTH - man_size_x;
    }
    
    
    if(man_y < 0){
      man_y = 0;
    }
    
   
    if((man_y + man_size_y) > LCDHEIGHT){
      man_y = LCDHEIGHT - man_size_y;
    }
        
    if (gb.collideBitmapBitmap(man_x, man_y, man, coin_x, coin_y, coin)  == true) {
      points = points + 1;
      coin_x = random(LCDWIDTH - coin_width);
      coin_y = random(LCDHEIGHT - coin_height);
      gb.sound.playOK();
    }

    gb.display.drawBitmap(man_x, man_y, man, 0, direction);
    gb.display.drawBitmap(coin_x, coin_y, coin, 0, 0);
    gb.display.println(points);
  
  }
}

