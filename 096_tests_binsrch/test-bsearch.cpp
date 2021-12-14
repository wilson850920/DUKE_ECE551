#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <ostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

class testFunc : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max;
  if (high > low) {
    max = log2(high - low) + 1;
  }
  else {
    max = 1;
  }
  CountedIntFn * temp_func = new CountedIntFn(max, f, mesg);
  int gotyou = binarySearchForZero(temp_func, low, high);
  assert(gotyou == expected_ans);
}

int main(void) {
  testFunc * myFunc = new testFunc();

  check(myFunc, -1, 4, 0, "1");
  check(myFunc, -3, -1, -2, "2");
  check(myFunc, 1, 4, 1, "3");
  check(myFunc, 0, 8, 0, "4");
  check(myFunc, -10, 0, -1, "5");

  delete myFunc;
  return EXIT_SUCCESS;
}
