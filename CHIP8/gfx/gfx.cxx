#include "gfx.hxx"

GFX::GFX(uint8_t *vram) {
    frame_buffer = vram;
}

uint8_t *GFX::VideoOut() {
    return frame_buffer;
}

GFX::~GFX()
{
}