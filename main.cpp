#include<iostream>
#include<vector>
#include "vectorsExt.hpp"


void testMatMult()
{
    std::vector<std::vector<double>> matrixA (2, std::vector<double>(3));  //2x3
    std::vector<std::vector<double>> matrixB(3, std::vector<double>(2));  //3x2
    std::vector<std::vector<double>> matrixC(2, std::vector<double>(2));  //2x2 


    matrixA[0] = std::vector<double> {1,2,3};
    matrixA[1] = std::vector<double> {1,2,3};

    matrixB[0] = std::vector<double> {1,1};
    matrixB[0] = std::vector<double> {1,1};
    matrixB[0] = std::vector<double> {1,1};

    martixMult(matrixA, matrixB, matrixC);


    std::cout << matrixSum(matrixC) << std::endl;
}

int main()
{
    std::vector<double> vectorA(10); //
    for(std::size_t i = 0; i < 10; i++)
    {
        vectorA[i] = i; //epic initialization move
    } 

    std::vector<double> sliceA = sliceVector(vectorA, 5, 10);
    std::vector<double> concatenadedVect = concatVectors(vectorA, sliceA);

    std::vector<std::vector<double>> matrixA(3, std::vector<double>(3));
    matrixA[0] = std::vector<double> {1,2,3};
    matrixA[1] = std::vector<double> {4,5,6};
    matrixA[2] = std::vector<double> {7,8,9};

    std::vector<std::vector<double>> slicedMatrix = sliceMatrix(matrixA, 1,3, 1,3); 


    std::vector<std::vector<double>> tempMatrix(2, std::vector<double>(2));
    tempMatrix[0] = std::vector<double> {3,4};
    tempMatrix[1] = std::vector<double> {1,0};

    std::vector<std::vector<double>> a = concatenateMatrices(slicedMatrix, tempMatrix, 1);
    std::cout << "sliced and then concatenad matrix with columns" << std::endl;
    printMatrixContent(a); 
    std::cout << " "<< std::endl;
    
    a = concatenateMatrices(slicedMatrix, tempMatrix, 0);
    std::cout << "sliced and then concatenad matrix with rows" << std::endl;
    printMatrixContent(a); 
    std::cout << " "<< std::endl;

    std::vector<std::vector<double>> matrixConv(3, std::vector<double>(3)); //3x3 matrix
    std::vector<std::vector<double>> filt(2, std::vector<double>(2)); //3x3 matrix
   

    matrixConv[0] = std::vector<double> {1,1,1};
    matrixConv[1] = std::vector<double> {1,1,1};
    matrixConv[2] = std::vector<double> {1,1,1};

    filt[0] = std::vector<double> {2,2};
    filt[1] = std::vector<double> {2,2};

    std::vector<std::vector<double>> convolvedMatrix = conv2d(matrixConv, filt);
    std::cout << "Convolution Output (should read 8s because 2+2+2+2 in each window)" << std::endl;  // 
    printMatrixContent(convolvedMatrix);

    return 1;
}