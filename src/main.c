#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define TARGET_FPS 60
#define pixel_w 10
#define pixel_h 10
#define pixel_r 10
#define TOOLBAR_HEIGHT 60

typedef struct{
  uint8_t color_r;
  uint8_t color_g;
  uint8_t color_b;
  uint8_t color_a;
} Color;

const float_t delay_time = (1.0 / TARGET_FPS); // in milliseconds

Color red = {255, 0, 0, 255};
Color green = {0, 255, 0, 255};
Color blue = {0, 0, 255, 255};
Color black = {0, 0, 0, 255};
Color white = {255, 255, 255, 255};
Color yellow = {255, 255, 0, 255};
Color purple = {130, 0, 130, 255};

Color C_arr[7] = {
  {255, 0, 0, 255},   // Red
  {0, 255, 0, 255},   // Green
  {0, 0, 255, 255},   // Blue
  {0, 0, 0, 255},     // Black
  {255, 255, 255, 255}, // White
  {255, 255, 0, 255},  //yellow 
  {130, 0, 130, 255}  //purple
};

int CC_poss = sizeof(C_arr) / sizeof(C_arr[0]);

bool inside_canvas(int x, int y) {
    return y >= TOOLBAR_HEIGHT;
}

void drawCircle(int _x, int _y, int radius, SDL_Surface *psurf, Color C_used){
  for(int w = 0; w < radius * 2; w++){
    for(int h = 0; h < radius * 2; h++){
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if((dx*dx + dy*dy) <= (radius * radius)){
        SDL_Rect pixel = (SDL_Rect){_x + dx, _y + dy, 1, 1}; // x and y are specified and width and height is specified as 1 pixel each
        SDL_FillRect(psurf, &pixel, SDL_MapRGB(psurf->format, C_used.color_r, C_used.color_g, C_used.color_b));
      }
    }
  }
}

void drawPixel(bool draw, int _x, int _y, SDL_Surface *psurf, Color C_used){
  
  // SDL_Rect pixel = (SDL_Rect){_x-pixel_w/2, _y-pixel_h/2, pixel_w, pixel_h}; // x and y are specified and width and height is specified as 1 pixel each
  // SDL_FillRect(psurf, &pixel, SDL_MapRGB(psurf->format, C_used.color_r, C_used.color_g, C_used.color_b));

  // Here you can add your drawing code
  drawCircle(_x, _y, pixel_r, psurf, C_used);

}


int main(int argc, char *argv[]) {
  bool done = false;

  printf("SDL2 Image Viewer\n");
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow =
  SDL_CreateWindow("Paint C", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    
  SDL_Surface *psurf = SDL_GetWindowSurface(pwindow);
  SDL_FillRect(psurf, NULL, SDL_MapRGB(psurf->format, 0, 0, 0));
  SDL_UpdateWindowSurface(pwindow);
  bool draw = false;
  int _x, _y;
  Color CC_used = black;
  int i = 0; 
  while(!done){
    uint32_t frame_start = SDL_GetTicks();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch(event.type){
        case SDL_QUIT:
          done = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            draw = true;
            _x = event.button.x;
            _y = event.button.y;
            CC_used = C_arr[i%CC_poss];
          }
          else if (event.button.button == SDL_BUTTON_RIGHT) {
            draw = false;
            _x = event.button.x;
            _y = event.button.y;
            i++;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          // CC_used = black;
          draw = false;
          break;  
          if (event.button.button == SDL_BUTTON_LEFT) {
              draw = false;
          }
          break;
        case SDL_MOUSEMOTION:
          _x = event.motion.x;
          _y = event.motion.y;
          break;
      }

    }
    if(draw){drawPixel(draw, _x, _y, psurf, CC_used); 
    SDL_UpdateWindowSurface(pwindow);
    }
    uint32_t frame_time = SDL_GetTicks() - frame_start;
    if(frame_time < (uint32_t)(delay_time * 1000)){
      SDL_Delay((uint32_t)(delay_time * 1000) - frame_time);
      // Convert to milliseconds
    }
  }
  SDL_DestroyWindow(pwindow);
  SDL_Quit();
  return 0;
}
