#ifndef JUICE_H
#define JUICE_H

#ifndef JUICE_CANVAS_WIDTH
#define JUICE_CANVAS_WIDTH 32
#endif

#ifndef JUICE_CANVAS_HEIGHT
#define JUICE_CANVAS_HEIGHT 16
#endif

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define JUICE_SOLID "█"
#define JUICE_DOT "░"

#define JUICE_RESET "\033[0m\n"

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

#define JUICE_MIN(a, b) ((a) < (b) ? (a) : (b))
#define JUICE_MAX(a, b) ((a) > (b) ? (a) : (b))

#define JUICE_PX_LIT(fg, bg, style)                                            \
  (juice_pixel_t) { (fg), (bg), (style) }
#define JUICE_PX(fg, bg, style) juice_mkpx(fg, bg, style)

#define JUICE_VEC2_LIT(x, y)                                                   \
  (juice_vec2_t) { (x), (y) }
#define JUICE_VEC2(x, y) juice_mkvec2(x, y)

#define JUICE_SIZE_LIT(w, h)                                                   \
  (juice_size_t) { (w), (h) }
#define JUICE_SIZE(w, h) juice_mksize(w, h)

#define JUICE_PX_FMT "\033[38;5;%dm\033[48;5;%dm%s"
#define JUICE_PX_ARG(px) (px).fg, (px).bg, (px).ch

static juice_pixel_t juice_canvas[JUICE_CANVAS_HEIGHT][JUICE_CANVAS_WIDTH];

void juice_begin_frame();
void juice_end_frame();

juice_pixel_t juice_mkpx(int fg, int bg, char *ch);
juice_vec2_t juice_mkvec2(size_t x, size_t y);
juice_size_t juice_mksize(size_t width, size_t height);

void juice_put(juice_vec2_t pos, juice_pixel_t px);
void juice_put_rect(juice_vec2_t start, juice_size_t size, juice_pixel_t px);
void juice_put_line(juice_vec2_t start, juice_vec2_t end, juice_pixel_t px);

#endif

#ifdef JUICE_IMPLEMENTATION

void juice_begin_frame() {
  for (size_t y = 0; y < JUICE_CANVAS_HEIGHT; y++)
    for (size_t x = 0; x < JUICE_CANVAS_WIDTH; x++) {
      juice_canvas[y][x] = JUICE_PX_LIT(15, 0, (char *)JUICE_SOLID);
    }
}

void juice_end_frame() {
  for (size_t y = 0; y < JUICE_CANVAS_HEIGHT; y++) {
    for (size_t x = 0; x < JUICE_CANVAS_WIDTH; x++)
      printf(JUICE_PX_FMT, JUICE_PX_ARG(juice_canvas[y][x]));
    printf(JUICE_RESET); // break line and reset
  }

  fflush(stdout);
}

juice_pixel_t juice_mkpx(int fg, int bg, char *ch) {
  return JUICE_PX_LIT(fg, bg, ch);
}

juice_vec2_t juice_mkvec2(size_t x, size_t y) { return JUICE_VEC2_LIT(x, y); }

juice_size_t juice_mksize(size_t width, size_t height) {
  return JUICE_SIZE_LIT(width, height);
}

void juice_put(juice_vec2_t pos, juice_pixel_t px) {
  if (pos.x >= JUICE_CANVAS_WIDTH || pos.y >= JUICE_CANVAS_HEIGHT)
    return;
  juice_canvas[pos.y][pos.x] = px;
}

void juice_put_rect(juice_vec2_t start, juice_size_t size, juice_pixel_t px) {
  size_t ex = JUICE_MIN(start.x + size.width, JUICE_CANVAS_WIDTH);
  size_t ey = JUICE_MIN(start.y + size.height, JUICE_CANVAS_HEIGHT);

  for (size_t y = start.y; y < ey; y++)
    for (size_t x = start.x; x < ex; x++)
      juice_put(JUICE_VEC2(x, y), px);
}

void juice_put_line(juice_vec2_t start, juice_vec2_t end, juice_pixel_t px) {
  int x0 = start.x;
  int y0 = start.y;
  int x1 = end.x;
  int y1 = end.y;

  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (1) {
    juice_put(JUICE_VEC2(x0, y0), px);

    if (x0 == x1 && y0 == y1)
      break;

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}
#endif
