#ifndef GFX_H_
#define GFX_H_

#include <cstdint>

class GFX
{
private:
    uint8_t *frame_buffer;
public:
    GFX(uint8_t *vram);
    uint8_t *VideoOut();
    ~GFX();
};





#endif // GFX_H_