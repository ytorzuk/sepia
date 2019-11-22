#include <iostream>
#include "tgaimage.h"
#include "sepia.h"

using namespace std;

int main()
{
    TGAImage input;
    input.read_tga_file("/home/ytorzuk/image.tga");
    TGAImage output(input.get_width(), input.get_height(), input.get_bytespp());
    cpu::applySepia(input.buffer(), input.get_width(), input.get_height(), output.buffer());
    output.write_tga_file("/home/ytorzuk/output.tga");

    return 0;
}

