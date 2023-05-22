#include "SDL_FontCache.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

class Point {
public:
  double x = 0;
  double y = 0;
  double z = 0;

  Point() {}
};

class Text {
public:
  FC_Font *font = FC_CreateFont();
  SDL_Color color;
  int size;
  char *path;

  Text(SDL_Color fontColor, char *fontPath, int fontSize) {
    color = fontColor;
    size = fontSize;
    path = fontPath;
  }
};

class Entity {
public:
  int posX;
  int posY;
  int velocity;
  int sizeX = 40;
  int sizeY = 40;

  Entity(int mouseX, int mouseY) {
    posX = mouseX;
    posY = mouseY;
  }
};

class Application {
public:
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  std::vector<Entity> entities;
  void loop();
  void renderTime(int time, SDL_Texture *text_texture);
  int mouseX;
  int mouseY;

  Application() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      std::cout << "SDL ERROR: " << SDL_GetError() << std::endl;
      return;
    }

    if (TTF_Init() < 0) {
      std::cout << "Error initializing SDL_ttf:" << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("./yoster.ttf", 24);

    window = SDL_CreateWindow("CUBE", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    if (!window) {
      std::cout << "SDL ERROR: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
      std::cout << "SDL ERROR: " << SDL_GetError() << std::endl;
    }
  }

  ~Application() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }
};

void renderText(Text textObject, SDL_Renderer &renderer){
    // TODO: Render the texture.
};

void clearTextRender(Text textObject) {
  // TODO: Destroy render;
}

void Application::loop() {
  bool windowOpen = true;
  int time;
  while (windowOpen) {
    Uint64 start = SDL_GetPerformanceCounter();
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        windowOpen = false;
      }

      if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouseX, &mouseY);
        Entity newBlock(mouseX, mouseY);
        entities.push_back(newBlock);
        std::cout << entities.size() << std::endl;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_r:
          entities.clear();
          break;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    for (Entity entiti : entities) {
      SDL_Rect rect;
      rect.h = entiti.sizeY;
      rect.w = entiti.sizeX;
      rect.x = entiti.posX;
      rect.y = entiti.posY;

      SDL_RenderDrawRect(renderer, &rect);
      SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);

    Uint64 end = SDL_GetPerformanceCounter();

    // limit fps to 60
    float elapsedMS =
        ((end - start) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
    time = floor(SDL_GetTicks() / 1000.0f);
  }
}

int main(int argc, char **argv) {
  Application app;
  std::cout << "Hello world" << std::endl;
  app.loop();
  return 0;
}
