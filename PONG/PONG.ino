//Alexander Freer 
//29/02/2020

#include <Arduboy2.h>
#include "Tinyfont.h"
Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

const unsigned char PROGMEM PongPaddle[] =
{
// width, height,
16, 24,
0x00, 0x00, 0x00, 0xe0, 0x30, 0x18, 0x08, 0x08, 0x08, 0x08, 0x18, 0x30, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0f, 0x18, 0x10, 0xf0, 0x10, 0x10, 0xf0, 0x10, 0x18, 0x0f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

int gamestate = 0;
int ballx = 64;
int bally = 0;
int ballSize = 4;
int ballRight = -1; //neg numbers for left
int ballDown = 1; //neg numbers for up
int paddleWidth = 4;
int paddleHeight = 9;
int playerx = 0;
int playery = 0;
int cpux = 123;
int cpuy = 0;
int playerPoints = 0;
int cpuPoints = 0;
int cpuDiff = 0;
int coolDown = 0;
bool bounce = false;
int PongPaddlex = 0;
int PongPaddley = 0;
bool newBall = true;
bool pause = false;
int backGroundx = 0;
int backGroundy = 0;
bool subtract = false;

void setup() {
  arduboy.begin();
  //Seed the random number generator
  arduboy.initRandomSeed();
  arduboy.setFrameRate(10);
  arduboy.clear();
}

void loop() {

  //This prevents the arduboy from running too fast
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.clear();

  arduboy.pollButtons();

  //Game Code here 
  switch (gamestate) {
    
     case 0:
     //Title Screen
      bally = random(20,44);
      if (bally < 32) {
      ballDown = 1;
      } else {
        ballDown = -1;
      }
      newBall = true;
      drawBackground();
      arduboy.setCursor(42,20);
      arduboy.print("P O N G");
      tinyfont.setCursor(26,40);
      tinyfont.print("press A to play");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 1;
        arduboy.setFrameRate(60);
      }
      break;
      
    case 1:
      //Play Game
      //Game Logic here
      //-----------------

      //draw points
      arduboy.setCursor(12,0);
      arduboy.print(playerPoints);
      arduboy.setCursor(111,0);
      arduboy.print(cpuPoints);
      
      //draw the ball and paddles
      arduboy.fillRect(ballx, bally, ballSize, ballSize, WHITE);
      arduboy.fillRect(playerx, playery, paddleWidth, paddleHeight, WHITE);
      arduboy.fillRect(cpux, cpuy, paddleWidth, paddleHeight, WHITE);
      
      if(newBall) {
        newBall = false;
        pause = true;
      }

      //does logic for cooldown
      if (coolDown > 0) {
        coolDown --;
      }

      //control our paddle
      if (arduboy.pressed(UP_BUTTON) && playery > 0) {
        playery = playery - 1;
      }
      if (arduboy.pressed(DOWN_BUTTON) && playery + paddleHeight < 63) {
        playery = playery + 1;
      }

      //Computer paddle control
      if (coolDown == 0) {
        if (bally > cpuy && cpuy + paddleHeight + 1 < 63) {
          cpuy ++;
        } else if (bally < cpuy && cpuy - 1 > 0) {
          cpuy --;
        }
      }
      
      //move the ball right
      if (ballRight == 1) {
        ballx = ballx + 1;
      }
      //move the ball left
      if (ballRight == -1) {
        ballx = ballx - 1;
      }
      //move ball down
      if (ballDown == 1) {
        bally = bally + 1;
      }
      //move ball up 
      if (ballDown == -1) {
        bally = bally - 1;
      }

      //Reflect the ball off the paddle
      if(ballx == playerx + paddleWidth && playery < bally + ballSize && playery + paddleHeight > bally) {
        ballRight = 1;
        bounce = true;
      }
      //Reflect the ball off the cpu paddle
      else if(ballx + ballSize == cpux && cpuy < bally + ballSize && cpuy + paddleHeight > bally) {
        ballRight = -1;
        bounce = true;
      }
      //reflect off top
      if (bally == 0) {
        ballDown = 1;
        bounce = true;
      }
      //reflect off bottom
      else if (bally + ballSize == 63) {
        ballDown = -1;
        bounce = true;
      }

      if (bounce) {
        bounce = false;
        cpuDiff = random(0,2);
        switch (cpuDiff) {
          //slow
          case 0:
            coolDown = 15;
            break;

          //fast
          case 1:
            coolDown = 0;
            break;
        }
      }

      //if an edge is reached
      if(ballx + ballSize < 0 || ballx > 127) {
        if (ballx > 127) {
          playerPoints ++;
        } else {
          cpuPoints ++;
        }
        newBall = true;
        ballx = 64;
        ballRight = -1; //neg numbers for left
        bally = random(20,44);
        if (bally < 32) {
          ballDown = 1;
        } else {
          ballDown = -1;
        }
      }
      if (playerPoints == 5) {
        gamestate = 2;
        arduboy.setFrameRate(10);
      }
      else if (cpuPoints == 5) {
        gamestate = 3;
        arduboy.setFrameRate(10);
      }
      break;
      
    case 2:
      //Win Screen
      drawBackground();
      arduboy.setCursor(40,20);
      arduboy.print("You Win!");
      if (arduboy.justPressed(A_BUTTON)) {
        reset();
        gamestate = 0;
      }
      break;
      
    case 3:
      //Lose Screen
      drawBackground();
      arduboy.setCursor(30,20);
      arduboy.print("You Lose :(");
      if (arduboy.justPressed(A_BUTTON)) {
        reset();
        gamestate = 0;
      }
      break;
  }

  arduboy.display();
  
  if(pause) {
    pause = false;
    delay(1000);
  }
}

void reset() {
  ballx = 64;
  bally = 0;
  playery = 0;
  cpuy = 0;
  ballRight = -1;
  ballDown = 1;
  coolDown = 0;
  bounce = false;
  playerPoints = 0;
  cpuPoints = 0;
}

void drawBackground() {
  if(subtract) {
    backGroundx --;
  } else {
    backGroundx ++;
  }
  if(backGroundx > 7 || backGroundx < 0) {
    backGroundy ++;
    if(backGroundx > 7) {
      backGroundx = 7;
      subtract = true;
    } 
    if (backGroundx < 0) {
      backGroundx = 0;
      subtract = false;
    }
    if(backGroundy > 2) {
      backGroundy = 0;
    }
  }
  for(int x = 0; x <= 112; x = x + 16) {
    for(int y = -1; y <= 63; y = y + 24) {
      if(x/16 == backGroundx && (y+1)/24 == backGroundy) {
        Sprites::drawOverwrite(x, y, PongPaddle, 0);
      }
    }
  }
}
