#include<iostream>
#include<vector>
#include <chrono>

double sumFirst(std::vector<double>& vectorA)
{
    if(vectorA.empty())
    {
        std::cout << "EMPTY ARRAY" << std::endl;
        return 0;
    }


    double sum = 0.0;
    for(std::size_t i = 0; i < vectorA.size(); i++)
    {
        sum += vectorA[i];
    }

    return sum;

}


double sumSecond(std::vector<double>& vectorA)
{
    if(vectorA.empty())
    {
        std::cout << "EMPTY ARRAY" << std::endl;
        return 0;
    }


    double sum = 0.0;
    std::size_t sizeVec = vectorA.size();
    for(std::size_t i = 0; i < sizeVec; i++)
    {
        sum += vectorA[i];
    }

    return sum;

}



int main()
{
    
    std::vector<double> vectorA(9999999);

    for(std::size_t i = 0; i < vectorA.size(); i++)
    {
        vectorA[i] = i;
    }

    double sum = 0.0;




    std::clock_t beforeSumFirst = std::clock();
    sum = sumFirst(vectorA);
    std::clock_t afterSumFirst = std::clock();
    
    std::cout << afterSumFirst - beforeSumFirst << " CLOCKS - SUM FIRST " <<" VALUE " << sum << std::endl;

    std::clock_t beforeSumSecond = std::clock();
    sum = sumSecond(vectorA);
    std::clock_t afterSumSecond = std::clock();

    std::cout << afterSumSecond- beforeSumSecond << " CLOCKS - SUM SECOND " << " VALUE " << sum << std::endl;
    std::cout << " NODE: *** 1000 CLOCKS per second ***" << std::endl;

    return 0;
}

