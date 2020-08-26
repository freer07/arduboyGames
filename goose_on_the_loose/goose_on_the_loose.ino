/*
 * Creators:
 * Jenna Straughan
 * Alex Freer
 * 21/03/2020
 * 
 */

 /*
  * TODO
  * 
  * Points/"coins" or something to collect 
  * 
  * health points 
  * 
  * checkpoints
  * 
  * more enemies
  * 
  * Win/GameOver
  * 
  * abilities to defeat enemies
  *   lay an egg
  *   peck 
  *   
  * gain back health 
  *  
  * Boss fight???
  */
 
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include <EEPROM.h>
#include "Tinyfont.h"
#include "maps.h"
#include "goose.h"
#include "enemies.h"


Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

//Game Variables
byte gameState = 0;
short mapDisplayX = 0;
short mapX = 0;
byte currMap = 1;
bool isOnLedge = false;

//goose
short gooseScreenX = 64 - 24;
int gooseMapX = map1Start;
int gooseY = ground - gooseHeight;
short gooseImg = 3;
bool movingRight = true;
byte distance = 0;
const byte maxJumpHeight = 34;
byte jumpHeight = 0;
byte heightLeft = 0;
bool isJumping = false;
int adjust = 0;
bool isDead = false;
int checkPoint = map1Start;

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
      isOnLedge = onLedge();
      moveGoose();
      walkEnemies();
      if(isJumping) {
        jumpGoose();
      } else {
        checkFall();
      }
      if(collisionWithOldMan()) {
        isDead = true;
      }
      calcAdjust();
      displayMap();
      displayLedges();
      displayEnemies();
      displayGoose();
    case 2://game over
    break;
  }
  
  arduboy.display();
}

void calcAdjust() {
  if(gooseY < 0) {
    adjust = gooseY;
  } else {
    adjust = 0;
  }
}

void checkFall() {
  if((gooseY + gooseHeight < ground && !isOnLedge) || isDead){
    gooseY ++;
  }
  if(gooseY > 64) {
    gooseMapX = checkPoint;
    isDead = false;
    gooseY = ground - gooseHeight;
  }
}

bool onLedge() {
  for(byte i = 0; i < map1Ledges; i ++){
    if(gooseMapX + gooseWidth - 6 >= map1LedgesX[i] && gooseMapX + 7 <= map1LedgesX[i] + ledgeLength){ //if goose's feet is where a ledge is
      if(gooseY + gooseHeight == map1LedgesY[i]) { //goose is standing on the ledge
        return true;
      }
    }
  }
  return false;//not on anyledge 
}

bool collisionWithOldMan() {
  for(byte i = 0; i < map1Ledges; i ++){
    if(gooseImg == 0 || gooseImg == 1 || gooseImg == 2) {
      if(((gooseMapX + 4 < map1EnemiesCurrentX[i] + oldManWidth) && (gooseMapX + gooseWidth > map1EnemiesCurrentX[i])) && 
      ((gooseY + gooseHeight - 6 > map1EnemiesY[i]) && (gooseY < map1EnemiesY[i] + oldManHeight))){
        return true;
      }
    } else {
      if(((gooseMapX < map1EnemiesCurrentX[i] + oldManWidth) && (gooseMapX + gooseWidth - 4 > map1EnemiesCurrentX[i])) && 
      ((gooseY + gooseHeight - 6 > map1EnemiesY[i]) && (gooseY < map1EnemiesY[i] + oldManHeight))){
        return true;
      }
    }
  }
  return false;
}

void moveGoose() {
  if(arduboy.pressed(LEFT_BUTTON)) {
    moveGooseLeft();
    movingRight = false;
  } else if (arduboy.pressed(RIGHT_BUTTON)) {
    moveGooseRight();
    movingRight = true;
  } else if (arduboy.justPressed(DOWN_BUTTON)) { //fall off ledge
    if(isOnLedge){
      isOnLedge = false;
      gooseY ++;
    }
  }
  if (arduboy.justPressed(B_BUTTON)) {
    if(!isJumping && (gooseY + gooseHeight == ground || isOnLedge)){
      isJumping = true;
      jumpHeight = maxJumpHeight;
      heightLeft = jumpHeight;
    } 
  } 
}

void displayMap() {
  Sprites::drawOverwrite(mapDisplayX, 0 - topOfBackground - adjust, map1, 0);
  Sprites::drawOverwrite(mapDisplayX + map1Width, 0 - topOfBackground - adjust, map1, 0);
}

void displayLedges() {
  for(byte i = 0; i < map1Ledges; i++) {
    Sprites::drawExternalMask(map1LedgesX[i] - gooseMapX + gooseScreenX, map1LedgesY[i] - adjust, Ledge, LedgeMask, 0, 0);
  }
}

void displayGoose() {
  switch(gooseImg) {
    case 0:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseStanding, GooseMask, 0, 0);
      break;
    case 1:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseWalk1, GooseMask, 0, 0);
      break;
    case 2:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseWalk2, GooseMask, 0, 0);
      break;
    case 3:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseStandingRight, GooseRightMask, 0, 0);
      break;
    case 4:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseWalk1Right, GooseRightMask, 0, 0);
      break;
    case 5:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseWalk2Right, GooseRightMask, 0, 0);
      break;
    case 6:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseJump, GooseJumpMask, 0, 0);
      break;
    case 7:
      Sprites::drawExternalMask(gooseScreenX, gooseY - adjust, GooseJumpRight, GooseJumpMaskRight, 0, 0);
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


/*
 * This method controls the walking action of the enemies in a map
 */
void walkEnemies(){
  for(byte i = 0; i < map1Enemies; i++){
    if(map1EnemiesStartX[i] == map1EnemiesCurrentX[i] && !walkingRight[i]) {//at the start of the pacing distance 
      walkingRight[i] = true;
      map1EnemiesCurrentX[i] = map1EnemiesCurrentX[i] + 0.25;
    } else if(map1EnemiesCurrentX[i] == map1EnemiesStartX[i] + travelDistance && walkingRight[i]) {//at the end of the pacing distance 
      walkingRight[i] = false;
      map1EnemiesCurrentX[i] = map1EnemiesCurrentX[i] - 0.25;
    } else if (walkingRight[i]) { //walking right 
      map1EnemiesCurrentX[i] = map1EnemiesCurrentX[i] + 0.25;
    } else { //walking left 
      map1EnemiesCurrentX[i] = map1EnemiesCurrentX[i] - 0.25;
    }

    if(map1CurrentDistance[i] > 0) {
      map1CurrentDistance[i] --;
    } else { //cahnge the image to show walking action
      map1CurrentDistance[i] = 10;
      switch(map1CurrentImg[i]) {
        case 0:
          map1CurrentImg[i] = 1;
          break;
        case 1:
          map1CurrentImg[i] = 0;
          break;
      }
    }
  }
}

void displayEnemies() {
  for(byte i = 0; i < map1Enemies; i++){
    int x = map1EnemiesCurrentX[i];
    byte y = map1EnemiesY[i];
    switch(map1EnemyType[i]) {
      case 0://oldman
        switch(map1CurrentImg[i]) {
          case 0:
            if(walkingRight[i]) {//old Man right
              displayEnemy(x, y, 2);
            } else {//old man
              displayEnemy(x, y, 0);
            }
            break;
          case 1:
            if(walkingRight[i]) {//old Man walking right
              displayEnemy(x, y, 3);
            } else {//old man walking 
              displayEnemy(x, y, 1);
            }
            break;
        }
        break;
      }
  }
}

void displayEnemy(int x, byte y, byte num) {
  switch(num) {
    case 0://OldMan
      Sprites::drawExternalMask(x - gooseMapX + gooseScreenX, y - adjust, OldMan, OldManMask, 0, 0);
      break;
    case 1://OldManWalking
      Sprites::drawExternalMask(x - gooseMapX + gooseScreenX, y - adjust, OldManWalk, OldManMask, 0, 0);
      break;
    case 2://OldManRight
      Sprites::drawExternalMask(x - gooseMapX + gooseScreenX, y - adjust, OldManRight, OldManMaskRight, 0, 0);
      break;
    case 3://oldManWalkingRight
      Sprites::drawExternalMask(x - gooseMapX + gooseScreenX, y - adjust, OldManWalkRight, OldManMaskRight, 0, 0);
      break;
  }
}
