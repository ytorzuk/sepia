#include "sepia.h"

namespace cpu
{
void applySepia(const unsigned char * inBuffer, unsigned width, unsigned height, unsigned char * outBuffer)
{
    for (unsigned row = 0; row < height; row++)
        for (unsigned col = 0; col < width; col++)
        {
            unsigned cIdx = ( row * width + col ) * 3;

            float b = *( inBuffer + cIdx     );
            float g = *( inBuffer + cIdx + 1 );
            float r = *( inBuffer + cIdx + 2 );

            *( outBuffer + cIdx     ) = .274f * r + .134f * g + .192f * b; // Red channel
            *( outBuffer + cIdx + 1 ) = .346f * r + .486f * g + .168f * b; // Green channel
            *( outBuffer + cIdx + 2 ) = .242f * r + .669f * g + .089f * b; // Blue channel
        }
}
}
