#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
using namespace std;
mutex p, a, o, at; //实例化m对象，不要理解为定义变量
int k_plate = 5;
int apple = 0;
int orange = 0;

void dad() {
  while (true) {
    lock_guard<mutex> locker(p);
    --k_plate;
  }
}

void mon() {
  while (1) {
    lock_guard<mutex> locker(p);
    cout << k_plate << endl;
  }
}

int main() {
  thread d(dad);
  thread mmm(mon);
  mmm.join();
  d.join();
}