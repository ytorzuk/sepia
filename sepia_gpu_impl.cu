#include "sepia.h"

#define BLOCK_SIZE (32)

namespace gpu
{

__global__ void sepiaKernel(unsigned char * image, unsigned width, unsigned height)
{
        int row = blockIdx.y * BLOCK_SIZE + threadIdx.y;
        int col = blockIdx.x * BLOCK_SIZE + threadIdx.x;

        int cIdx = ( row * width + col ) * 3;

        unsigned char b = *( image + cIdx     );
        unsigned char g = *( image + cIdx + 1 );
        unsigned char r = *( image + cIdx + 2 );

        *( image + cIdx     ) = .274f * r + .134f * g + .192f * b; // Red channel
        *( image + cIdx + 1 ) = .346f * r + .486f * g + .168f * b; // Green channel
        *( image + cIdx + 2 ) = .242f * r + .669f * g + .089f * b; // Blue channel
}


void applySepia(const unsigned char * inBuffer, unsigned width, unsigned height, unsigned char * outBuffer)
{
    unsigned char * dImage;
    unsigned size = width * height * 3;
    cudaMalloc(&dImage, size);
    cudaMemcpy(dImage, inBuffer, size, cudaMemcpyHostToDevice);

    dim3 dimBlock( BLOCK_SIZE, BLOCK_SIZE );
    dim3 dimGrid( width / dimBlock.x, height / dimBlock.y );
    sepiaKernel<<<dimGrid, dimBlock>>>(dImage, width, height);

    cudaMemcpy(outBuffer, dImage, size, cudaMemcpyDeviceToHost);
    cudaFree(dImage);
}
}

