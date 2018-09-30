#include "Utility.h"
#include "Grid.h"
#include "FileManagement.h"
#include "CellGen.h"


bool closeAppBool;


void closeApp()
{
  closeAppBool = true;
}

int main()
{
  closeAppBool = false;

  if(getUserBool("Enter 'random' for a random cell assignment, or 'file' for File Import.", "random","file")==true)//prompt for configuration type
  {
    //Random Generation
    int tempX = getUserInt("Insert Grid Length between 1 and 99: ");
    int tempY = getUserInt("Insert Grid Height between 1 and 99: ");
    float density = getUserFloat("Insert density between 0 and 1: ");
    setRandCellAmount(density);
    genGrid(tempX,tempY);
  }
  else
  {
    selectFile();//File Import Generation
  }

  if(getUserBool("Enter 'classic' for Classic Border mode, or 'other' for more options.", "classic","other")==false)//prompt for grid type
  {
    if(getUserBool("Enter 'mirror' for Mirror Border mode, or 'donut' for Donut Mode.", "mirror","donut")==true)//prompt for further grid type
    {
      setBorderType(1);
      std::cout<< "BorderType: " << getBorderType() << endl;//mirror border type
    }
    else
    {
      setBorderType(2);
      std::cout<< "BorderType: " << getBorderType() << endl;//donut border type
    }
  }
  else
  {
    setBorderType(0);
    std::cout<< "BorderType: " << getBorderType() << endl;//classic border type
  }

  if(getUserBool("Enter 'normal' for a brief pause between generations, or 'other' for more options.", "normal","other")==true)
  {
    setInbetweenGenMode(0);//sets for a small interval between generations
  }
  else
  {
    if(getUserBool("Enter 'manual' for manualy starting each next generations, or 'file' to output to a file.", "manual","file")==true)
    {
      setInbetweenGenMode(1);//requires manual input between generations
    }
    else
    {
      setInbetweenGenMode(2);//outputs to file for each generation
      createOutputFile();//creates the file for above
    }
  }
  clearConsole();//clears CMD console
  simulate();//starts the simulation
  return EXIT_SUCCESS;
}
