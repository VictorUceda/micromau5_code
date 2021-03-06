#include <StackList.h>
#include <stdarg.h>

//Include custom data types
#include "coord.h"
#include "entry.h"

#define NORTH 1
#define SOUTH 2
#define EAST 4
#define WEST 8
  //Define some global constants
  #define X 13
  #define Y 13


  entry maze[Y][X]; //maze matrix ¡¡Cuidado usa la Y y la X al reves ya que maze[0] es la FILA superior!!
  uint8_t headings[] = {1,2,4,8}; //N,S,E,W

//Variables para simulacion de un laberinto y comprobar la correccion
  uint8_t posXrobot=0;
  uint8_t posYrobot=12;
boolean mazeSol[27][27]={
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}; //matriz con posibles paredes en los indices pares y celdas en los impares. 0 si no hay pared 1 si si.

void pf(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

uint8_t wallsAt(uint8_t posX, uint8_t posY){
  uint8_t ret=0;
  uint8_t nX=posX*2+1;
  uint8_t nY=posY*2+1;
  //W=8,E=4,S=2,N=1
  if(!mazeSol[nY-1][nX])ret+=1; //no hay pared al norte
  if(!mazeSol[nY+1][nX])ret+=2; //no hay pared al sur
  if(!mazeSol[nY][nX-1])ret+=8; //no hay pared al oeste
  if(!mazeSol[nY][nX+1])ret+=4; //no hay pared al este
  //pf("DEBUG WALLSAT (%d,%d)=%d\n",posX,posY,ret);
  return ret;
}

/*
Imprime el esado actual de maze con las sitancias en las celdas
+----+
| 9  |
+----+
*/
void printMaze(){
  uint8_t i,j;
  for (j=0;j<Y;j++){
    for(i=0;i<X;i++){
      if(!(maze[j][i].walls & NORTH))
        Serial.print("+---+");
      else
        Serial.print("+   +");
    }
    Serial.println("");
    for(i=0;i<X;i++){
      if(!(maze[j][i].walls & WEST))
        Serial.print("|");
      else
        Serial.print(" ");
      if(i==posXrobot && j==posYrobot)
        pf("^%d",maze[j][i].distance);
      else
        pf(" %d",maze[j][i].distance);
      if(maze[j][i].distance < 10) pf(" ");
      if(!(maze[j][i].walls & EAST))
        Serial.print("|");
      else
        Serial.print(" ");
    }
    Serial.println("");
    for(i=0;i<X;i++){
      if(!(maze[j][i].walls & SOUTH))
        Serial.print("+---+");
      else
        Serial.print("+   +");
    }
    Serial.println("");

  }
}


void setup(){
  //instantiate an empty maze
  Serial.begin(115200);
  instantiate();
delay(1000);

}



void instantiate(){
  for(uint8_t j = 0; j<Y; j++){
    for(uint8_t i = 0; i<X; i++){
      maze[j][i].distance = calcCenter(i, j, X);
      maze[j][i].walls = 15;
      //If this is the left column (0,x)
      if(i==0){
        maze[j][i].walls = 7;
      }
      //if this is the top row
      if(j==0){
        maze[j][i].walls = 14;
      }
      //if this is the bottom row
      if(j==(Y-1)){
        maze[j][i].walls = 13;
      }
      //If this is the righ column
      if(i==(X-1)){
        maze[j][i].walls = 11;
      }
      maze[0][0].walls = 6;
      maze[Y-1][0].walls = 5;
      maze[0][X-1].walls = 10;
      maze[X-1][Y-1].walls = 9;
    }
  }
}
//Get the most optimistic distance between two coordinates in a grid
uint8_t calcDist(uint8_t posx, uint8_t posy, uint8_t desireX, uint8_t desireY){
  uint8_t dist = abs(desireY-posy)+abs(desireX-posx);
  return dist;
}

//Get the most optimistic distance between a given coordinate and a
//3x3 square in the center of a maze of dimension dim (dim must be even)
uint8_t calcCenter(uint8_t posx, uint8_t posy, uint8_t dim){
  uint8_t center = dim/2;
  uint8_t dist = 0;

  if(posy < center){
    if(posx < center){
      //You're in the top left of the maze
      dist=calcDist(posx, posy, (center-1), (center-1));
    }else if(posx == center){
      dist=calcDist(posx, posy, center, (center-1));
    }else{
      //You're in the bottom left of the maze
      dist=calcDist(posx,posy, (center+1),(center-1));
    }
  }else if(posy == center){
    if(posx < center){
      //You're in the top center of the maze
      dist=calcDist(posx, posy, center-1, center);
    }else if(posx == center){
      dist=0;
    }else{
      //You're in the bottom center of the maze
      dist=calcDist(posx,posy, center+1,center);
    }
  }else{
    if(posx < center){
      //You're in the bottom left of the maze
      dist=calcDist(posx,posy,(center - 1),(center + 1));
    }else if(posx == center){
      dist=calcDist(posx, posy, center, (center + 1));
    }else{
      //You're in the bottom right of the maze
      dist=calcDist(posx,posy,(center + 1),(center + 1));
    }
  }
return dist;
}

/*
INPUT: a coordinate representing a current position, and a heading
OUTPUT: the coordinates of the next desired position based on the heading and current position
*/
coord bearingCoord(coord currCoord, uint8_t heading){
  coord nextCoord = {0,0};
  switch (heading){
    case 1:
      //code
      nextCoord.x=currCoord.x;
      nextCoord.y=currCoord.y-1;
      break;
    case 2:
      nextCoord.x=currCoord.x;
      nextCoord.y=currCoord.y+1;
      break;
    case 4:
      nextCoord.x=currCoord.x+1;
      nextCoord.y=currCoord.y;
      break;
    case 8:
      nextCoord.x=currCoord.x-1;
      nextCoord.y=currCoord.y;
      break;
  }
  return nextCoord;
}

/*
INPUT: A Coord representing the current coordiante and the robots current heading
OUTPUT: An optimal direction away from the current coordinate.
*/
uint8_t orient(coord currCoord, uint8_t heading){
  //printMaze();
  //pf("DEBUG orient (%d,%d-%d)\n",currCoord.x,currCoord.y,heading);
  coord leastNext = {0,0};
  //This is the absolute largest value possible (dimension of maze squared)
  uint8_t leastNextVal = sizeof(maze)*sizeof(maze);
  uint8_t leastDir = heading;

  //If there is a bitwise equivalence between the current heading and the cell's value, then the next cell is accessible
  //pf("DEBUG orient if w(%d,%d)=%d(=%d) h=%d\n",currCoord.x,currCoord.y,maze[currCoord.y][currCoord.x].walls,wallsAt(currCoord.x,currCoord.y), heading);
  if((maze[currCoord.y][currCoord.x].walls & heading) != 0){
    //Define a coordinate for the next cell based onthis heading and set the leastNextVal t its value
    //pf("\tDEBUG orient test1 (%d,%d-%d)->", currCoord.x,currCoord.y,heading);
    coord leastnextTemp = bearingCoord(currCoord, heading);
    pf("(%d,%d)\n",leastnextTemp.x,leastnextTemp.y);
    if(checkBounds(leastnextTemp)){
      leastNext = leastnextTemp;
      leastNextVal = maze[leastNext.y][leastNext.x].distance;
    }
  }
  //pf("DEBUG orient partial result (%d,%d)=%d\n",leastNext.x,leastNext.y,leastNextVal);
  for(uint8_t i=0; i<sizeof(headings); i++){
    uint8_t dir = headings[i];
    //if this dir is accessible
    if((maze[currCoord.y][currCoord.x].walls & dir) != 0){
      //define the coordiante for this dir
      coord dirCoord = bearingCoord(currCoord,dir);

      if(checkBounds(dirCoord)){
        //if this dir is more optimal than continuing straight
        if(maze[dirCoord.y][dirCoord.x].distance < leastNextVal){
          //update teh value of leastNextVal
          leastNextVal = maze[dirCoord.y][dirCoord.x].distance;
          //update the value of leastnext to this dir
          leastNext = dirCoord;
          leastDir = dir;
          //pf("DEBUG orient actualizar minimo to h=%d, (%d,%d-%d)\n",leastDir,leastNext.x,leastNext.y,leastNextVal);
        }
      }
    }
  }
  return leastDir;
}

//Take a coordinate and test if it is within the allowable bounds
boolean checkBounds(coord Coord){
  if((Coord.x >= X) || (Coord.y >= Y) || (Coord.x < 0) || (Coord.y < 0))
    return false;
  else
    return true;
}

/*
INPUT: Coord
OUTPUT: An integer that is the least neighbor
*/
uint8_t checkNeighs(coord Coord){
  uint8_t minVal =  sizeof(maze)*sizeof(maze);
  for(int i=0; i<sizeof(headings); i++){
    uint8_t dir = headings[i];
    //if this dir is accessible
    if((maze[Coord.y][Coord.x].walls & dir) != 0){
      //Get the coordinate of the accessible neighbor
      coord neighCoord = bearingCoord(Coord, dir);
      //Check the value of the accessible neighbor
      if (checkBounds(neighCoord)){
        //if the neighbore is less than the current recording minimum value, update the minimum value
        //If minVal is null, set it right away, otherwise test
        if(maze[neighCoord.y][neighCoord.x].distance < minVal){minVal = maze[neighCoord.y][neighCoord.x].distance;}
      }
    }
  }
  return minVal;
}

//Given a coordinate, test and return if the coordinate is bounded on three sides
boolean isDead(coord coord){
  boolean deadEnd = false;
  if(checkBounds(coord)){
    uint8_t bounds = maze[coord.y][coord.x].walls;
    //bounds is the integer from the exploratory maze that represents the known walls of the coordinate
    if((bounds == 1)||(bounds == 2)||(bounds == 4) || (bounds == 8)){deadEnd=true;}
  }
  return deadEnd;
}

boolean isEnd(coord Coord, coord DesiredArray[]){
  boolean End = false;
  for(uint8_t i=0; i<sizeof(DesiredArray);i++){
    coord Desired = DesiredArray[i];
    if(checkBounds(Coord)){
      if((Coord.x == Desired.x)&&(Coord.y==Desired.y)){
        End = true;
      }
    }
  }
  return End;
}

/*
This function makes calls to the dispatcher to get the following info
  -orientation
  -surrounding walls
Using orientation and walls, this information is mapped to a map integer in the global coordinate frame
*/
uint8_t readCurrent(){
  //TODO: Fill this bitch out
  //return 0;

  return wallsAt(posXrobot, posYrobot);
}

uint8_t readAhead(){
  return 0;
}


/*
INPUT: Coordindate to update, and a direction representing the wall to add
OUTPUT: Update to coordinate adding the wall provided as an argument
*/
void coordUpdate(coord coordinate, uint8_t wallDir){
  if(checkBounds(coordinate)){
    if((maze[coordinate.y][coordinate.x].walls & wallDir) != 0){
      maze[coordinate.y][coordinate.x].walls = maze[coordinate.y][coordinate.x].walls-wallDir;
    }
  }
}

/*
INPUT: Current Robot coordinate
OUTPUT: Update maze for learned walls
*/
void floodFillUpdate(coord currCoord, coord desired[]){
  StackList<coord> entries;

  maze[currCoord.y][currCoord.x].walls=readCurrent();
  entries.push(currCoord);

  for(uint8_t i=0; i<sizeof(headings); i++){
    uint8_t dir = headings[i];
    //If there's a wall in this dir
    if((maze[currCoord.y][currCoord.x].walls & dir) == 0){
      //pf("direccion %d con paredes=%d\n",dir,maze[currCoord.y][currCoord.x].walls);
      coord workingCoord = {currCoord.x,currCoord.y};
      switch(dir){
        case 1:
          workingCoord.y=workingCoord.y-1;
          coordUpdate(workingCoord,2);
          break;
        case 2:
          workingCoord.y=workingCoord.y+1;
          coordUpdate(workingCoord,1);
          break;
        case 4:
          workingCoord.x=workingCoord.x+1;
          coordUpdate(workingCoord, 8);
          break;
       case 8:
         workingCoord.x=workingCoord.x-1;
         coordUpdate(workingCoord,4);
         break;
      }
      //If the workingEntry is a valid entry and not a dead end, push it onto the stack
      if(checkBounds(workingCoord)&&(!isEnd(workingCoord, desired))){
       // pf("DEBUG\t a la cola-> (%d,%d)\n",workingCoord.x,workingCoord.y);
        entries.push(workingCoord);
      }
    }
  }
  //pf("DEBUG\tNumero en la cola: %d\n",entries.count());

  //While the entries stack isn't empty
  while(!entries.isEmpty()){
    //Pop an entry from the stack
    coord workingEntry = entries.pop();
    uint8_t neighCheck = checkNeighs(workingEntry);
    //pf("DEBUG\t vecino minimo de (%d,%d) es: %d\n",workingEntry.x,workingEntry.y,neighCheck);
    //If the least neighbor of the working entry is not one less than the value of the working entry
    if(neighCheck+1!=maze[workingEntry.y][workingEntry.x].distance){
      maze[workingEntry.y][workingEntry.x].distance=neighCheck+1;
      for(uint8_t i=0;i<sizeof(headings);i++){
        uint8_t dir = headings[i];
        if((maze[workingEntry.y][workingEntry.x].walls & dir) != 0){
          coord nextCoord = bearingCoord(workingEntry,dir);
          if(checkBounds(nextCoord)){
            if(!isEnd(nextCoord, desired)){
              entries.push(nextCoord);
            }
          }
        }
      }
    }
  }
}

void floodFill(coord desired[], coord currCoord, boolean isMoving){

  uint8_t heading = 1;
  /*Integer representation of heading
  * 1 = N
  * 4 = E
  * 2 = S
  * 8 = W
  */
  while(maze[currCoord.y][currCoord.x].distance != 0){

      floodFillUpdate(currCoord, desired);
      //Serial.println("END UPDATE");
      printMaze();
      uint8_t nextHeading = orient(currCoord, heading);
      coord nextCoord = bearingCoord(currCoord, nextHeading);
      //TODO: ADD MOVING INSTRUCTIONS HERE
      if(isMoving){
         pf("\tmovimiento: (%d,%d)->(%d,%d) [heading %d->%d]\n",currCoord.x,currCoord.y,nextCoord.x,nextCoord.y,heading,nextHeading);
      }
      posXrobot=nextCoord.x;
      posYrobot=nextCoord.y;

      //This should occur as a callback of the moving finishing
      currCoord = nextCoord;
      heading = nextHeading;
  }
}


void resetToCoord(coord desiredCoord){
  for(int j = 0; j<Y; j++){
    for(int i = 0; i<X; i++){
      maze[j][i].distance = calcDist(i, j, desiredCoord.x, desiredCoord.y);
    }
  }
}
void instantiateReflood(){
  for(int j = 0; j<Y; j++){
    for(int i = 0; i<X; i++){
      maze[j][i].distance = calcCenter(i, j, X);
    }
  }
}


void createSpeedQueue(){
  /*coord workingCoord = globalCoord;
  byte workingDir = globalHeading;
  int workingDist = 7.74;
  while((workingCoord.x!=globalEnd.x)&&(workingCoord.y!=globalEnd.y)){
    byte optimalDir = orient(workingCoord, workingDir);

    //If the direction is the same, accumulate distance
    if(optimalDir==workingDir){
      workingDist+=7.74;
    }else{
      //if the optimal is different from the working, add the working and the accumulated distance
      instruction nextInstruction = {workingDist, optimalDir};
      instructions.push(nextInstruction);
      //Reset the distance to one square and update the workingDir
      workingDist = 7.74;
      workingDir = optimalDir;
    }

    //update workingCoord to the next optimal coord
    workingCoord = bearingCoord(workingCoord, optimalDir);
  }*/
}

void reflood(){
  //Refill the maze for most optimistic values, but now the maze has walls
  instantiateReflood();

  //Run flood fill but without actual motion
  coord desired[] = {{4,5},{4,6},{4,4},{5,5},{5,6},{5,4},{6,5},{6,6},{6,4}};
  coord currCoord = {0,12};
  floodFill(desired, currCoord, false);

  //Now, the robot is still at the start, but the maze distance values have been updated with the walls discovered
  //So we follow the maze creating instructions
  createSpeedQueue();
  //We now have a queue of instructions.

}

void loop(){
  uint8_t i=0;
  pf("INI_LOOP%d\n",i++);
  coord desired[] = {{4,5},{4,6},{4,4},{5,5},{5,6},{5,4},{6,5},{6,6},{6,4}};
  floodFill(desired, {0,12},true);
  printMaze();
  Serial.println("VOLVIENDO AL ORIGEN");
  coord returnCoord[] = {{0,12}};
  resetToCoord(returnCoord[0]);
  floodFill(returnCoord, {posXrobot,posYrobot},true);

  reflood();
  printMaze();
  while(1);
}
