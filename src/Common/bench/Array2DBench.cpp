#include <benchmark/benchmark.h>
#include <stdlib.h>
#include <cstdint>
#include <vector>

#include "Matrix.hpp"
#include "Vector2D.hpp"

static void BM_Vector2D(benchmark::State& state)
{
    size_t width = state.range(0);
    size_t height = state.range(1);

    pipeline::Vector2D<uint32_t> vec(height, width);

    for (auto _ : state)
    {
        for (size_t row = 0; row < height; ++row)
        {
            for (size_t col = 0; col < width; ++col)
            {
                vec.at(row, col) = rand();
            }
        }
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_Vector2D)->Args({1920, 1080});

static void BM_StdVector2D(benchmark::State& state)
{
    size_t width = state.range(0);
    size_t height = state.range(1);

    std::vector<std::vector<uint32_t>> vec;
    vec.resize(height);
    for (size_t row = 0; row < height; ++row)
    {
        vec.at(row).resize(width);
    }

    for (auto _ : state)
    {
        for (size_t col = 0; col < width; ++col)
        {
            for (size_t row = 0; row < height; ++row)
            {
                vec[row][col] = rand();
            }
        }
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_StdVector2D)->Args({1920, 1080});

// static void BM_Matrix(benchmark::State& state)
// {
//     size_t width = state.range(0);
//     size_t height = state.range(1);

//     pipeline::Matrix<uint32_t> vec(width, height);

//     for (auto _ : state)
//     {
//         for (size_t row = 0; row < height; ++row)
//         {
//             for (size_t col = 0; col < width; ++col)
//             {
//                 vec.at(row, col) = rand();
//             }
//         }
//         benchmark::ClobberMemory();
//     }
// }

// BENCHMARK(BM_Matrix)->Args({1920, 1080});

BENCHMARK_MAIN();
