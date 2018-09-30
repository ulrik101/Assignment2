#include<stdlib.h>
#include "Grid.h"
#include <iostream>
#include <experimental/random>
#include <cstring>
#include <algorithm>
#include <iterator>
#include "Utility.h"

using namespace std;

std::string cellAlive = "X";
std::string cellDead  = "-";
int borderType;//classic/mirror/donut
int gridX;//width limit
int gridY;//height limit
int totalCells;
int totalLivingCells;
float randCellAmount;
bool grid[100][100];
bool gridBackend[100][100];

float setRandCellAmount(float percent)
{
  randCellAmount = percent;
}
int getBorderType()
{
  return borderType;
}
void setBorderType(int type)
{
  borderType = type;
}

bool getGridIndex(int x, int y)//returns index at that point in main grid
{
  bool val = grid[x][y];
  if(borderType == 2)//adjusts for torus mode
  {
    val = grid[torusRetarget(gridX,x)][torusRetarget(gridY,y)];
  }
  return val;
}

bool getGridBackendIndex(int x, int y)//returns index at that point in backend grid
{
  bool val = gridBackend[x][y];
  if(borderType == 2)//adjusts for torus mode
  {
    val = gridBackend[torusRetarget(gridX,x)][torusRetarget(gridY,y)];
  }
  return val;
}

void setX(int x)
{
  gridX = x;
}
void setY(int y)
{
  gridY = y;
}
int getGridX()
{
  return gridX;
}
int getGridY()
{
  return gridY;
}

int getTotalLivingCells()
{
  return totalLivingCells;
}

void randCellAlive()//randomly picks a point and turns it alive if it is dead. restarts if point found is alive.
{
  int randX = std::experimental::randint(1,gridX);
  int randY = std::experimental::randint(1,gridY);
  if(gridBackend[randX][randY]==false)
  {
    toggleCellState(randX,randY);
  }
  else
  {
    randCellAlive();
  }
}

void toggleCellState(int x, int y)//switches the value of the cell at the given point. adds or removes from the living counter
{
  if(gridBackend[x][y]==false)
  {
    totalLivingCells+=1;
  }
  else
  {
    totalLivingCells-=1;
  }
  gridBackend[x][y] = !gridBackend[x][y];
}

void genGrid(int x, int y)//sets the grid up with the width, height, and density
{
  gridX = x;
  gridY = y;
  totalCells = x*y;
  totalLivingCells = 0;
  float limit = totalCells * randCellAmount;
  for(int i = 1; i <= limit; i++)
  {
    randCellAlive();
  }
}

void printGrid()//prints out the grid
{
  for(int y = gridY; y >= 1; y--)
  {
    for(int x = 1; x <= gridX; x++)
    {
      if(gridBackend[x][y]==true)
      {
        std::cout << cellAlive;
      }
      else
      {
        std::cout << cellDead;
      }
    }
    std::cout << std::endl;
  }
}

void commitBackend()//makes the main grid equal to the backend
{
  memcpy( grid, gridBackend, sizeof(grid) );
}

bool gridStable()//determins if the grid and the backend are the same. used to determin if it has stabilized
{
  for(int x = 1; x <= gridX; x++)
  {
    for(int y = 1; y <= gridY; y++)
    {
      if(grid[x][y] != gridBackend[x][y])
      {
        return false;
      }
    }
  }
  return true;
}
