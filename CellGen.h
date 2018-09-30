#include <iostream>
using namespace std;

int getGenerationCount();
void setInbetweenGenMode(int type);
bool isNeighborAlive(int xCoord, int yCoord, int xDir, int yDir);

int countNeighbors(int xCoord, int yCoord);


void updateCellAndDeadNeighbors(int xCoord, int yCoord);
void nextGen();


void simulate();
