#include <stdio.h>
#include "follow_line.h"

void traverse(Pos2Dint start,  Pos2Dint stop )
{
  InfoLine vline;
  Pos2Dint p;
  initLine(start.x, start.y, stop.x, stop.y, &vline);
  while (nextPoint(&vline, &p, +1) > 0) {
    if (p.x == start.x && p.y == start.y) {
      /* We suppose that the start position is not worth visiting! */
      continue;
    }
    printf("Visiting point (%d,%d)\n", p.x, p.y);
  }
}

int main()
{
  Pos2Dint start = {0, 0};
  Pos2Dint stop = {10, 5};
  traverse(start, stop);
  return 0;
}
