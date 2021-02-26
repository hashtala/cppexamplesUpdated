#include<iostream>
#include<vector>
#include<cmath>

#define SIZE 128

/*
-- fills array with points
-- points are linear space from start to stop
-- step interval DEPENDS on start, stop and SIZE
-- step interval = (stop - start / size)
*/

void initLinSpace(std::vector<double>& matrixPtr, 
                  std::size_t size, double start, 
                  double stop)
{
    if(start > stop) return;
    double step = (stop - start)/size;

    for(std::size_t i = 0; i < size; i++)
    {
        matrixPtr[i] = start + step*i; //just creates linear space from say 0 to 2 with step 0.01
    }
}


/*
-- mapping function
-- function we are trying to linearly apporximate
*/
double function(double x)
{
    return 0.5*exp(x+1) - 1.35914;
}

/*
-- takes pointer to INITIALIZED linear space
-- takes pointer to matrix where function values are written into
-- takes function pointer that returns and takes single double
*/
void evaluateFunction(std::vector<double>& linSpacePtr,
                      std::vector<double>& funtionMatrix, 
                      double (*function)(double), 
                      std::size_t size)
{
    if(linSpacePtr.size() < size) return;

    for(int i = 0; i < size; i++)
    {
        funtionMatrix[i] = function(linSpacePtr[i]);
    }
}

/*
-- takes coefficients to be optimized 
-- takes  INITIALIZED linear space 
-- return apporoximation to function with given coefficients 
*/
void feedForward(std::vector<double>& linSpacePtr, 
                 std::vector<double>& cofficientMatrix, 
                 std::vector<double>& predictedMatrix,
                 std::size_t  size)
{
    if(linSpacePtr.size() < size) return;
    for(std::size_t i=0; i < size; i++)
    {
        predictedMatrix[i] = linSpacePtr[i]*cofficientMatrix[1] + cofficientMatrix[0]; // k*x + b
    }
}




/*
-- returns sum of squares of differences between two vectors
-- it is a cost function
*/
double squaredError(std::vector<double>& functionMatrix,
                    std::vector<double>& predictionMatrix)
{
    double totalError = 0.0;
    std::size_t i = functionMatrix.size();
    if(functionMatrix.size() != predictionMatrix.size()) return 0.0;
    for(std::size_t i = 0; i < SIZE; i++)
    {
        totalError += pow((functionMatrix[i] - predictionMatrix[i]), 2);
    }
    return totalError;
}


/*
-- calculates gradients
-- returns squared error on given parameters
*/
double calculateGradient(double (*squaredError)(std::vector<double>&,  std::vector<double>&),
                       std::vector<double>& linSpacePtr,
                       std::vector<double>& cofficientMatrix,
                       std::vector<double>& gradientVector,
                       std::vector<double>& predictedMatrix,
                       std::vector<double>& functionMatrix,
                       std::size_t size)
{
    double delta = 0.0001;
    double errorBefore = 0.0;
    double errorAfter = 0.0;

    for(std::size_t i = 0; i < cofficientMatrix.size(); i++)
    {
        feedForward(linSpacePtr, cofficientMatrix, predictedMatrix, size);
        errorBefore = squaredError(functionMatrix, predictedMatrix);  //we calcuale error for f(x)

        cofficientMatrix[i] = cofficientMatrix[i] + delta; //we change value a littlel bit (f(x+x0))

        feedForward(linSpacePtr, cofficientMatrix, predictedMatrix, size); 
        errorAfter = squaredError(functionMatrix, predictedMatrix);  // we calculate error for f(x+x0)

        gradientVector[i] = (errorAfter - errorBefore)/delta;
    }    
    return errorAfter;
}

int main()
{
    std::vector<double> linSpace(SIZE);
    std::vector<double> functionMatrix(SIZE);
    std::vector<double> predictionMatrix(SIZE);
    std::vector<double> coeffs(2);
    std::vector<double> gradients(2);
    double learingRate = 0.0005; //hyperparameter;
    int numIterations = 1500; //number of iterations
    double squareErr = 0; //will be used to print values 
    coeffs[0] = 1.0;
    coeffs[1] = 1.0;
    initLinSpace(linSpace, SIZE, 0, 1);
    evaluateFunction(linSpace, functionMatrix, function, SIZE);
    feedForward(linSpace,coeffs,predictionMatrix, SIZE);


    for(int i =0; i < numIterations; i++)
    {
        squareErr = calculateGradient(squaredError, 
                                        linSpace,
                                        coeffs,
                                        gradients,
                                        predictionMatrix,
                                        functionMatrix, 
                                        SIZE);
        
        //NOW WE HAVE DERIATIVES IN gradients MATRIX

        for(std::size_t j = 0; j < gradients.size(); j++)
        {
            coeffs[j] -= gradients[j]*learingRate;
        }

        if(i%10 == 0)
        {
            std::cout << squareErr;
            std::cout << " ";
            std::cout << gradients[0];
            std::cout << " ";
            std::cout << gradients[1] << std::endl;
        }                              
    }
    

    std::cout << coeffs[0] << std::endl;
    std::cout << coeffs[1] << std::endl;
    
    return 1;
}

