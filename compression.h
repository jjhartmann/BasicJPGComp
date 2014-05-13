#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <QImage>
#include <QColor>
#include "umatrix.h"

using namespace std;




class Compression
{
public:
    Compression();
    void rgbToYUV(const QImage *img);
    void yuvToRGB(uMatrix *imgY, uMatrix *imgU, uMatrix *imgV);
    void DCT();

    QImage *imgY;
    QImage *imgU;
    QImage *imgV;

    QImage *compressedImage;


    uMatrix *matY;
    uMatrix *matU;
    uMatrix *matV;


private:
    QRgb returnYUV(QColor imgColor, int x);
    int freturnYUV(QColor imgColor, int x);
    int ireturnRGB(int Y, int U, int V, int index);
    float wMatYUV[3][3];
    float wMatRGB[3][3];

};

#endif // COMPRESSION_H
