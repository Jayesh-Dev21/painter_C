#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FPS 60

int main(int argc, char *argv[]) {
  bool done = false;
  float_t delay_time = (1.0 / TARGET_FPS); // in milliseconds

  printf("SDL2 Image Viewer\n");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow =
      SDL_CreateWindow("Paint C", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  
  SDL_Surface *psurf = SDL_GetWindowSurface(pwindow);
  
  bool draw = false;
  while(!done){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch(event.type){
        case SDL_QUIT:
          done = true;
          break;
        case SDL_MOUSEMOTION:
          draw = true;
          
      }

    }

    // Clear screen with black color
    SDL_FillRect(psurf, NULL, SDL_MapRGB(psurf->format, 0, 0, 0));

    // Here you can add your drawing code

    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay((uint32_t)(delay_time * 1000)); // Convert to milliseconds
  }
  // Init Pixel
  //   int x, y;
  //   SDL_Rect pixel =
  //       (SDL_Rect){0, 0, 1, 1}; // x and y are specified and width and height
  //       is
  //                               // specified as 1 pixel each

  //   for (x = 0; x < width; x++) {
  //     for (y = 0; y < height; y++) {
  //       int idx = (y * loadedImg.width + x) * 3;
  //       uint8_t r = loadedImg.body[idx];
  //       uint8_t g = loadedImg.body[idx + 1];
  //       uint8_t b = loadedImg.body[idx + 2];
  //       uint32_t color = SDL_MapRGB(psurf->format, r, g, b);
  //       pixel.x = x;
  //       pixel.y = y;
  //       SDL_FillRect(psurf, &pixel, color);
  //     }
  //   }
  //   SDL_UpdateWindowSurface(pwindow);

  //   uint32_t start = SDL_GetTicks();
  //   SDL_Event e;

  //   while (SDL_GetTicks() - start < delay_time) {
  //       while (SDL_PollEvent(&e)) {
  //           if (e.type == SDL_QUIT) {
  //               SDL_DestroyWindow(pwindow);
  //               SDL_Quit();
  //               free(loadedImg.body);
  //               return 0;
  //           }
  //       }
  //   }
}
