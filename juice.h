#ifndef JUICE_H
#define JUICE_H

#include <stddef.h>
#include <stdio.h>

#define JUICE_SOLID "█"
#define JUICE_DOT "░"

#define JUICE_CANVAS_WIDTH 32
#define JUICE_CANVAS_HEIGHT 16

typedef struct {
  size_t width;
  size_t height;
} juice_size_t;

typedef struct {
  size_t x;
  size_t y;
} juice_vec2_t;

typedef struct {
  int fg;
  int bg;
  char *ch;
} juice_pixel_t;

#define JUICE_PX_LIT(fg, bg, style)                                            \
  (juice_pixel_t) { (fg), (bg), (style) }
#define JUICE_PX(fg, bg, style) juice_mkpx(fg, bg, style)

#define JUICE_VEC2_LIT(x, y)                                                   \
  (juice_vec2_t) { (x), (y) }
#define JUICE_VEC2(x, y) juice_mkvec2(x, y)

#define JUICE_PX_FMT "\033[38;5;%dm\033[48;5;%dm%s"
#define JUICE_PX_ARG(px) (px).fg, (px).bg, (px).ch

static juice_pixel_t juice_canvas[JUICE_CANVAS_HEIGHT][JUICE_CANVAS_WIDTH];

void juice_begin_frame();
void juice_end_frame();

juice_pixel_t juice_mkpx(int fg, int bg, char *ch);
juice_vec2_t juice_mkvec2(size_t x, size_t y);

void juice_put(juice_vec2_t pos, juice_pixel_t px);

#endif

#ifdef JUICE_IMPLEMENTATION

void juice_begin_frame() {
  for (size_t y = 0; y < JUICE_CANVAS_HEIGHT; y++)
    for (size_t x = 0; x < JUICE_CANVAS_WIDTH; x++) {
      juice_canvas[y][x] = JUICE_PX_LIT(15, 0, JUICE_SOLID);
    }
}

void juice_end_frame() {
  for (size_t y = 0; y < JUICE_CANVAS_HEIGHT; y++) {
    for (size_t x = 0; x < JUICE_CANVAS_WIDTH; x++)
      printf(JUICE_PX_FMT, JUICE_PX_ARG(juice_canvas[y][x]));
    printf("\033[0m\n"); // break line and reset
  }

  fflush(stdout);
}

juice_pixel_t juice_mkpx(int fg, int bg, char *ch) {
  return JUICE_PX_LIT(fg, bg, ch);
}

juice_vec2_t juice_mkvec2(size_t x, size_t y) { return JUICE_VEC2_LIT(x, y); }

void juice_put(juice_vec2_t pos, juice_pixel_t px) {
  juice_canvas[pos.y][pos.y] = px;
}

#endif
