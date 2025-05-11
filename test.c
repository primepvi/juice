#define JUICE_IMPLEMENTATION
#define JUICE_CANVAS_WIDTH 41
#define JUICE_CANVAS_HEIGHT 20
#include "juice.h"

int main() {
  juice_begin_frame();

  // yellow face
  juice_put_rect(JUICE_VEC2(10, 5), JUICE_SIZE(20, 10),
                 JUICE_PX(226, 226, JUICE_SOLID));

  // black eyes
  juice_put_rect(JUICE_VEC2(14, 8), JUICE_SIZE(2, 2),
                 JUICE_PX(0, 0, JUICE_SOLID));
  juice_put_rect(JUICE_VEC2(24, 8), JUICE_SIZE(2, 2),
                 JUICE_PX(0, 0, JUICE_SOLID));

  // red mouth
  juice_put_rect(JUICE_VEC2(16, 12), JUICE_SIZE(8, 1),
                 JUICE_PX(160, 0, JUICE_SOLID));

  juice_end_frame();
  return 0;
}
