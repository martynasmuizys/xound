#include "ui.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

void Window::init() {
    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) != 0) {
        return;
    }

    // Create window with Vulkan graphics context
    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_HIDDEN);
    SDL_Window* window = SDL_CreateWindow("Zoundboard", 1280, 720, window_flags);
    if (window == nullptr) {
        return;
    }
}
