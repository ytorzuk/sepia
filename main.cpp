#include <iostream>
#include <chrono>
#include "tgaimage.h"
#include "sepia.h"

using namespace std;

int main(int argc, const char ** argv)
{
    TGAImage input;
    input.read_tga_file(argv[1]);
    TGAImage output(input.get_width(), input.get_height(), input.get_bytespp());

    auto cpuStart = std::chrono::system_clock::now();
    cpu::applySepia(input.buffer(), input.get_width(), input.get_height(), output.buffer());
    auto cpuEnd = std::chrono::system_clock::now();

    std::chrono::duration<double> cpuDiff = cpuEnd-cpuStart;
    std::cout << "Time to apply sepia effect on CPU to an image: " << cpuDiff.count() << " s\n";

    auto gpuStart = std::chrono::system_clock::now();
    gpu::applySepia(input.buffer(), input.get_width(), input.get_height(), output.buffer());
    auto gpuEnd = std::chrono::system_clock::now();

    std::chrono::duration<double> gpuDiff = gpuEnd-gpuStart;
    std::cout << "Time to apply sepia effect on GPU to an image: " << gpuDiff.count() << " s\n";

    output.write_tga_file(argv[2]);

    return 0;
}

