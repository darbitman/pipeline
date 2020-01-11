#include <benchmark/benchmark.h>
#include <stdlib.h>
#include <cstdint>
#include <vector>

#include "Vector2D.hpp"

static void BM_Vector2D(benchmark::State& state)
{
    constexpr size_t width{1920};
    constexpr size_t height{1080};

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
    }
}

BENCHMARK(BM_Vector2D);

static void BM_StdVector2D(benchmark::State& state)
{
    constexpr size_t width{1920};
    constexpr size_t height{1080};

    std::vector<std::vector<uint32_t>> vec;
    vec.resize(height);
    for (size_t row = 0; row < height; ++row)
    {
        vec.at(row).resize(width);
    }

    for (auto _ : state)
    {
        for (size_t row = 0; row < height; ++row)
        {
            for (size_t col = 0; col < width; ++col)
            {
                vec[row][col] = rand();
            }
        }
    }
}

BENCHMARK(BM_Vector2D);

BENCHMARK_MAIN();
