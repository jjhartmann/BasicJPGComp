#include "umatrix.h"
#include <iostream>
using namespace std;

uMatrix::uMatrix(int x, int y)
{
    sizeX = x;
    sizeY = y;

    uMat = new matTable(x, matRow(y));
}
uMatrix::~uMatrix(){
    delete uMat;
}

int uMatrix::getPoint(int x, int y){

    if(y >= sizeY || x >= sizeX){
        std::cout << "Error! - Size out of bounds - uMatrix::getPoint -: " << endl;
        return 0;
    } else {
    return  (*uMat)[x][y];
    };


}

void uMatrix::setPoint(int x, int y, int set){

    if(y >= sizeY || x >= sizeX){
        std::cout << "Error! - Size out of bounds - uMatrix::setPoint -  " << sizeX << " " << sizeY << " ";
        std::cout << x << " " << y << "  Set is: " << set << endl;
    } else {
    (*uMat)[x][y] = set;
    };
}

int uMatrix::getSizeX(){
    return sizeX;
}

int uMatrix::getSizeY(){
    return sizeY;
}

bool uMatrix::empty(){
    if(sizeX == 0 && sizeY == 0){
        return true;
    } else {
        return false;
    }
}
