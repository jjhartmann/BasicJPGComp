#include "compression.h"
#include "math.h"
#include <QRgb>
#include <iostream>
using namespace std;


//********* Constructor  ****************
Compression::Compression()
{

    // Initialize the Matrix - YUV
    wMatYUV[0][0] = 0.299;
    wMatYUV[0][1] = 0.587;
    wMatYUV[0][2] = 0.114;
    wMatYUV[1][0] = 0.14713;
    wMatYUV[1][1] = (-0.28886);
    wMatYUV[1][2] = 0.436;
    wMatYUV[2][0] = 0.615;
    wMatYUV[2][1] = (-0.51499);
    wMatYUV[2][2] = (-0.10001);

    // Initialize the Matrix - RGB
    wMatRGB[0][0] = 1.0;
    wMatRGB[0][1] = 0;
    wMatRGB[0][2] = 1.13983;
    wMatRGB[1][0] = 1.0;
    wMatRGB[1][1] = (-0.38465);
    wMatRGB[1][2] = (-0.58060);
    wMatRGB[2][0] = 1.0;
    wMatRGB[2][1] = (2.03211);
    wMatRGB[2][2] = (0);



}


//**************************************************
// RGB TO YUV
//**************************************************
void Compression::rgbToYUV(const QImage *img){
    const int width = img->width();
    const int height = img->height();

    //Create Image file for Viewing
    imgY = new QImage(width, height, QImage::Format_RGB32);
    imgU = new QImage(width/2, height/2, QImage::Format_RGB32);
    imgV = new QImage(width/2, height/2, QImage::Format_RGB32);


    matY = new uMatrix(width, height);
    matU = new uMatrix(width/2, height/2);
    matV = new uMatrix(width/2, height/2);


    QColor t;

    for(int i = 0; i < height; i++){

        // Second Forloop
        for(int j = 0; j < width; j++){

            t.setRgb(img->pixel(j,i));

            //Convert Pixels to YUV
            // For Y
            imgY->setPixel(j,i, returnYUV(t,0));
            matY->setPoint(j, i, freturnYUV(t, 0));

            //For U and V
            if(i%2==0 && j%2==0){
                // U
                imgU->setPixel(j/2,(i/2),  returnYUV(t,1));
                matU->setPoint(j/2,(i/2),  freturnYUV(t,1)+128);

                // V
                imgV->setPixel(j/2, (i/2),  returnYUV(t,2));
                matU->setPoint(j/2,(i/2),   freturnYUV(t,2)+128);



            } // IF Statement End

//            std::cout << "OUTSIDE THE IF.. \n";
        }// FOR 2 ENd


    } // FOR 1 END


}

//**************************************************
// YUV TO RGB
//**************************************************

void Compression::yuvToRGB( uMatrix *uMatY,  uMatrix *uMatU,  uMatrix *uMatV){
     int  width = uMatY->getSizeX();
     int  height = uMatY->getSizeY();

    int YVAL, UVAL, VVAL;

    //Create Image file for Viewing
    compressedImage = new QImage(width, height, QImage::Format_RGB32);





    QColor t;

    for(int i = 0; i < height; i++){

        // Second Forloop
        for(int j = 0; j < width; j++){

            YVAL = uMatY->getPoint(j,i);

            if(i%2==0 && j%2==0){
               VVAL = uMatV->getPoint(j/2,(i/2));
               UVAL = uMatU->getPoint(j/2,(i/2));
            }

            //CREATE RGB VALUE
            t.setRgb(ireturnRGB(YVAL, VVAL, UVAL, 0), ireturnRGB(YVAL, VVAL, UVAL, 1), ireturnRGB(YVAL, VVAL, UVAL, 2) );

            //SET COMPRESSED IMAGE VALUE
            compressedImage->setPixel(j, i, t.rgb());


//            std::cout << "OUTSIDE THE IF.. \n";
        }// FOR 2 ENd


    } // FOR 1 END


}




QRgb Compression::returnYUV(QColor imgColor, int x){


      int result =  wMatYUV[x][0]*imgColor.red() +
                    wMatYUV[x][1]*imgColor.green() +
                    wMatYUV[x][2]*imgColor.blue();

      switch(x)
      {
      case 0:
          imgColor.setRgb(result,result,result);
          break;
      case 1:
          result += 128;
          imgColor.setRgb(result,result,result);
          break;
      case 2:
          result += 128;
          imgColor.setRgb(result,result,result);
          break;
      }


//    std::cout << "   Inside returnYUV: " << result;
     return imgColor.rgb();


};

//********************************************
//Return the flaot to form Matrix with cv::Mat
int Compression::freturnYUV(QColor imgColor, int x){


      float result =  wMatYUV[x][0]*imgColor.red() +
                      wMatYUV[x][1]*imgColor.green() +
                      wMatYUV[x][2]*imgColor.blue();


//     std::cout << "   Inside returnYUV: " << result;
     return round(result);


};

int Compression::ireturnRGB(int Y, int U, int V, int index){


      float result =  wMatRGB[index][0]*Y+
                      wMatRGB[index][1]*U +
                      wMatRGB[index][2]*V;


//     std::cout << "Inside ireturnRGB: " << result << endl;
     return round(result);


};

