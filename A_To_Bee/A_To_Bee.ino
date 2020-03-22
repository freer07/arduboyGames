/*
 * Alex Freer
 * 21/03/2020
 * 
 * TODO:
 * add lives
 * wasps
 * flowers -> random between the two
 * counter for points
 * increase difficulty with the number of points
 * sounds 
 * intro screen 
 * lose screen
 * credits screen
 * 
 * Maybe:
 * other enemies like pest spray
 * stinger
 * boost
 * save max score if possible
 * 
 */
 
#include <Arduboy2.h>
Arduboy2 arduboy;

//flower2 size 16x16
const unsigned char PROGMEM flower2[] =
{
// width, height,
16, 16,
0x1f, 0x63, 0xc6, 0x84, 0x3c, 0x78, 0xcc, 0x07, 0x07, 0xcc, 0x78, 0x0c, 0x84, 0xc6, 0x63, 0x1f, 
0x00, 0x00, 0x00, 0x01, 0x31, 0x6a, 0x4b, 0xfe, 0xfe, 0xa3, 0x92, 0x51, 0x21, 0x00, 0x00, 0x00, 
};

//flower1 size 16x16
const unsigned char PROGMEM flower1[] =
{
// width, height,
16, 16,
0x00, 0x3f, 0x66, 0xcc, 0x88, 0x78, 0xdc, 0x0e, 0x0f, 0xdc, 0x78, 0x88, 0xcc, 0x66, 0x3f, 0x00, 
0x00, 0x00, 0x00, 0x08, 0x19, 0x32, 0x53, 0xff, 0xa3, 0xd3, 0x72, 0x19, 0x08, 0x00, 0x00, 0x00, 
};

//hive size 16x16
const unsigned char PROGMEM hive[] =
{
// width, height,
16, 16,
0x01, 0x01, 0x01, 0x81, 0x61, 0x59, 0x15, 0x57, 0x57, 0x44, 0x58, 0x60, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x06, 0x1d, 0x35, 0x55, 0x45, 0x55, 0x51, 0x51, 0x51, 0x35, 0x1d, 0x06, 0x00, 0x00, 
};

//wasp size 13x10
const unsigned char PROGMEM wasp[] =
{
// width, height,
16, 16,
0x80, 0x40, 0x20, 0x90, 0x78, 0xae, 0x25, 0xae, 0x78, 0x90, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 
0x01, 0x03, 0x02, 0x01, 0x00, 0x01, 0x03, 0x01, 0x00, 0x01, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM waspUpsideDown[] =
{
// width, height,
16, 16,
0x06, 0x0b, 0x11, 0x26, 0x78, 0xd6, 0x93, 0xd6, 0x78, 0x26, 0x11, 0x0b, 0x06, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//Bee size 11x9
const unsigned char PROGMEM beeLeft[] =
{
// width, height,
16, 16,
0xe0, 0x10, 0x4e, 0x09, 0xfd, 0x0a, 0xf9, 0x95, 0x62, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM beeRight[] =
{
// width, height,
16, 16,
0x20, 0x20, 0x62, 0x95, 0xf9, 0x0a, 0xfd, 0x09, 0x4e, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


//Game Variables
int gameState = 0;
const int arduboyTop = 0;
const int arduboyBottom = 64;
const int arduboyLeft = 0;
const int arduboyRight = 128;
int numOfWasps = 1;
const int maxNumOfWasps = 4;
int lives = 3;

//Bee
const int beeWidth = 11;
const int beeHeight = 9;
int beeX = 0;
int beeY = 25;
boolean movingLeft = false;

//Wasps
const int waspWidth = 13;
const int waspHeight = 10;
int wasp1X = 50;
double wasp1Y = arduboyTop - waspHeight;
bool wasp1Top = true;
int wasp2X = -50;
int wasp2Y = arduboyBottom;
bool wasp2Top = false;
int wasp3X = -50;
int wasp3Y = arduboyTop - waspHeight;
bool wasp3Top = true;
int wasp4X = -50;
int wasp4Y = arduboyBottom;
bool wasp4Top = false;

//hive
const int hiveX = 0;
const int hiveY = 25;

//flower
const int flowerWidth = 16;
const int flowerHeight = 16;


void setup() {
  arduboy.begin();
  //Seed the random number generator
  arduboy.initRandomSeed();
  arduboy.clear();
}

void loop() {
  //This prevents the arduboy from running too fast
  if (!arduboy.nextFrame()) {
    return;
  }
  
  arduboy.clear();

  arduboy.pollButtons();

  switch(gameState) {
    case 0://TitleScreen
    case 1://Game
      moveBee();
      moveWasps();
      drawWasps();
      drawBee();
      drawHive();
      break;
  }

  arduboy.display();
}

void moveWasps() {
  switch(numOfWasps) {
    case 1:
      moveWasp(wasp1X, wasp1Y, 1);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
}

void drawWasps() {
  if(wasp1Top) {
    Sprites::drawSelfMasked(wasp1X, (int)wasp1Y, waspUpsideDown, 0);
  } else {
    Sprites::drawSelfMasked(wasp1X, (int)wasp1Y, wasp, 0);
  }
}

void moveWasp(int waspX, double waspY, int waspNum) {
  switch(waspNum) {
    case 1:
      if(wasp1Y + waspHeight < arduboyTop || wasp1Y > arduboyBottom) {
        wasp1X = 50;//place off screen incase there isn't a spot
        placeWasp(waspNum);
      } else {
        if(wasp1Top) {
          wasp1Y = wasp1Y + 0.5;
        } else {
          wasp1Y = wasp1Y - 0.5;
        }
      }
      break;
    case 2:
    case 3:
    case 4:
      break;
  }
}

int placeWasp(int waspNum) {
  for(int guess = 0; guess < 10; guess ++) {
    int x = random(17, arduboyRight - waspWidth - flowerWidth);
    double y;
    int top = random(0,2);
    bool isTop = true;

    switch(top) {
      case 0:
        y = arduboyTop - waspHeight;
        isTop = true;
        break;
      case 1:
        y = arduboyBottom;
        isTop = false;
        break;
    }
    if(notWithinObjectPath(x)){ 
      //setXVal
      switch(waspNum) {
        case 1:
          wasp1X = x;
          wasp1Top = isTop;
          wasp1Y = y;
          return;
        case 2:
          wasp2X = x;
          return;
        case 3:
          wasp3X = x;
          return;
        case 4:
          wasp4X = x;
          return;
      }
      return;
    }
  }
}

bool notWithinObjectPath(int x) {
  int plus = x + waspWidth + 2;
  int plus1X = wasp1X + waspWidth + 2;
  int plus2X = wasp2X + waspWidth + 2;
  int plus3X = wasp3X + waspWidth + 2;
  int plus4X = wasp4X + waspWidth + 2;
  
  if(plus != wasp1X 
    && plus != wasp2X 
    && plus != wasp3X 
    && plus != wasp4X
    && plus1X != x
    && plus2X != x
    && plus3X != x
    && plus4X != x) {
      return true;
    }
  return false; 
}

void drawHive() {
  Sprites::drawSelfMasked(hiveX, hiveY, hive, 0);
}

void moveBee() {
  if (arduboy.pressed(UP_BUTTON) && beeY > arduboyTop) {
    beeY --;
  } else if (arduboy.pressed(DOWN_BUTTON) && beeY + beeHeight < arduboyBottom) {
    beeY ++;
  } 
  if (arduboy.pressed(LEFT_BUTTON) && beeX > arduboyLeft) {
    beeX --; 
    movingLeft = true;
  } else if (arduboy.pressed(RIGHT_BUTTON) && beeX + beeWidth < arduboyRight) {
    beeX ++;
    movingLeft = false;
  }
}

void drawBee() {
  if(!movingLeft) {
    Sprites::drawSelfMasked(beeX, beeY, beeRight, 0);
  } else {
    Sprites::drawSelfMasked(beeX, beeY, beeLeft, 0);
  }
}
