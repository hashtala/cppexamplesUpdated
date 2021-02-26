#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vectorsExt.hpp"
#include <vector>
#include <cmath>


/*
   all assertion values are obtained from Python numpy and scipy.signal
*/

TEST_CASE("TESTS")
{

    std::vector<std::vector<double>> matrixA(3, std::vector<double>(3));
    matrixA[0] = std::vector<double> {1,2,3};
    matrixA[1] = std::vector<double> {4,5,6};
    matrixA[2] = std::vector<double> {7,8,9};

    std::vector<std::vector<double>> matrixOnes2D(2, std::vector<double>(2));
    matrixOnes2D[0] = std::vector<double> {1,1};
    matrixOnes2D[1] = std::vector<double> {1,1};

    std::vector<std::vector<double>> convolvedMatAones = conv2d(matrixA,matrixOnes2D);
    std::vector<std::vector<double>> matrixMultBuffer(2, std::vector<double>(2));

    martixMult(convolvedMatAones, matrixOnes2D, matrixMultBuffer);

    std::vector<std::vector<double>> small2DMatrix(2, std::vector<double>(2));
    small2DMatrix[0] = std::vector<double>{0.32, 0.74};
    small2DMatrix[1] = std::vector<double>{0.12, 0.27};
    std::vector<std::vector<double>> convWithSmallArray = conv2d(matrixMultBuffer, small2DMatrix);
    
    std::vector<std::vector<double>> slicedMatrixA = sliceMatrix(matrixA, 1,3,1,3);
    


    SECTION("Matrix sum")
    {   
        REQUIRE(matrixSum(matrixA) == 45.0);
        REQUIRE(matrixSum(matrixOnes2D) == 4.0);
        REQUIRE(matrixSum(convolvedMatAones) == 80.0);
        REQUIRE(matrixSum(matrixMultBuffer) == 160.0);
        REQUIRE(matrixSum(small2DMatrix) > 1.44);
        REQUIRE(matrixSum(small2DMatrix) < 1.46);
        REQUIRE(matrixSum(slicedMatrixA) == 28.0);
    }

    SECTION("CONVULUTION")
    {
        REQUIRE(convolvedMatAones[0] == std::vector<double> {12,16});
        REQUIRE(convolvedMatAones[1] == std::vector<double> {24,28});
    }


  
    SECTION("Matrix Multiplication")
    {
        REQUIRE(matrixMultBuffer[0] == std::vector<double> {28,28});
        REQUIRE(matrixMultBuffer[1] == std::vector<double> {52,52});
    }

    SECTION("SLICE")
    {
        REQUIRE(slicedMatrixA[0] == std::vector<double> {5,6});
        REQUIRE(slicedMatrixA[1] == std::vector<double> {8,9});
    }

}


