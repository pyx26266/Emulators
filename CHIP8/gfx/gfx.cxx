#include "gfx.hxx"

GFX::GFX(uint8_t *vram) {
    frame_buffer = vram;
    frame_buffer[0] = 1;
    frame_buffer[5] = 1;
    frame_buffer[30] = 1;
    frame_buffer[1] = 1;
    frame_buffer[2] = 1;
}

uint8_t *GFX::VideoOut() {
    return frame_buffer;
}

GFX::~GFX()
{
}