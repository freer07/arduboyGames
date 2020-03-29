/*
 * Creators:
 * Jenna Straughan
 * Alex Freer
 * 21/03/2020
 * 
 */
 
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include <EEPROM.h>
#include "Tinyfont.h"
#include "maps.h"
#include "goose.h"


Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

//Game Variables
byte gameState = 0;
short mapDisplayX = 0;
short mapX = 0;
const byte ground = 59;
byte currMap = 1;

//goose
short gooseScreenX = 64 - 24;
int gooseMapX = map1Start;
byte gooseY = ground - gooseHeight;
short gooseImg = 3;
bool movingRight = true;
byte distance = 0;
const byte maxJumpHeight = 30;
byte jumpHeight = 0;
byte heightLeft = 0;
bool isJumping = false;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.audio.on();
  arduboy.initRandomSeed(); //Seed the random number generator
  arduboy.clear();

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
  #ifndef AB_DEVKIT
    // if not a DevKit
    tunes.initChannel(PIN_SPEAKER_2);
  #else
    // if it's a DevKit
    tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
    tunes.toneMutesScore(true);       // mute the score when a tone is sounding
  #endif
}

void loop() {
  //This prevents the arduboy from running too fast
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();

  switch(gameState) {
    case 0://intro 
    case 1:
      moveGoose();
      if(isJumping) {
        jumpGoose();
      } else {
        checkFall();
      }
      displayMap();
      displayGoose();
    case 2://game over
    break;
  }
  
  arduboy.display();
}

void checkFall() {
  /*check if above platform here */
  if(gooseY + gooseHeight < ground){
    gooseY ++;
  }
}

void moveGoose() {
  if(arduboy.pressed(LEFT_BUTTON)) {
    moveGooseLeft();
    movingRight = false;
  } else if (arduboy.pressed(RIGHT_BUTTON)) {
    moveGooseRight();
    movingRight = true;
  } 
  if (arduboy.justPressed(B_BUTTON)) {
    if(!isJumping && gooseY + gooseHeight == ground){
      isJumping = true;
      jumpHeight = maxJumpHeight;
      heightLeft = jumpHeight;
    } 
  } 
}

void displayMap() {
  Sprites::drawOverwrite(mapDisplayX, 0, map1, 0);
  Sprites::drawOverwrite(mapDisplayX + map1Width, 0, map1, 0);
}

void displayGoose() {
  switch(gooseImg) {
    case 0:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseStanding, GooseMask, 0, 0);
      break;
    case 1:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseWalk1, GooseMask, 0, 0);
      break;
    case 2:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseWalk2, GooseMask, 0, 0);
      break;
    case 3:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseStandingRight, GooseRightMask, 0, 0);
      break;
    case 4:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseWalk1Right, GooseRightMask, 0, 0);
      break;
    case 5:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseWalk2Right, GooseRightMask, 0, 0);
      break;
    case 6:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseJump, GooseJumpMask, 0, 0);
      break;
    case 7:
      Sprites::drawExternalMask(gooseScreenX, gooseY, GooseJumpRight, GooseJumpMaskRight, 0, 0);
      break;
  }
}

void jumpGoose() {
  if(heightLeft > 0) {
    if(!movingRight){
      gooseImg = 6;
    } else {
      gooseImg = 7;
    }
    heightLeft --;
    gooseY --; 
  } else {
    if(!movingRight){
      gooseImg = 0;
    } else {
      gooseImg = 3;
    }
    isJumping = false;
    heightLeft = 0;
    jumpHeight = 0;
  }
}

void moveGooseRight() {
  if(gooseMapX + gooseWidth < map1End){
    walkingGooseImgRight();
    gooseMapX ++;
    mapX --;
    if(mapDisplayX + map1Width > 0) {
      mapDisplayX --;
    } else {
      mapDisplayX = 0;
    }
  }
}

void moveGooseLeft() {
  if(gooseMapX > map1Start){
    walkingGooseImgLeft();
    gooseMapX --;
    mapX ++;
    if(mapDisplayX < 0) {
      mapDisplayX ++;
    } else {
      mapDisplayX = 0 - map1Width;
    }
  }
}

void walkingGooseImgLeft() {
  if(distance == 0) {
    gooseImg = gooseImg == 1 ? 2: 1;
    distance = 10;
  } else {
    distance --;
  }
}

void walkingGooseImgRight() {
  if(distance == 0) {
    gooseImg = gooseImg == 4 ? 5: 4;
    distance = 10;
  } else {
    distance --;
  }
}
