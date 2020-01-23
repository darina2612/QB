#include "PerformanceTestHelpers.h"

#include <chrono>
#include <iostream>


namespace PerformanceTestHelpers
{

double ExecutionTime(const std::function<void()>& task)
{
    using namespace std::chrono;
    auto startTimer = steady_clock::now();
    task();
    return static_cast<double>((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den;
}

void TestPerformance(const std::string& testInfo, const std::function<void()>& task)
{
    std::cout << testInfo << " execution time : " << ExecutionTime(task) << std::endl;
}

}
