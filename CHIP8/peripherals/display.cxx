#include "display.hxx"
#include "../logging.hxx"



// Display::Display(std::vector<int>& buffer) : frame_buffer(buffer) {}

void Display::Initialize(int height, int width, const char *title) {
    this->height = height;
    this->width = width;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error in initialising SDL " << SDL_GetError() << std::endl;
        SDL_Quit();
        // exit(1);
    }
    SDL_CreateWindowAndRenderer(width, height, 0, &window_, &renderer_);
    if (window_ == nullptr || renderer_ == nullptr) {
        std::cerr << "SDL Error: " << SDL_GetError() << '\n';
        // return false;
    }
    SDL_SetWindowTitle(window_, title);
}

void Display::PollEvents(/* const std::function<void(int, int)> &on_key */) {
//     SDL_Event event;
//     bool quit = false;
//     while (!quit) {

//         while (SDL_PollEvent(&event) != 0) {
//             if (event.type == SDL_QUIT) {
//                 quit = true;
//             }
//             /* if (event.type == SDL_KEYDOWN) {
//                 on_key(event.key.keysym.sym, 1);
//             }
//             if (event.type == SDL_KEYUP) {
//                 on_key(event.key.keysym.sym, 0);
//             } */
//         }
//     }
}

 void Display::ClearScreen() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
}

 void Display::DrawPixel(int x, int y, int scale) {
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_Rect block {x * scale, y * scale, scale, scale};
    SDL_RenderDrawRect(renderer_, &block);
    SDL_RenderFillRect(renderer_, &block);
}

void Display::PresentBackBuffer() {
    SDL_RenderPresent(renderer_);
}

void Display::Refresh() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int totalBit = x + y*64;
            int arrayIndex = totalBit/8;
            int bitPosition = totalBit%8;
            if ((frame_buffer[arrayIndex] >> (7 - bitPosition)) & 0x01) {
                DrawPixel(x, y, 10);
                // LOG_INFO("drawing pixel x,y %d,%d", x, y);
            }
        }
    }
}

void Display::Connect(uint8_t *video_in) {
    frame_buffer = video_in;
}

Display::Display()
{
}

Display::~Display()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
}