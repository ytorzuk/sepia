#include <iostream>
#include <chrono>
#include "tgaimage.h"
#include "sepia.h"

using namespace std;

int main()
{
    TGAImage input;
    input.read_tga_file("/home/ytorzuk/image.tga");
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

    output.write_tga_file("/home/ytorzuk/output.tga");

    return 0;
}

