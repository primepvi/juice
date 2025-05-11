# juice.c 🧃

A tiny single-header terminal canvas library written in C.  
Draw pixels, rectangles, and lines using ANSI escape codes.

## Usage

To use `juice`, you must define some macros before including the header.  
Here’s a basic example:

```c
#define JUICE_IMPLEMENTATION
#include "juice.h"
```

You can also define canvas size using macros before including the header:

```c
#define JUICE_IMPLEMENTATION
#define JUICE_CANVAS_WIDTH 64   // Set canvas width to 64 pixels
#define JUICE_CANVAS_HEIGHT 64  // Set canvas height to 64 pixels
#include "juice.h"
```

## Examples

### Draw a single solid pixel at position `(x: 15, y: 7)`:

```c
#define JUICE_IMPLEMENTATION
#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put(JUICE_VEC2(15, 7), JUICE_PX(0, 0, JUICE_SOLID));
  juice_end_frame();
  return 0;
}
```

### Draw a 16x8 rectangle at position `(x: 7, y: 4)`:

```c
#define JUICE_IMPLEMENTATION
#include "juice.h"

int main() {
  juice_begin_frame();
  juice_put_rect(JUICE_VEC2(7, 4), JUICE_SIZE(16, 8), JUICE_PX(1, 0, JUICE_DOT));
  juice_end_frame();
  return 0;
}
```

## License

MIT License
