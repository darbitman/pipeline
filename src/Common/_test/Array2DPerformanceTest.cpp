#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "Array2D.hpp"

using std::vector;

using namespace pipeline;

int64_t TimeInMicroseconds(vector<vector<double>>& vec, size_t width, size_t height)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t row = 0; row < height; ++row)
    {
        for (size_t col = 0; col < width; ++col)
        {
            vec[row][col] = 1.0;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();
}

int64_t TimeInMicroseconds(Array2D<double>& arr, size_t width, size_t height)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t col = 0; col < width; ++col)
    {
        for (size_t row = 0; row < height; ++row)
        {
            arr.at(col, row);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();
}

double ComputeAverageTime(const vector<int64_t>& times)
{
    double average = 0.0;
    double N = times.size();
    for (int n = 0; n < N; ++n)
    {
        average += times[n] / N;
    }
    return average;
}

int32_t main()
{
    constexpr size_t width{1920};
    constexpr size_t height{1080};

    Array2D<double> arr(width, height);

    vector<vector<double>> vec;
    vec.resize(height);

    for (size_t row = 0; row < height; ++row)
    {
        vec.at(row).resize(width);
    }

    vector<int64_t> vectorTimes;
    vector<int64_t> array2DTimes;

    for (size_t n = 0; n < 100; ++n)
    {
        vectorTimes.push_back(TimeInMicroseconds(vec, width, height));
        array2DTimes.push_back(TimeInMicroseconds(arr, width, height));
    }

    double averageVectorTime = ComputeAverageTime(vectorTimes);
    double averageArray2DTime = ComputeAverageTime(array2DTimes);

    std::cout << "Average time for std::vector " << averageVectorTime << " microseconds\n";
    std::cout << "Average time for Array2D " << averageArray2DTime << " microseconds\n ";

    return 0;
}