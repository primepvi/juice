#define JUICE_IMPLEMENTATION
#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put(JUICE_VEC2(10, 5), JUICE_PX(25, 0, JUICE_DOT));
  juice_end_frame();

  return 0;
}
