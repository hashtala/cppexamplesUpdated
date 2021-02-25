#include<iostream>
#include<vector>
#include "vectorsExt.hpp"

int main()
{
    
            
    std::vector<std::vector<double>> matrixA (2, std::vector<double>(2));
    std::vector<std::vector<double>> matrixB (2, std::vector<double>(2));

    /*
    matrixA[0] = std::vector<double> {1,2};
    matrixA[1] = std::vector<double> {3,4};
    */
    std::vector<double> vectorA {1,3,6};

    //int a = sizeof(matrixA);
    //std::cout << a;
    
    /*
    matrixA[0] = std::vector<double> {1,2};
    matrixA[1] = std::vector<double> {1,2,3};

    matrixB[0] = std::vector<double> {1,2};
    matrixB[1] = std::vector<double> {1,2};
    */
    
    std::vector<std::vector<double>> matrixC = concatenateMatrices(matrixA, matrixB, 0);

    return 0;
}