#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QImage;
    jComp = new Compression;
    buildY = new BlockTransform;
    buildU = new BlockTransform;
    buildV = new BlockTransform;


}

MainWindow::~MainWindow()
{
    delete ui;
}



//*************************************
// Load a Image into QImage Container.
//*************************************
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath());

    //Debug File Name
    ui->label_debug->setText(filename);

    if(!filename.isEmpty()){ //Test for Error
        image->load(filename);

        if (image->isNull()) { //Test for Error
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot Load %1").arg(filename));

        }
    }

//  Load Image into the Viewer Before YUV Conversion
    ui->imageRAW->setPixmap(QPixmap::fromImage(*image));
    ui->imageRAW->setScaledContents(true);


}

//********************************************
// ** Create and Seperate the YUV of the Image
// ** THis is using chroma subsampling 420
//********************************************
void MainWindow::on_pushButton_2_clicked()
{
    if(!image->isNull()){
    jComp->rgbToYUV(image);
//  Load Image into the Viewer Before YUV Conversion
    ui->imageY->setPixmap(QPixmap::fromImage(*jComp->imgY));
    ui->imageY->setScaledContents(true);

    ui->imageU->setPixmap(QPixmap::fromImage(*jComp->imgU));
    ui->imageU->setScaledContents(true);

    ui->imageV->setPixmap(QPixmap::fromImage(*jComp->imgV));
    ui->imageV->setScaledContents(true);
    } else {
        ui->label_debug->setText("WARNING! - MUST FIRST CHOOSE IMAGE");
    }
    //DEBUG
//    ui->label_debug->setText(std::to_string(jComp->matU->getPoint(100, 300)));
//    std::cout << "\n\nThis is a test:  " << jComp->matU->getPoint(100, 300);
}


//********************************************
// ** Create the RCL and DPCM
//********************************************
void MainWindow::on_buildRclDpcm_clicked()
{
    if(!image->isNull()){
    //BUILD AND CONSTRUCT THE RCL AND DPCM COMPONENTS
    buildY->constructRclDp(*jComp->matY, LAYER_Y);
    buildU->constructRclDp(*jComp->matU, LAYER_U);
    buildV->constructRclDp(*jComp->matV, LAYER_V);


    ui->label_debug->setText("SAVEING THE COMPRESSED IMAGE TO BUFFER");
    buildY->saveCompressedImage();
    buildU->saveCompressedImage();
    buildV->saveCompressedImage();
    } else {
        ui->label_debug->setText("WARNING! - MUST FIRST CHOOSE IMAGE");
    }

}



//********************************************
// ** SAVE AND UPDATE BUTTON
//********************************************

void MainWindow::on_pushButton_4_clicked()
{



    cout << "\n\nBUILDING COMPRESSED IMAGE\n\n" << endl;
    jComp->yuvToRGB(buildY->compressedImage, buildU->compressedImage, buildV->compressedImage);


}

//********************************************
// ** ViewImage
//********************************************
void MainWindow::on_pushButton_5_clicked()
{
    ui->compressed_img->setPixmap(QPixmap::fromImage(*jComp->compressedImage));

}


//********************************************
// ** Misc. Button for DEBUG and TEST
//********************************************
void MainWindow::on_pushButton_3_clicked()
{
    if(!image->isNull()){

//    int lumaQ[8][8] = {{16,11,10, 16, 24,40,51,61},
//                       {12,12,14,19,26,58,60,55},
//                       {14, 13, 16, 24, 40,  57,  69,  56},
//                       {14, 17, 22, 29, 51,  87,  80,  62},
//                       {18, 22, 37, 56, 68,  109, 103, 77},
//                       {24, 35, 55, 64, 81,  104, 113, 92},
//                       {49, 64, 78, 87, 103, 121, 120, 101},
//                       {72, 92, 95, 98, 112, 100, 103, 99}};
    ui->label_debug->setText("Before the Button....SAVE RLC");

//    buildY->SaveRLC_DPCM(lumaQ);
//    buildY->printDPCM();
//    cout << "\n\nTHIS IS FOR Y \n";
//    buildY->printPreRLC();
//    cout << "\n\nTHIS IS FOR U \n";
//    buildU->printPreRLC();
//    cout << "\n\nTHIS IS FOR V \n";
//    buildV->printPreRLC();


//    cout << "\n\nTHIS IS FOR Y \n";
//    buildY->printDPCM();
//    cout << "\n\nTHIS IS FOR U \n";
//    buildU->printDPCM();
//    cout << "\n\nTHIS IS FOR V \n";
//    buildV->printDPCM();


//    cout << "\n\nTHIS IS FOR Y \n";
//    buildY->printRCL();
//    cout << "\n\nTHIS IS FOR U \n";
//    buildU->printRCL();
//    cout << "\n\nTHIS IS FOR V \n";
//    buildV->printRCL();
    cout << "\n\nTHIS IS FOR V - IDCT\n";
    buildU->saveCompressedImage();

    } else {
        ui->label_debug->setText("WARNING! - MUST FIRST CHOOSE IMAGE");
    }
}



