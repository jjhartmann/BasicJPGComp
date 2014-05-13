#include "blocktransform.h"
#include <QColor>
#include <iostream>
#include "math.h"
BlockTransform::BlockTransform()
{
}


void BlockTransform::constructRclDp(uMatrix img, TYPE_YUV LAYER){
    createDCTTable();

    //Matrix Containers
    int matInt[8][8];
    int quantI[8][8];
    int quantInverse[8][8];
    float DCTMatrix[8][8];
    float iDCTMatrix[8][8];


    int width = img.getSizeX();
    int height = img.getSizeY();

    //Store iDCT Results in Continer
    compressedImage = new uMatrix(width, height);

    //Temp Color Container
    QColor t;

    for(int i = 1; i < height; ){
        for(int j = 1; j < width; ){

            //Build 8x8 block
            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){

                    //Extract int Value from Image
                    matInt[l][k] = img.getPoint(l+j-1,k+i-1) - 128;
//                    std::cout << i << " " << j << k << " " << l <<  " THi is the 8x8 block:  " << matInt[k][l] << std::endl;

                }
            }//end 8x8 block

//******************************************
//            cout << "Before the Function DCT \n";
            //Call the DCT FUNTION
            DCT(matInt, DCTMatrix);

//******************************************
//            cout << "Before the Function Quantize \n";
            //Quantize the DCT Block
            //CHANGE BASED ON LUMA OR CHROMA
            if(LAYER == LAYER_Y){
                QuantizeY(DCTMatrix, quantI);
            } else {
                QuantizeUV(DCTMatrix, quantI);

            }


            //INVERSE QUANTIZE
            if(LAYER == LAYER_Y){
                iQuantizeY(quantI, quantInverse);
            } else {
                iQuantizeUV(quantI, quantInverse);

            }

//            cout << "Before the Function RLC \n";

//******************************************
            //INVERSE DCT PROCESS
            inverseDCT(quantInverse, iDCTMatrix);

//******************************************
            //SAVE AND STORE RCL
//            SaveRLC_DPCM(quantI);
            // SAVE preRCL into matRCL with RCL format
            //(#number of zeros, element)
//            Save_RLE();



            //END SECTION BLOCK
            j = (j*8);
        } //Subsection For-Loop


        i = (i*8);
    } //Subsection For-Loop

//******************************************
// RUN AND SAVE AC COMPENTS IN RLE FORMAT

//    Save_RLE();

    //SAVE COMPRESSED IMAGE TO UMATRIX
//    saveCompressedImage();
}




//***********************************************************
// THE DCT PROCESS
//***********************************************************
void BlockTransform::DCT(int (&matInt)[8][8], float (&DCTMatrix)[8][8]){
    //DCT T Element

    int i, j, u, v;
        for (u = 0; u < 8; ++u) {
            for (v = 0; v < 8; ++v) {
            DCTMatrix[u][v] = 0;
                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
                        DCTMatrix[u][v] += matInt[i][j] * cos(M_PI/((float)8)*(i+1./2.)*u)*cos(M_PI/((float)8)*(j+1./2.)*v);
//                        cout << DCTMatrix[u][v] << " ";
                    }
                }
            }
        }


//    float idcttemp[8][8];
//    for (int row = 0; row < 8; row++) {
//         for (int col = 0; col < 8; col++) {
//             // Multiply the row of A by the column of B to get the row, column of product.
//             for (int inner = 0; inner < 8; inner++) {
//                 idcttemp[row][col] += dctTable[row][inner] * matInt[inner][col];
//             }
////                 std::cout << /*product*/[row][col] << "  ";
//         }
////             std::cout << "\n";
//     }

//    for (int row = 0; row < 8; row++) {
//         for (int col = 0; col < 8; col++) {
//             // Multiply the row of A by the column of B to get the row, column of product.
//             for (int inner = 0; inner < 8; inner++) {
//                 DCTMatrix[row][col] += idcttemp[row][inner] * dctTable[col][inner];
//             }
//                 std::cout << DCTMatrix[row][col] << "  ";
//         }
////             std::cout << "\n";
//     }





//    cout << "\nINSIDE DCT: " << endl;



}


//***********************************************************
// THE inverseDCT PROCESS
//***********************************************************
void BlockTransform::inverseDCT(int (&DCTMatrix)[8][8], float (&iDCTMatrix)[8][8]){
    //DCT T Element
    int i, j, u, v;

        for (u = 0; u < 8; ++u) {
            for (v = 0; v < 8; ++v) {
              iDCTMatrix[u][v] = 1/4.*DCTMatrix[0][0];
              for(i = 1; i < 8; i++){
              iDCTMatrix[u][v] += 1/2.*DCTMatrix[i][0];
               }
               for(j = 1; j < 8; j++){
              iDCTMatrix[u][v] += 1/2.*DCTMatrix[0][j];
               }

               for (i = 1; i < 8; i++) {
                    for (j = 1; j < 8; j++) {
                        iDCTMatrix[u][v] += DCTMatrix[i][j] * cos(M_PI/((float)8)*(u+1./2.)*i)*cos(M_PI/((float)8)*(v+1./2.)*j);
                    }
                }
            iDCTMatrix[u][v] *= 2./((float)8)*2./((float)8);
            cout << "  " << iDCTMatrix[u][v];
            preCompImage.push_back(round(iDCTMatrix[u][v]));
            }
        }

//        float idcttemp[8][8];
//        for (int row = 0; row < 8; row++) {
//             for (int col = 0; col < 8; col++) {
//                 // Multiply the row of A by the column of B to get the row, column of product.
//                 for (int inner = 0; inner < 8; inner++) {
//                     idcttemp[row][col] += dctTable[inner][row] * DCTMatrix[inner][col];
//                 }
////                 std::cout << product[row][col] << "  ";
//             }
////             std::cout << "\n";
//         }

//        for (int row = 0; row < 8; row++) {
//             for (int col = 0; col < 8; col++) {
//                 // Multiply the row of A by the column of B to get the row, column of product.
//                 for (int inner = 0; inner < 8; inner++) {
//                     iDCTMatrix[row][col] += idcttemp[row][inner] * dctTable[inner][col];
//                 }
//                 std::cout << iDCTMatrix[row][col] << "  ";
//             }
////             std::cout << "\n";
//         }

//    cout << "\nINSIDE iDCT: " << endl;



}

//***********************************************************
// Quantize the Table
//***********************************************************
void BlockTransform::QuantizeY(float (&matInt)[8][8],int (&quantI)[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

//            for(int k = 0; k < 8; k++){
                 quantI[j][i] = round(matInt[j][i]/lumaQ[j][i]);

//               cout << "This is qauntized table LUMA:  " << quantI[i][j] << endl;
//            }
        }

    }
}

//*** QUANTIZE U AND V ****
void BlockTransform::QuantizeUV(float (&matInt)[8][8],int (&quantI)[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

           // for(int k = 0; k < 8; k++){
                 quantI[j][i] = round(matInt[j][i]/chromaQ[j][i]);

//               cout << "This is qauntized table CHROM:  " << quantI[i][j] << endl;
           // }
        }

    }
}

//***********************************************************
// INVERSE Quantize the Table
//***********************************************************
void BlockTransform::iQuantizeY(int (&matInt)[8][8],int (&quantI)[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

//            for(int k = 0; k < 8; k++){
                 quantI[j][i] = round(matInt[j][i]*lumaQ[j][i]);

               cout << "This is INVERSE qauntized table LUMA:  " << quantI[i][j] << endl;
//            }
        }

    }
}

//*** QUANTIZE U AND V ****
void BlockTransform::iQuantizeUV(int (&matInt)[8][8],int (&quantI)[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

           // for(int k = 0; k < 8; k++){
                 quantI[j][i] = round(matInt[j][i]*chromaQ[j][i]);

//               cout << "This is qauntized table CHROM:  " << quantI[i][j] << endl;
           // }
        }

    }
}


//*******************************************************************
// Save inverse DCT to compressed Image container
//*******************************************************************
void BlockTransform::saveCompressedImage(){
    int size =  preCompImage.size();

    for(int i  = 0; i < size-64;){

        for(int k = 0; k < 8; k++){
            for(int p = 0; p < 8; p++){

                compressedImage->setPoint(i+p, i+k, round(preCompImage.at(i)));

//                cout << "DEBUG: PRECOMPIMAGE: " << preCompImage.at(i) << endl;
            }
        }



        i+= 64;
    }








}



//*******************************************************************
// Save Element Items to RCL and DPCM
//*******************************************************************
void BlockTransform::SaveRLC_DPCM(int (&quantI)[8][8]){
    // Using QuantI[i][j]



    //Implement ZigZag rendering
    int itr = 1;

    for(int Diag = 0; Diag <= 14; Diag++){

       if(Diag == 0){
            //Place DCMP Here
            if(DPCM.empty()){
                DPCM.push_back(quantI[0][0]);
                DPCM_temp.push_back(quantI[0][0]);


            } else {
                DPCM.push_back(DPCM_temp.back()-quantI[0][0]);
                DPCM_temp.push_back(quantI[0][0]);
            }

       } else if(Diag <= 7){
           //First Half Here
            for(int i = 0; i <= Diag; i++ ){

                //Even and Odd Diagonals
                if(Diag%2 == 1){
                     preRCL.push_back(quantI[i][Diag-i]);
                } else{
                    preRCL.push_back(quantI[Diag-i][i]);
                }

            } // END FOR

        } else {

           //Last Half of 8x8 Block
           for(int i = itr; i <= Diag-itr; i++){

               //Even and Odd Diagonals
               if(Diag%2 == 1){
                    preRCL.push_back(quantI[i][Diag-i]);
               } else{
                   preRCL.push_back(quantI[Diag-i][i]);
               }

//               cout << "DEBUG: " << i << " " << (Diag - i) << endl;


           } // END FOR

           itr++; //iterator for the other half of function

       } // END IF ELSE STATEMENT

       //DEBUG
//       cout << "DCPM AND RCL: " << preRCL.at(4);
//       cout <<  " " << preRCL[Diag];
//       cout << endl;

     } // END DIAGONAL FOR STATEMENT



}

//***********************************************************
// CONVERT TO RUN LENGTH CODE (# of ZEROS, NEXT element)
//***********************************************************
void BlockTransform::Save_RLE(){
    eRCL ercl;
    int z15 = 0;
    int nzero = 0;

    //Normalize the Length of the 64 instances
    int nLength = preRCL.size()%63 + preRCL.size();

    //EACH INSTANCE OF THE BLOCK IS CONTAINED ON 63 Instainces
    for(int i = 0; i < nLength; ) {

        //ITER THROUGH ELEMENT BLOCKS
        for(int j = i; j < i+63; j++){
            if(j == i){
                // INITIAL CASE (0, .at(j))
                if(preRCL.at(j) > 0){
                ercl.zrs = 0;
                ercl.e = preRCL.at(j);
                matRLC.push_back(ercl);
                } else {
                    nzero++;
                }
            } else {

                if(preRCL.at(j) == 0){
                    nzero++;
                    //SPECIAL CASE nzero > 15 :: (# of ZEROs, 0)
                    //HUFMAN CODE IS ONLY 4bits
                    if(nzero > 15){
                        ercl.zrs = 15;
                        ercl.e = 0;
                        matRLC.push_back(ercl);

                        //ITER z15
                        z15++;
                        nzero = 0;
                    }

                    //LAST BLOCK ELEMENT TEST
                    if(j == i+62){
                        //TEST and POP_BACK
                        int k = 0;
                        while(k < z15){
                            matRLC.pop_back();
                            k++;
                        }
                        ercl.EOB = true;
                        matRLC.push_back(ercl);

                    }


                } else {
                    //CREATE RCL
                    ercl.zrs = nzero;
                    ercl.e = preRCL.at(j);
                    matRLC.push_back(ercl);

                    //FINAL TEST - INDICATE EOBs
                    if(j == i+62){
                        ercl.EOB = true;
                        matRLC.push_back(ercl);
                    }
                    //REINTIALIZE # OF ZEROS
                    nzero = 0;
                    z15 = 0;

                }


            } //END IF MAIN

        } //END BLOCK FOR-LOOP



        //REINITIALIZE VARS
        ercl.EOB = false;
        nzero = 0;
        z15 = 0;
       //Subsection 63 Blocks
       i += 63;
    }// END MAIN FOR-LOOP




}

//************************************************************************
// TESTING - PRINT THE RCL CODE RAW
//************************************************************************
void BlockTransform::printPreRLC(){

    if(preRCL.empty()){
        cout << "The PRERCL is EMPTY!!!!" << endl;
    } else {
       int size = preRCL.size();
       for(int i = 0; i < size; i++){
            cout << ", " << preRCL.at(i);
        }

    }

}

void BlockTransform::printRCL(){
    int size = matRLC.size();
    for(int i = 0; i < size; i++){

        if(!matRLC.at(i).EOB){
        cout << "(" << matRLC.at(i).zrs << ", " << matRLC.at(i).e << ")  ";
        } else {
            cout << "(" << matRLC.at(i).EOB << ")  ";
        }

    }
}

//************************************************************************
// TESTING - PRINT THE DPCM CODE RAW
//************************************************************************
void BlockTransform::printDPCM(){

    if(DPCM_temp.empty()){
        cout << "The PRERCL is EMPTY!!!!" << endl;
    } else {
       int size = DPCM_temp.size();
       for(int i = 0; i < size; i++){
            cout << ", " << DPCM_temp.at(i);
        }

    }

}


//************************************************************************
// TESTING - PRINT THE COMPRESSED IMAGE
//************************************************************************
void BlockTransform::printCImage(){

    if(compressedImage->empty()){
        cout << "The PRERCL is EMPTY!!!!" << endl;
    } else {
       int x = compressedImage->getSizeX();
       int y = compressedImage->getSizeY();
       for(int i = 0; i < x; i++){
           for(int j = 0; j < y; j++){
            cout << ", " << compressedImage->getPoint(i, j);
           }
        }

    }

}


void BlockTransform::createDCTTable(){
    float dctT;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j == 0){
                dctT = 1/ (2*sqrt(2));
            }else{
                dctT = 0.5 * cos((((2.*i)+1.)*j*PI)/16.);
            }

            dctTable[i][j] = dctT;
//            cout << "DCT TABLE :: " << i << j << "  " << dctT << endl;
        }
    }


}



//OLD CODE
////***********************************************************
//// THE DCT PROCESS
////***********************************************************
//void BlockTransform::DCT(int (&matInt)[8][8]){
//    //DCT T Element
//    double dctT;
//    int dctM[8][8];

//    // Matrix Multiplication T*M
//    for(int i = 0; i < 8; i++){
//        for(int j = 0; j < 8; j++){
//            dctM[i][j] = 0;

//            if(j == 0){
//                dctT = 1/ sqrt(8);
//            }else{
//                dctT = 0.5 * cos((((2.*i)+1.)*j*PI)/16.);
//            }

//            for(int k = 0; k < 8; k++){
//                dctM[i][j] += round(matInt[i][k]*dctT);
//            }
//        }
//    }

//    // Matrix Multiplication M*T'
//    for(int i = 0; i < 8; i++){
//        for(int j = 0; j < 8; j++){
//            matInt[i][j] = 0;

//            for(int k = 0; k < 8; k++){

//                if(j == 0){
//                    dctT = 1/ sqrt(8);
//                }else{
//                    dctT = 0.5*cos((((2.*k)+1.)*j*PI)/16.);
//                }

//                matInt[i][j] += round(dctM[i][j]*dctT);

//            }
//        }
//    }




//    cout << "\nINSIDE DCT: " << endl;



//}


////***********************************************************
//// THE inverseDCT PROCESS
////***********************************************************
//void BlockTransform::inverseDCT(int (&matInt)[8][8]){
//    //DCT T Element
//    double dctT;
//    int dctM[8][8];

//    // Matrix Multiplication T'*M
//    for(int i = 0; i < 8; i++){
//        for(int j = 0; j < 8; j++){
//            dctM[i][j] = 0;

//            if(i == 0){
//                dctT = 1/ sqrt(8);
//            }else{
//                dctT = 0.5 * cos((((2.*j)+1.)*i*PI)/16.);
//            }

//            for(int k = 0; k < 8; k++){
//                dctM[i][j] += round(matInt[i][k]*dctT);
//            }
//        }
//    }

//    // Matrix Multiplication M*T
//    for(int i = 0; i < 8; i++){
//        for(int j = 0; j < 8; j++){
//            matInt[i][j] = 0;

//            for(int k = 0; k < 8; k++){

//                if(k == 0){
//                    dctT = 1/ sqrt(8);
//                }else{
//                    dctT = 0.5*cos((((2.*j)+1.)*k*PI)/16.);
//                }

//                matInt[i][j] += round(dctM[i][j]*dctT);

//            }
//        }
//    }


//}






