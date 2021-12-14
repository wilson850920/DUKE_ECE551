#include <cstdio>
#include <cstdlib>

#include "function.h"

//class SinFunciton : public Function<int, int> {
// public:
//  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
//};

int bianrySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int fans = f->invoke(mid);
    if (fans == 0) {
      return mid;
    }
    else if (fans > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
