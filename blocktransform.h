#ifndef BLOCKTRANSFORM_H
#define BLOCKTRANSFORM_H
#include <vector>
#include <QImage>
#include "umatrix.h"

using namespace std;

enum TYPE_YUV{LAYER_Y, LAYER_U, LAYER_V };

struct eRCL {
    int zrs;
    int e;
    bool EOB = false;
};


class BlockTransform
{
public:
    BlockTransform();
    void constructRclDp(uMatrix img,  TYPE_YUV LAYER);
    void saveCompressedImage();


    //TESTING - PUBLIC FUNCTIONS
    void printPreRLC();
    void printDPCM();
    void printRCL();
    void printCImage();

    //PUBLIC CONTAINER COMPRESSED IMAGE
     uMatrix *compressedImage;
private:

    //FUnction Declaration
   void DCT(int (&matInt)[8][8], float (&DCTMatrix)[8][8]);
   void inverseDCT(int (&DCTMatrix)[8][8], float (&iDCTMatrix)[8][8]);
   void QuantizeY(float (&matInt)[8][8],int (&quantI)[8][8]);
   void QuantizeUV(float (&matInt)[8][8],int (&quantI)[8][8]);
   void iQuantizeY(int (&matInt)[8][8],int (&quantI)[8][8]);
   void iQuantizeUV(int (&matInt)[8][8],int (&quantI)[8][8]);
   void SaveRLC_DPCM(int (&quantI)[8][8]);
   void Save_RLE();
   void createDCTTable();




   //****CONST VARIABLES*****
   //Quantize Tables CONST
   int const lumaQ[8][8] = {{16, 11, 10, 16, 24,  40,  51,  61},
                            {12, 12, 14, 19, 26,  58,  60,  55},
                            {14, 13, 16, 24, 40,  57,  69,  56},
                            {14, 17, 22, 29, 51,  87,  80,  62},
                            {18, 22, 37, 56, 68,  109, 103, 77},
                            {24, 35, 55, 64, 81,  104, 113, 92},
                            {49, 64, 78, 87, 103, 121, 120, 101},
                            {72, 92, 95, 98, 112, 100, 103, 99}};



   int const chromaQ[8][8] = {{17, 18, 24, 47, 99, 99, 99, 99},
                         {18, 21, 26, 66, 99, 99, 99, 99},
                         {24, 26, 56, 99, 99, 99, 99, 99},
                         {47, 66, 99, 99, 99, 99, 99, 99},
                         {99, 99, 99, 99, 99, 99, 99, 99},
                         {99, 99, 99, 99, 99, 99, 99, 99},
                         {99, 99, 99, 99, 99, 99, 99, 99},
                         {99, 99, 99, 99, 99, 99, 99, 99}};

  //declare PI Const
  double const PI = 3.14159265359;

   //Final Storage CONTAINERS
  float dctTable[8][8];
   vector<int> preCompImage;
   vector<eRCL> matRLC;
   vector<int> preRCL;
   vector<int> DPCM;
   vector<int> DPCM_temp;


};

#endif // BLOCKTRANSFORM_H
