#include <stdlib.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "Matrix.hpp"
#include "Vector2D.hpp"

using std::vector;

using namespace pipeline;

int64_t TimeInMicroseconds(vector<vector<uint32_t>>& vec, size_t width, size_t height)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t row = 0; row < height; ++row)
    {
        for (size_t col = 0; col < width; ++col)
        {
            vec[row][col] = rand();
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();
}

int64_t TimeInMicroseconds(IArray2D<uint32_t>& arr, size_t width, size_t height)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t row = 0; row < height; ++row)
    {
        for (size_t col = 0; col < width; ++col)
        {
            arr.at(row, col) = rand();
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

    Vector2D<uint32_t> vector2d(height, width);
    Matrix<uint32_t> matrix(height, width);

    vector<vector<uint32_t>> vec;
    vec.resize(height);

    for (size_t row = 0; row < height; ++row)
    {
        vec.at(row).resize(width);
    }

    vector<int64_t> vectorTimes;
    vector<int64_t> vector2DTimes;
    vector<int64_t> matrixTimes;

    for (size_t n = 0; n < 100; ++n)
    {
        vectorTimes.push_back(TimeInMicroseconds(vec, width, height));
        vector2DTimes.push_back(TimeInMicroseconds(vector2d, width, height));
        matrixTimes.push_back(TimeInMicroseconds(matrix, width, height));
    }

    double averageVectorTime = ComputeAverageTime(vectorTimes);
    double averageVector2DTime = ComputeAverageTime(vector2DTimes);
    double averageMatrixTime = ComputeAverageTime(matrixTimes);

    std::cout << "Average time for std::vector " << averageVectorTime << " microseconds\n";
    std::cout << "Average time for Vector2D " << averageVector2DTime << " microseconds\n";
    std::cout << "Average time for Matrix " << averageMatrixTime << " microseconds\n";

    return 0;
}