#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<stdexcept>


/*********************************************************************************
*                                                                                *
* --Takes a matrix as input                                                      *
* --Throws exceptions if it is not a rectangular matrix or the matrix is empty   *
*                                                                                *
 *********************************************************************************/

void validateMatrix(const std::vector<std::vector<double>>& matrixA)
{
    try
    {
        if(matrixA.empty())
        {
            throw std::invalid_argument("EMPTY MATRIX!!!");
        }
        else if(matrixA[0].empty())
        {
            throw std::invalid_argument("EMPTY VECTOR AT 0 INDEX");
        }
        else
        {
            //MAKE SURE all vectors of matrix are SAME SIZE!!!
            std::size_t shapeA = matrixA.size(); //if the above if-statements has passed and we're here, matrix.size() and matrix[0].size() wil not be undefined
            std::size_t currentVectorLen = matrixA[0].size(); 
            std::size_t prevVecLen = currentVectorLen; //by keep trakcing of previous vector size it is possible to throw exception what shapes have been conflicted
            std::size_t shapeB = 0;//it is 0 until it is validated
            for(std::size_t i = 0; i < shapeA; i++)
            {
                if(matrixA[i].empty())
                {
                    throw std::invalid_argument{"EMPTY VECTOR AT " + std::to_string(i)};
                }
                    
                currentVectorLen = matrixA[i].size();
                if(currentVectorLen != prevVecLen)
                {
                    throw std::invalid_argument{"Vector Size MISMATCH AT INDEX (" + std::to_string(i) + ") SHAPES ->   " + std::to_string(currentVectorLen) +" & " + std::to_string(prevVecLen)};
                }
                prevVecLen = currentVectorLen;
            }
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}


void validateVector(std::vector<double>& vectorA)
{
    if(vectorA.empty())
    {
        std::cout << "EMPTY VECTOR" << std::endl;
        throw std::invalid_argument("EMPTY VECTOR!!!");
    }
}


/***********************************************************************
* -- Will be used to determine concatenation Type                      *
* -- if Rows is selected, rows of matrices will be concatenatad        *
* -- if Columns is selected, columns of matrices will be concatenated  *
************************************************************************/

enum class ConcatenationType {
	Rows,
	Columns,
};


/*******************************************************
* -- matrix multiplication function                    *
* -- it takes three intpus                             *
* -- reference to matrix A, B and C which is AxB       *
* Note: shapes of A and B should be a x b || b x c     *
* output matrix will have a x c shape                  *
********************************************************/

void martixMult(const std::vector<std::vector<double>>& matrixA, 
                const std::vector<std::vector<double>>& matrixB, 
                std::vector<std::vector<double>>& matrixC)
{

    validateMatrix(matrixA);
    validateMatrix(matrixB);

    try
    {
        if(matrixA[0].size() != matrixB.size())
        {
            throw std::invalid_argument{"SHAPE MISMATCH ->  " + std::to_string(matrixA[0].size()) +" & " + std::to_string(matrixB.size())};
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

   

    //resizing output matrix buffer
    matrixC.resize(matrixA.size());
    for(std::size_t i = 0; i < matrixB[0].size(); i++)
    {
        matrixC[i].resize(matrixB[0].size());
    }


    double temp = 0.0;
    for(std::size_t k = 0; k < matrixB[0].size(); k++)
    {
        for(std::size_t i = 0; i < matrixA.size(); i++)
        {
            temp = 0;
            for(std::size_t j = 0; j < matrixA[0].size(); j++)
            {
                temp += matrixA[i][j]*matrixB[j][k];
                // MOGNI aq unda daematos MESAME loop rom gaakontrolos 
            }
            matrixC[i][k] = temp; 
          
        }     
    }

}

/********************************************************
* -- prints content of matrix                           *
* -- uses reference just to skip copying instructions   *
**********************************************************/
void printMatrixContent(const std::vector<std::vector<double>>& matrixA)
{
   //validateMatrix(matrixA);
   for(std::size_t i = 0; i< matrixA.size(); i++)
   {
       for(std::size_t j = 0; j < matrixA[i].size(); j++)
       {
            std::cout << matrixA.at(i).at(j);  //this wil throw error anyway if matrix is out of bounds so...
            std::cout << " ";
       }
        std::cout << " " << std::endl;
   }
}


/***********************************************
* -- returns sum of array elements             *
* -- reuires pointer of 2D vector to be passed *
************************************************/

double matrixSum(const std::vector<std::vector<double>> &matrixA)
{
    validateMatrix(matrixA);
    double sum = 0.0;
    std::size_t a = matrixA.size();
    for(std::size_t i = 0; i < a; i++)
    {
        std::size_t b = 0;
        b = matrixA[i].size();
        for(std::size_t j = 0; j < b; j++)
        {
            sum += matrixA[i][j];
        }
    } 

    return sum;
}

/**************************************************************************
*-- This convolution function MODIFIES input buffer                       *
*-- Writes convolved signal right into input buffer                       *
***************************************************************************/

void convolve(std::vector<double>& sineBuffer, std::vector<double>& filter)
{
   // std::vector<double> convFilter{1.0, 0.7, 0.5, 0.3}; //size 4;
    double tempResult = 0.0;
    for(std::size_t i = 0; i < sineBuffer.size() - filter.size(); i++) // MODE same
    {
        tempResult = 0.0;
        for(int j = 0; j < filter.size(); j++)
        {
           tempResult += sineBuffer[i+j]*filter[j];
        }
        sineBuffer[i] = tempResult;
    }

}

/*******************************************************************************
* -- convolves matrixA with filter                                             *
* -- convolution mode is VALID.                                                *
* -- returs 2D array with size a - m  + 1 by b - n + 1                         *
* -- where a x b and m x n are shapes of input matrix and filter respectively. *
********************************************************************************/

std::vector<std::vector<double>> conv2d(const std::vector<std::vector<double>> matrixA, 
                                        const std::vector<std::vector<double>> filter)
{

    validateMatrix(matrixA);
    validateMatrix(filter);

    const std::size_t a = matrixA.size();
    const std::size_t b = matrixA[0].size();   // matxiA is size a x b;
    const std::size_t m = filter.size();
    const std::size_t n = filter[0].size(); // filter is m x b;
    std::size_t shapeA = a - m + 1;
    std::size_t shapeB = b - n+ 1;
    std::vector<std::vector<double>> tempVector(shapeA, std::vector<double>(shapeB));
    double tempSum = 0.0;
    for(std::size_t l = 0; l < shapeA ; l++)
    {
        for(std::size_t k = 0; k < shapeB; k++)
        {
            tempSum = 0.0;
            for(std::size_t i = 0; i < n; i ++)  
            {
                for(std::size_t j = 0; j < m; j++)
                {
                    tempSum += matrixA[k+i][l+j]*filter[i][j]; //we need to offset main matrix by k and l
                }
            }
            tempVector[k][l] = tempSum;
        }
    }

    return tempVector;

}

/******************************************************************
* -- returns concatenated array of vectorA with vectorB           *
* -- note: order of inputs yeld to different output               *
* -- Concat(vectorA, vectorB)  IS NOT Concat(vectorB, vectorA)    *
*******************************************************************/

std::vector<double> concatVectors(std::vector<double>& vectorA, std::vector<double>& vectorB)
{

    validateVector(vectorA);
    validateVector(vectorB);

    const std::size_t sizeA = vectorA.size();
    const std::size_t sizeB = vectorB.size();
    const std::size_t size = sizeA + sizeB;
    std::vector<double> tempVector(size);
    
    std::size_t indexVar = 0;
    for(std::size_t i = 0; i < sizeA; i++)
    {
        tempVector[indexVar] = vectorA[i]; 
        indexVar++;
    }

    for(std::size_t i = 0; i < sizeB; i++)
    {
        tempVector[indexVar] = vectorB[i];
        indexVar++;
    }

    return tempVector;
}

/*********************************************************************
* --returns slice of Vector with given intevals                      *
* --including element on index start and excluding element from end  *
* --size is end - start                                              *
**********************************************************************/

std::vector<double> sliceVector(std::vector<double> vectorA, std::size_t start, std::size_t end)  //could also be used for copy.
{

    validateVector(vectorA);

    if(start > end)
    {
        std::cout << "Incorrect Intervals!!!";
        return std::vector<double> {0};
    }

    const std::size_t  size = end - start;
    std::vector<double> tempVector(size);
    std::size_t j = 0;
    for(std::size_t i = start; i < end; i++)
    {
        tempVector[j] = vectorA[i];
        j++;
    }
    return tempVector;
}


/*****************************************************************
* -- slices matrixA and returns sliced matrix                    *
*-- return shape is b - a x n - m                                *
* -- a is start index on rows and b is end index on rows         *
* -- m is start index on columns and n is end index on column    *
******************************************************************/

std::vector<std::vector<double>> sliceMatrix(std::vector<std::vector<double>>& matrixA,
                                             std::size_t a, 
                                             std::size_t b,
                                             std::size_t m, 
                                             std::size_t n)
{

    validateMatrix(matrixA);

    if(a > b || m > n)
    {
        std::cout << "INCORRECT slice interval!!!" << std::endl;
        return std::vector<std::vector<double>> {{0.0}};
    }

    const std::size_t sizeRow = b - a;
    const std::size_t sizeCol = n - m;

    const std::size_t sizeMatrixVector = matrixA[0].size(); // suppose size of matrixA is a x b then this variable is b.
    std::vector<std::vector<double>> tempMatrix(sizeRow, std::vector<double>(sizeCol)); //matrix that will be returned
    std::vector<double> tempRowVector(sizeMatrixVector);
    std::vector<double> tempSlicedVector(sizeRow);

     //lets break down matrix into ROW vectors and use vector slicing function

    for(std::size_t i = 0; i < sizeCol; i++)
    {

        tempRowVector = matrixA[m+i];
        tempSlicedVector = sliceVector(tempRowVector, a, b);
        tempMatrix[i] = tempSlicedVector;       
    }

    return tempMatrix;
}

/************************************************************
*-- concatenates two matrices either row-wise or column-wise*
*-- set flag = 1 to concatenate rows of matrice             *
*-- set flag = 0 to conatenate columns ofmatrices           *
*************************************************************/

std::vector<std::vector<double>> concatenateMatrices(std::vector<std::vector<double>>& matrixA,
                                                     std::vector<std::vector<double>>& matrixB,
                                                     ConcatenationType flag)  
{


    validateMatrix(matrixA);
    validateMatrix(matrixB);



    if(flag == ConcatenationType::Rows)
    {
        const std::size_t a = matrixA.size();
        const std::size_t m = matrixB.size();
        try
        {
            if(a != m)
            {
                throw std::invalid_argument("SHAPE Mistmatch, did you mean flag = 1?");
            }

        }
        catch(std::exception& e)
        {
            std::cerr<< e.what() << std::endl;
        }

        const std::size_t b = matrixA[0].size();
        const std::size_t n = matrixB[0].size();

        const std::size_t rowLen = a + m;
        const std::size_t colLen = b + n;

        std::vector<std::vector<double>> tempArray(a, std::vector<double>(colLen));

        for(std::size_t i = 0; i < a; i++) //or m but whatever
        {
            tempArray[i] = concatVectors(matrixA[i], matrixB[i]);
        }        

        return tempArray;

    }
    else if(flag == ConcatenationType::Columns)
    {
        const std::size_t b = matrixA[0].size();
        const std::size_t n = matrixB[0].size();

        try
        {
            if(b != n)
            {
                throw std::invalid_argument("SHAPE Mistmatch, did you mean flag = 0?");
            }

        }
        catch(std::exception& e)
        {
            std::cerr<< e.what() << std::endl;
        }

        const std::size_t a = matrixA.size();
        const std::size_t m = matrixB.size();

        const std::size_t rowLen = a + m;
        const std::size_t colLen = b + n;      
        std::size_t indexVar = 0;
        std::vector<std::vector<double>> tempArray(colLen, std::vector<double>(b)); //could be n as well
    
        for(std::size_t i = 0; i < a; i++) //or m but whatever
        {
            tempArray[indexVar] = matrixA[i];
            indexVar++;
        }       
        for(std::size_t i = 0; i < m; i++) //or m but whatever
        {
            tempArray[indexVar] = matrixB[i];
            indexVar++;
        }       

        return tempArray;
    }
    else
    {
        std::cerr << "INVALID CONCATENATION TYPE\n";
    }


    return std::vector<std::vector<double>>{{0}};
}

