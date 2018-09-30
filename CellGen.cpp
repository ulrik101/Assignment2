#include "Grid.h"
#include "Utility.h"
#include "FileManagement.h"
#include <thread>
#include <chrono>
int generationCount;
int inbetweenGenMode;

int getGenerationCount()
{
  return generationCount;
}

void setInbetweenGenMode(int type)
{
  inbetweenGenMode = type;
}

bool isNeighborAlive(int xCoord, int yCoord, int xDir, int yDir)//the xDir and yDir are units away from x and y Coord.
{
  int tempX = xCoord+xDir;
  int tempY = yCoord+yDir;
  switch(getBorderType())
  {
    case 0://normal border mode
      tempX = xCoord+xDir;
      tempY = yCoord+yDir;
      if(tempX > getGridX() || tempY > getGridY())
      {
        return false;
      }
      break;
    case 1://mirrored border mode
      tempX = mirrorRetarget(getGridX(), xCoord + xDir);
      tempY = mirrorRetarget(getGridY(), yCoord + yDir);
      break;
    case 2://torus border mode
      tempX = torusRetarget(getGridX(), xCoord + xDir);
      tempY = torusRetarget(getGridY(), yCoord + yDir);
      break;
  }
  getGridIndex(tempX, tempY);
}

int countNeighbors(int xCoord, int yCoord)//counts the amount of living neighbors a space has
{
  int neighborCount = 0;
  for (int xDir = 1; xDir >= -1; xDir--)
  {
    for (int yDir = 1; yDir >= -1; yDir--)
    {
      if(yDir != 0 || xDir != 0)//to prevent counting self
      {
        if(isNeighborAlive(xCoord, yCoord, xDir, yDir))
        {
          neighborCount+=1;
        }
      }
    }
  }
  return neighborCount;
}

void updateCellAndDeadNeighbors(int xCoord, int yCoord)//updates specified living cell and tries to adjust neightbors
{
  int neighborCount = countNeighbors(xCoord,yCoord);
  //Edit Living Cell
  if(getGridIndex(xCoord, yCoord) && getGridBackendIndex(xCoord, yCoord))//if cell is alive in both grid and backend
  {
    switch(neighborCount)
    {
      case 0:
      case 1:
      toggleCellState(xCoord,yCoord);//too few neighbors
      break;
      case 2:
      case 3://stable
      break;
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      toggleCellState(xCoord,yCoord);//not enough neighbors
      break;
    }
  }

  //Edit Dead Cell Neighbors
  for (int xDir = 1; xDir >= -1; xDir--)
  {
    for (int yDir = 1; yDir >= -1; yDir--)
    {
      if(getGridIndex(xCoord + xDir, yCoord + yDir)==false && getGridBackendIndex(xCoord + xDir, yCoord + yDir)==false)//if cell is dead in both grid and backend, prevents cell from being edited more than once per generation
      {
      if((yDir != 0 || xDir != 0) && getGridIndex(xCoord + xDir, yCoord + yDir) == false)//to prevent counting self or living cells
        {
          int x = xCoord + xDir;
          int y = yCoord + yDir;
          int otherNeighbors=countNeighbors(x,y);
          if(getBorderType()==2)//retargets cells for torus/donut mode
          {
            x = torusRetarget( getGridX(), x);
            y = torusRetarget( getGridY(), y);
            otherNeighbors=countNeighbors(x,y);
          }
          if(otherNeighbors==3)//if there are three living neighbors, switch state to living
          {
            toggleCellState(x,y);
          }
        }
      }
    }
  }
}

void nextGen()//function for starting the next generation cycle
{
  generationCount+=1;
  for(int y=1;y<=getGridY();y++)
  {
    for(int x=1;x<=getGridX();x++)
    {
      if(getGridIndex(x,y))
      {
        updateCellAndDeadNeighbors(x,y);
      }
    }
  }
}

void simulate()//starts the entire simulation
{
  int livingCells = getTotalLivingCells();
  bool stopSim = false;
  clearConsole();
  std::cout << generationCount << std::endl;//prints out current generation count
  printGrid();
  commitBackend();//commits backend to main grid

  std::string newLine;
  if(inbetweenGenMode == 0)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  if(inbetweenGenMode == 1)
  {
    std::getline(std::cin, newLine);
    std::getline(std::cin, newLine);
  }
  if(inbetweenGenMode == 2)
  {
    printArrayToFile();
  }

  while(livingCells != 0 && stopSim == false)
  {
    clearConsole();
    nextGen();
    std::cout << generationCount << std::endl;
    printGrid();
    stopSim = gridStable();
    commitBackend();
    livingCells = getTotalLivingCells();
    if (stopSim)//if simulation is stable, end game
    {
      std::cout << "Game Stable, please press enter to end game. "<< std::endl;
      std::getline(std::cin, newLine);
      std::getline(std::cin, newLine);
    }
    if(inbetweenGenMode == 0)//inbetween generation pause
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if(inbetweenGenMode == 1)//manual generation
    {
      std::getline(std::cin, newLine);
    }
    if(inbetweenGenMode == 2)//output to file for each generation
    {
      printArrayToFile();
    }
  }
}
