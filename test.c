#define JUICE_IMPLEMENTATION
#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put_line(JUICE_VEC2(0, 0), JUICE_VEC2(31, 15),
                 JUICE_PX(1, 1, JUICE_SOLID));
  juice_put_line(JUICE_VEC2(31, 0), JUICE_VEC2(0, 15),
                 JUICE_PX(1, 1, JUICE_SOLID));
  juice_end_frame();
  return 0;
}
