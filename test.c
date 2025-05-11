#define JUICE_IMPLEMENTATION
#define JUICE_CANVAS_WIDTH 10
#define JUICE_CANVAS_HEIGHT 10

#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put_rect(JUICE_VEC2(0, 0), JUICE_SIZE(10, 10),
                 JUICE_PX(15, 0, JUICE_DOT));
  juice_end_frame();

  return 0;
}
