#include <iostream>
using namespace std;

int getBorderType();
void setBorderType(int type);

float setRandCellAmount(float percent);
bool getGridIndex(int x, int y);
bool getGridBackendIndex(int x, int y);
int getTotalLivingCells();

void setX(int x);
void setY(int y);
int getGridX();
int getGridY();
void printGrid();
void genGrid(int x, int y);
void toggleCellState(int x, int y);
void commitBackend();
bool gridStable();

/*
class Grid
{
  public:
    Grid();
    Grid(int x, int y);
    ~Grid();


};
*/
