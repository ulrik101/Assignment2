#include<fstream>
#include<iostream>
#include "Utility.h"
#include<algorithm>
#include<stdexcept>
#include "CellGen.h"
#include "Grid.h"

using namespace std;
std::string outputFileName;


void setArrayFromFile(std::string filename, int x, int y)//sets the backend grid up from a file
{
  ifstream file(filename);
  setX(x);
  setY(y);
  if(file.is_open())
  {
    int lineCount = 0;
    while(!file.eof())
    {
      lineCount +=1;
      std::string local_string;
      file >> local_string;
      if(lineCount > 2)
      {
        for(int e = 0; e < x; e++)
        {
          if(local_string[e] == 'X')
          {
            int localx=e+1;
            int localy=lineCount-3;
            toggleCellState(localx, (y-localy));
          }
        }
      }
    }
  }
}


//Listen, lets pretend the below method doesnt exist.
void selectFile()//selects file for import and does error checking
{
  bool loaded = false;
  int fileX;
  int fileY;
  while(true)
  {
    std::string filename = "";
    std::cout<< "Insert the exact name and extension for the starter game: " << endl;
    std::cin >> filename;
    ifstream file(filename);
    try
    {
      fileX = 0;
      fileY = 0;
      int lineCount = 0;
      ifstream file(filename);
      if(file.is_open())//if file is open
      {
        while(!file.eof())//while there is a next line
        {
          std::string local_string;
          file >> local_string;
          if(lineCount <= 1)//sets the X and Y value of the grid from the first two lines
          {
              int tempInt = std::stoi (local_string,nullptr,10);
              if(tempInt > 0 && tempInt <=100)
              {
                if(lineCount < 1)
                {
                  fileY = tempInt;//sets grid height
                }
                else
                {
                  fileX = tempInt;//sets grid width
                }
              }
              else
              {
                throw std::exception();
              }
          }
          if(lineCount > 1)//reads the rest of the grid
          {
            int count = std::count(local_string.begin(),local_string.end(), 'X') + std::count(local_string.begin(),local_string.end(), '-');

            if(local_string.size()!=fileX || lineCount > fileY+2 || local_string.size()!=count)//checks the dimensions of the supplied grid to confirm it is the same as the ints above. Also Checks for invalid characters
            {
              throw std::exception();
            }
          }
          lineCount+=1;
        }
        loaded = true;
      }
      if (loaded == true)//checks to see if file was properly loaded
      {
        setArrayFromFile(filename, fileX, fileY);
      }
      else
      {
        throw std::exception();
      }
      file.close();
      break;
    }
    catch(const std::exception& e)
    {
      std::cout<< "Incorrect File Format. Read the Readme.txt for more info about format. " << endl;
      file.close();
    }
  }
}

void createOutputFile()//creates the output file
{
  std::cout<< "Insert the exact name and extension for the output file: " << endl;
  std::cin >> outputFileName;//user input
  ofstream outputFile;
  outputFile.open(outputFileName);
  outputFile.close();
}

void printArrayToFile()//prints the grid to the supplied output file
{
  ofstream outputFile;
  outputFile.open(outputFileName, ios::out | ios::app);
  outputFile << endl << endl << getGenerationCount()<<endl;
  for(int y = getGridY(); y >= 1; y--)
  {
    for(int x = 1; x <= getGridX(); x++)
    {
      if(getGridIndex(x,y)==true)
      {
        outputFile << "X";
      }
      else
      {
        outputFile << "-";
      }
    }
    outputFile << endl;
  }
  outputFile.close();
}
