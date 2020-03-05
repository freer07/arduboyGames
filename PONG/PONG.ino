//Alexander Freer 
//29/02/2020

#include <Arduboy2.h>
Arduboy2 arduboy;

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

void setup() {
  arduboy.begin();
  //Seed the random number generator
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  arduboy.clear();

  bally = random(10,54);
  if (bally < 32) {
    ballDown = 1;
  } else {
    ballDown = -1;
  }
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
      arduboy.setCursor(0,0);
      arduboy.print("Title Screen");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 1;
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
        switch (cpuDiff) {
          //easy
          case 0:
            coolDown = 30;
            break;

          //med
          case 1:
            coolDown = 20;
            break;

          //hard
          case 2:
            coolDown = 10;
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
        ballx = 64;
        bally = random(10,54);
        if (bally < 32) {
          ballDown = 1;
        } else {
          ballDown = -1;
        }
      }
      if (arduboy.justPressed(A_BUTTON) || playerPoints == 5) {
        gamestate = 2;
      }
      else if (cpuPoints == 5) {
        gamestate = 3;
      }
      break;
      
    case 2:
      //Win Screen
      arduboy.setCursor(0,0);
      arduboy.print("You Win");
      if (arduboy.justPressed(A_BUTTON)) {
        reset();
        gamestate = 0;
      }
      break;
      
    case 3:
      //Lose Screen
      arduboy.setCursor(0,0);
      arduboy.print("You Lose");
      if (arduboy.justPressed(A_BUTTON)) {
        reset();
        gamestate = 0;
      }
      break;
  }

  arduboy.display();
}

void reset() {
  ballx = 64;
  bally = 0;
  playery = 0;
  cpuy = 0;
  ballRight = -1;
  ballDown = 1;
  coolDown = 0;
  cpuDiff = 0;
  bounce = false;
  playerPoints = 0;
  cpuPoints = 0;
}
