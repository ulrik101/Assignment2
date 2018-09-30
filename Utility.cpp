
#include "Utility.h"
using namespace std;

int mirrorRetarget(int gridLimit, int coord)
{
  int retarget = coord;
  if(coord > gridLimit)
  {
    retarget = (gridLimit + 1) - (coord - gridLimit);
  }
  if(coord < 1)
  {
    retarget =  -1*coord + 1;
  }
  return retarget;
}

int torusRetarget(int gridLimit, int coord)//retargets coordinates to fit within the grid confines
{
  int retarget = coord;
  if(coord > gridLimit)
  {
    retarget = coord - gridLimit;
  }
  if(coord < 1)
  {
    retarget = gridLimit + coord;
  }


  return retarget;
}

bool getUserBool(std::string prompt, std::string boolTrue, std::string boolFalse)//prompts the user for a boolean answer. user must answer with either the second or third input
{
  std::string userInput = "";

  do
  {
    std::cout << prompt << std::endl;
    std::cin >> userInput;
  }while(userInput != boolTrue && userInput != boolFalse);//repeat while incorrect input is given. Stop when correct is given
  if(userInput == boolTrue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

float getUserFloat(std::string prompt)//prompts the user for a float answer.
{
  while(true)
  {
    try
    {
      float percent;
      std::cout << prompt << std::endl;
      cin >> percent;
      if(percent > 0 && percent <= 1)
      {
        return percent;
        break;
      }
      std::cin.clear();
      std::cin.ignore();
    }
    catch(const std::exception& e)
    {

    }
  }
}

int getUserInt(std::string prompt)//prompts the user for a int answer.
{
  while(true)
  {
    int num;
    std::cout << prompt << std::endl;
    try
    {

      std::cin >> num;
      if(num > 0 && num < 100)
      {
        return num;
        break;
      }
      std::cin.clear();
      std::cin.ignore();
    }
    catch(const std::exception& e)
    {

    }
  }
}


void clearConsole()
{
  for(int i = 0; i < 15; i ++)
  {
    std::cout << std::endl;
  }
}
