#define JUICE_IMPLEMENTATION
#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put_rect(JUICE_VEC2(7, 4), JUICE_SIZE(16, 8),
                 JUICE_PX(1, 0, JUICE_DOT));
  juice_end_frame();

  return 0;
}
