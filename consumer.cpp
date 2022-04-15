#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;
struct signal {
  static int plate;
  static int apple;
  static int orange;
  signal() {
    plate = 1;
    apple = 0;
    orange = 0;
  }
  void plate_up() { ++plate; }
  void plate_down() { --plate; }
  void apple_up() { ++apple; }
  void apple_down() { --apple; }
  void orange_up() { ++orange; }
  void orange_down() { --orange; }
};