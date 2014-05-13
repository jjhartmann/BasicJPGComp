#ifndef UMATRIX_H
#define UMATRIX_H
#include <vector>
#include <memory>
using namespace std;
class uMatrix
{
public:
    uMatrix(int x, int j);
    ~uMatrix();

    //Return int form xy
    int getSizeX() ;
    int getSizeY() ;
    bool empty();
    int getPoint(int x, int y);
    void setPoint(int x, int y, int set);


private:
    int sizeX;
    int sizeY;

    typedef vector<int> matRow;
    typedef vector<matRow> matTable;

    matTable *uMat;
};

#endif // UMATRIX_H
